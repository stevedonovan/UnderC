cmake_minimum_required(VERSION 3.16)
project(Underc VERSION 1.5.4 LANGUAGES CXX)
include(GNUInstallDirs)
include(CTest)

option(UCL_SHARED "Build underc as a shared library" OFF)
# GNU readline and curses are not part of a stock MSVC toolchain, and the
# historical Windows build never used them, so default the option off there.
if(WIN32)
    option(UCL_USE_READLINE "Build with GNU readline support" OFF)
else()
    option(UCL_USE_READLINE "Build with GNU readline support" ON)
endif()
option(UCL_DISABLE_NATIVE_ABI "Use VM-width int/enum/long objects" OFF)
option(UCL_LIBFFI "Use libffi for ABI-portable native calls" ON)
option(UCL_COMPILE_ONLY_NARROW_VM "Allow a VM word narrower than host pointers for compile checks only" OFF)
option(UCL_STRICT_CONVERSIONS "Enable migration-focused conversion diagnostics" OFF)
option(UCL_LEGACY_CPP_IMPORTS "Enable experimental compiler-specific C++ symbol imports" ON)
option(UCL_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

math(EXPR UNDERC_HOST_BITS "${CMAKE_SIZEOF_VOID_P} * 8")
set(UNDERC_VM_BITS "${UNDERC_HOST_BITS}" CACHE STRING "UnderC VM word size (16, 32, or 64)")
set_property(CACHE UNDERC_VM_BITS PROPERTY STRINGS 16 32 64)
if(NOT UNDERC_VM_BITS MATCHES "^(16|32|64)$")
    message(FATAL_ERROR "UNDERC_VM_BITS must be 16, 32, or 64")
endif()
if(UNDERC_VM_BITS LESS UNDERC_HOST_BITS AND NOT UCL_COMPILE_ONLY_NARROW_VM)
    message(FATAL_ERROR
        "UNDERC_VM_BITS=${UNDERC_VM_BITS} cannot transport ${UNDERC_HOST_BITS}-bit host pointers. "
        "Use the host-width default for runnable builds, or set "
        "UCL_COMPILE_ONLY_NARROW_VM=ON for a non-runnable compile check.")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Parser sources are generated with bison/yacc from build/parser.y and cached in
# src/gen.  If the cached files are present they are used verbatim, and bison is
# neither required nor searched for.  This allows building on systems that have
# no bison/yacc installed.  Delete src/gen to force regeneration.
set(UNDERC_PARSER_GEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gen")
set(UNDERC_PARSER_SOURCE "${UNDERC_PARSER_GEN_DIR}/tparser.cpp")
set(UNDERC_PARSER_HEADER "${UNDERC_PARSER_GEN_DIR}/tparser.h")

if(EXISTS "${UNDERC_PARSER_SOURCE}" AND EXISTS "${UNDERC_PARSER_HEADER}")
    message(STATUS "UnderC: using pre-generated parser in ${UNDERC_PARSER_GEN_DIR} (bison/yacc not required)")
    set(UNDERC_PARSER_OUTPUTS "${UNDERC_PARSER_SOURCE}")
else()
    message(STATUS "UnderC: generated parser not found in ${UNDERC_PARSER_GEN_DIR}; running bison/yacc")
    find_package(BISON REQUIRED)
    file(MAKE_DIRECTORY "${UNDERC_PARSER_GEN_DIR}")
    BISON_TARGET(UnderCParser build/parser.y "${UNDERC_PARSER_SOURCE}"
        DEFINES_FILE "${UNDERC_PARSER_HEADER}"
        COMPILE_FLAGS "-y -Wno-conflicts-sr -Wno-conflicts-rr -Wno-other")
    set(UNDERC_PARSER_OUTPUTS "${BISON_UnderCParser_OUTPUTS}")
endif()

set(UNDERC_INCLUDE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../include")
set(UNDERC_PUBLIC_INCLUDE_DIR "${UNDERC_INCLUDE_ROOT}/underc")
set(UNDERC_UCLSTL_INCLUDE_DIR "${UNDERC_PUBLIC_INCLUDE_DIR}/uclstl")
set(UNDERC_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include")
file(MAKE_DIRECTORY "${UNDERC_GENERATED_INCLUDE_DIR}/underc")
configure_file(version.h.in
    "${UNDERC_GENERATED_INCLUDE_DIR}/underc/version.h" @ONLY)

# The interactive (#help) and command-line (--help) help text is compiled into
# the interpreter from README.md and cli/README.md instead of being read from
# resource files at runtime.  Only the text between the
# GENERATE_HELP_H_CONTENT_CLI markers in each file is used.
set(UNDERC_HELP_HEADER_DIR "${CMAKE_CURRENT_BINARY_DIR}/help-gen")
set(UNDERC_HELP_HEADER "${UNDERC_HELP_HEADER_DIR}/help.h")
set(UNDERC_README_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../README.md")
set(UNDERC_README_CLI  "${CMAKE_CURRENT_SOURCE_DIR}/../cli/README.md")
file(MAKE_DIRECTORY "${UNDERC_HELP_HEADER_DIR}")
add_custom_command(
    OUTPUT "${UNDERC_HELP_HEADER}"
    COMMAND "${CMAKE_COMMAND}"
        "-DREADME_ROOT=${UNDERC_README_ROOT}"
        "-DREADME_CLI=${UNDERC_README_CLI}"
        "-DOUTPUT=${UNDERC_HELP_HEADER}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/build/generate-help-h.cmake"
    DEPENDS "${UNDERC_README_ROOT}" "${UNDERC_README_CLI}"
        "${CMAKE_CURRENT_SOURCE_DIR}/build/generate-help-h.cmake"
    COMMENT "Generating compiled-in help text (help.h)"
    VERBATIM)
add_custom_target(underc-help-header DEPENDS "${UNDERC_HELP_HEADER}")

# defs.h is the default interactive prelude.  It is installed to lib/uclr and
# loaded from <UC_HOME>/lib/uclr/defs.h at runtime; keep the in-tree copy under
# lib/uclr in sync so the repository root works as UC_HOME during development.
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/uclr/defs.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../lib/uclr/defs.h" COPYONLY)

set(UNDERC_SOURCES
    breakpoints.cpp bytecode_optimizer.cpp class.cpp code.cpp common.cpp directcall.cpp dissem.cpp
    engine.cpp errors.cpp ex_vfscanf.cpp expressions.cpp function.cpp
    function_match.cpp hard_except.cpp imports.cpp iostrm.cpp keywords.cpp
    lexer.cpp main.cpp mangle.cpp mstring.cpp operators.cpp os.cpp program.cpp
    subst.cpp table.cpp templates.cpp tokens.cpp types.cpp
    uc_tokens.cpp ucri.cpp utils.cpp dll_entry.cpp ${UNDERC_PARSER_OUTPUTS}
    ${UNDERC_HELP_HEADER})

if(UNIX AND NOT APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|AMD64)$")
    enable_language(ASM)
    list(APPEND UNDERC_SOURCES sysv_abi_x86_64.S)
    set(UNDERC_HAS_SYSV_X86_64 TRUE)
endif()

if(UCL_SHARED)
    add_library(underc SHARED ${UNDERC_SOURCES})
    target_compile_definitions(underc PRIVATE UCL_SHARED=1)
else()
    add_library(underc STATIC ${UNDERC_SOURCES})
endif()
add_library(Underc::underc ALIAS underc)
target_include_directories(underc
    PUBLIC
        "$<BUILD_INTERFACE:${UNDERC_INCLUDE_ROOT}>"
        "$<BUILD_INTERFACE:${UNDERC_GENERATED_INCLUDE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
        "${UNDERC_PUBLIC_INCLUDE_DIR}"
        "${UNDERC_GENERATED_INCLUDE_DIR}/underc"
        "${UNDERC_HELP_HEADER_DIR}"
        "${UNDERC_PARSER_GEN_DIR}")
set_source_files_properties(main.cpp PROPERTIES OBJECT_DEPENDS "${UNDERC_HELP_HEADER}")
target_compile_definitions(underc PRIVATE _CONSOLE _FAKE_IOSTREAM _MSTRING)
target_compile_definitions(underc PUBLIC UNDERC_VM_BITS=${UNDERC_VM_BITS})
if(UNDERC_HAS_SYSV_X86_64)
    target_compile_definitions(underc PRIVATE UCL_SYSV_X86_64=1)
endif()
if(NOT UCL_LIBFFI AND UNDERC_HOST_BITS EQUAL 64 AND NOT UNDERC_HAS_SYSV_X86_64)
    message(FATAL_ERROR "UCL_LIBFFI=OFF on a 64-bit host is supported only for Linux System V x86-64")
endif()
if(UCL_LEGACY_CPP_IMPORTS)
    target_compile_definitions(underc PRIVATE UCL_LEGACY_CPP_IMPORTS=1)
endif()
if(UCL_COMPILE_ONLY_NARROW_VM)
    target_compile_definitions(underc PRIVATE UCL_COMPILE_ONLY_NARROW_VM=1)
endif()
# libffi discovery.
#
# Every platform accepts an explicitly given
#
#   -DLIBFFI_INCLUDE_DIR=<dir> -DLIBFFI_LIBRARY=<file>
#
# pair.  It is used verbatim and is never replaced by an automatically
# discovered copy, so a deliberate choice always wins.  On Windows that pair is
# the only mechanism: the nmake build (build-cmake-vs2026-nmake-release.bat)
# has no pkg-config, so the two variables are normally filled in by
# find_path/find_library from CMAKE_PREFIX_PATH and PkgConfig is never
# required there.
#
# On Unix pkg-config remains the usual answer, but it is no longer the only
# one.  The search order is: the explicit pair above, a libffi CMake package,
# pkg-config, and finally a plain find_path/find_library sweep.  A libffi built
# by hand into its own prefix commonly installs neither a CMake package nor a
# .pc file, and is now buildable against with
#
#   cmake -S src -B build -DLIBFFI_INCLUDE_DIR=/opt/libffi/include \
#                         -DLIBFFI_LIBRARY=/opt/libffi/lib/libffi.a
#
# A prebuilt libffi carries no architecture marker that find_library inspects,
# so an x64 package is accepted without complaint by an x86 build.  The
# mismatch then surfaces only when the first consumer executable links, as a
# wall of unresolved __imp__ffi_* externals.  Probe the candidate with a real
# link before committing to it, so the failure is reported here with a usable
# explanation instead of by the linker.  The probe result is cached, and
# re-tested whenever the candidate itself changes.
macro(underc_probe_libffi probe_var probe_includes probe_libraries)
    if(NOT "${probe_includes}|${probe_libraries}" STREQUAL "${UNDERC_LIBFFI_PROBED_CANDIDATE}")
        unset(${probe_var} CACHE)
        set(UNDERC_LIBFFI_PROBED_CANDIDATE "${probe_includes}|${probe_libraries}"
            CACHE INTERNAL "libffi candidate last link-probed")
    endif()
    include(CheckCXXSourceCompiles)
    set(CMAKE_REQUIRED_INCLUDES ${probe_includes})
    set(CMAKE_REQUIRED_LIBRARIES ${probe_libraries})
    check_cxx_source_compiles("
#include <ffi.h>
int main() {
    ffi_cif cif;
    ffi_type *args[1];
    args[0] = &ffi_type_pointer;
    ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, args);
    return 0;
}
" ${probe_var})
    unset(CMAKE_REQUIRED_INCLUDES)
    unset(CMAKE_REQUIRED_LIBRARIES)
endmacro()

# An imported target from a libffi CMake package is reduced to its own file and
# include directory.  underc is an installed, exported library: an imported
# target name recorded in its link interface does not exist in a consumer's
# project, and the consumer then fails with "cannot find -lsome::target".
function(underc_imported_library_location target out_location out_includes)
    set(location "")
    foreach(property IMPORTED_LOCATION IMPORTED_LOCATION_RELEASE
            IMPORTED_LOCATION_NOCONFIG IMPORTED_LOCATION_RELWITHDEBINFO
            IMPORTED_LOCATION_MINSIZEREL IMPORTED_LOCATION_DEBUG)
        get_target_property(candidate ${target} ${property})
        if(candidate)
            set(location "${candidate}")
            break()
        endif()
    endforeach()
    get_target_property(includes ${target} INTERFACE_INCLUDE_DIRECTORIES)
    if(NOT includes)
        set(includes "")
    endif()
    set(${out_location} "${location}" PARENT_SCOPE)
    set(${out_includes} "${includes}" PARENT_SCOPE)
endfunction()

set(UNDERC_LIBFFI_INCLUDE_DIRS "")
set(UNDERC_LIBFFI_LINK_LIBRARIES "")
# Half of the pair is never enough, and silently falling back to a discovered
# libffi would ignore the half that was given.  (On Windows find_path and
# find_library fill in whichever half is missing, which is their documented
# job there, so this applies to the Unix search only.)
if(UCL_LIBFFI AND (LIBFFI_INCLUDE_DIR OR LIBFFI_LIBRARY) AND NOT WIN32)
    if(NOT LIBFFI_INCLUDE_DIR OR NOT LIBFFI_LIBRARY)
        message(FATAL_ERROR
            "LIBFFI_INCLUDE_DIR and LIBFFI_LIBRARY must be given together.  "
            "LIBFFI_INCLUDE_DIR='${LIBFFI_INCLUDE_DIR}', "
            "LIBFFI_LIBRARY='${LIBFFI_LIBRARY}'.")
    endif()
endif()
if(UCL_LIBFFI AND WIN32)
    find_path(LIBFFI_INCLUDE_DIR NAMES ffi.h)
    find_library(LIBFFI_LIBRARY NAMES ffi libffi)
    if(LIBFFI_INCLUDE_DIR AND LIBFFI_LIBRARY)
        underc_probe_libffi(UNDERC_LIBFFI_LINKS "${LIBFFI_INCLUDE_DIR}" "${LIBFFI_LIBRARY}")
    else()
        set(UNDERC_LIBFFI_LINKS FALSE)
    endif()
    if(NOT UNDERC_LIBFFI_LINKS)
        if(LIBFFI_LIBRARY)
            set(UNDERC_LIBFFI_PROBLEM "libffi was found at ${LIBFFI_LIBRARY} but cannot be linked by this toolchain, which targets ${UNDERC_HOST_BITS}-bit code")
        else()
            set(UNDERC_LIBFFI_PROBLEM "no libffi was found")
        endif()
        if(UNDERC_HOST_BITS EQUAL 64)
            message(FATAL_ERROR "UCL_LIBFFI=ON but ${UNDERC_LIBFFI_PROBLEM}.  A 64-bit Windows build has no built-in native dispatcher to fall back on.  Point CMAKE_PREFIX_PATH at a libffi built for the same architecture as the compiler in this environment, or name it with -DLIBFFI_INCLUDE_DIR and -DLIBFFI_LIBRARY.")
        endif()
        message(WARNING "UCL_LIBFFI=ON but ${UNDERC_LIBFFI_PROBLEM}.  Falling back to the built-in 32-bit native dispatcher.  Variadic natives and by-value aggregate arguments are unavailable in that mode; point CMAKE_PREFIX_PATH at a matching libffi to restore them.")
        set(UCL_LIBFFI OFF)
    else()
        set(UNDERC_LIBFFI_INCLUDE_DIRS "${LIBFFI_INCLUDE_DIR}")
        set(UNDERC_LIBFFI_LINK_LIBRARIES "${LIBFFI_LIBRARY}")
        message(STATUS "UnderC: libffi from ${LIBFFI_LIBRARY}")
    endif()
elseif(UCL_LIBFFI)
    set(UNDERC_LIBFFI_ORIGIN "")
    if(LIBFFI_INCLUDE_DIR AND LIBFFI_LIBRARY)
        set(UNDERC_LIBFFI_INCLUDE_DIRS "${LIBFFI_INCLUDE_DIR}")
        set(UNDERC_LIBFFI_LINK_LIBRARIES "${LIBFFI_LIBRARY}")
        set(UNDERC_LIBFFI_ORIGIN "${LIBFFI_LIBRARY} (given as LIBFFI_INCLUDE_DIR/LIBFFI_LIBRARY)")
    endif()
    # A CMake package, if libffi was built with one (see
    # github.com/mathematechde/libffi).  Its imported target is reduced to a
    # plain file so the underc export stays usable by consumers.
    if(NOT UNDERC_LIBFFI_ORIGIN)
        # Package name and target name both vary between libffi CMake ports,
        # so try the spellings that are actually in use rather than one.
        find_package(libffi CONFIG QUIET)
        if(NOT libffi_FOUND)
            find_package(ffi CONFIG QUIET)
        endif()
        foreach(UNDERC_LIBFFI_TARGET libffi::libffi libffi::ffi ffi::ffi ffi::libffi libffi ffi)
            if(TARGET ${UNDERC_LIBFFI_TARGET})
                underc_imported_library_location(${UNDERC_LIBFFI_TARGET}
                    UNDERC_LIBFFI_TARGET_FILE UNDERC_LIBFFI_TARGET_INCLUDES)
                set(UNDERC_LIBFFI_INCLUDE_DIRS "${UNDERC_LIBFFI_TARGET_INCLUDES}")
                if(UNDERC_LIBFFI_TARGET_FILE)
                    set(UNDERC_LIBFFI_LINK_LIBRARIES "${UNDERC_LIBFFI_TARGET_FILE}")
                    set(UNDERC_LIBFFI_ORIGIN "${UNDERC_LIBFFI_TARGET_FILE} (CMake package libffi)")
                else()
                    set(UNDERC_LIBFFI_LINK_LIBRARIES ${UNDERC_LIBFFI_TARGET})
                    set(UNDERC_LIBFFI_ORIGIN "CMake package target ${UNDERC_LIBFFI_TARGET}")
                endif()
                break()
            endif()
        endforeach()
    endif()
    # pkg-config.  The module's own libraries are taken as absolute file paths
    # for the same reason: PkgConfig::<name> is an imported target that does
    # not exist in an installed consumer's project.
    if(NOT UNDERC_LIBFFI_ORIGIN)
        find_package(PkgConfig QUIET)
        if(PKG_CONFIG_FOUND)
            pkg_check_modules(UNDERC_PC_LIBFFI QUIET libffi)
            if(UNDERC_PC_LIBFFI_FOUND)
                set(UNDERC_LIBFFI_INCLUDE_DIRS ${UNDERC_PC_LIBFFI_INCLUDE_DIRS})
                if(UNDERC_PC_LIBFFI_LINK_LIBRARIES)
                    set(UNDERC_LIBFFI_LINK_LIBRARIES ${UNDERC_PC_LIBFFI_LINK_LIBRARIES})
                else()
                    set(UNDERC_LIBFFI_LINK_LIBRARIES ${UNDERC_PC_LIBFFI_LIBRARIES})
                    foreach(UNDERC_LIBFFI_DIR IN LISTS UNDERC_PC_LIBFFI_LIBRARY_DIRS)
                        list(APPEND UNDERC_LIBFFI_LINK_LIBRARIES "-L${UNDERC_LIBFFI_DIR}")
                    endforeach()
                endif()
                set(UNDERC_LIBFFI_ORIGIN "${UNDERC_LIBFFI_LINK_LIBRARIES} (pkg-config libffi ${UNDERC_PC_LIBFFI_VERSION})")
            endif()
        endif()
    endif()
    # Last resort: the ordinary find_* sweep, which also honours
    # CMAKE_PREFIX_PATH.  This fills the same LIBFFI_INCLUDE_DIR and
    # LIBFFI_LIBRARY cache entries the caller may set by hand.
    if(NOT UNDERC_LIBFFI_ORIGIN)
        find_path(LIBFFI_INCLUDE_DIR NAMES ffi.h)
        find_library(LIBFFI_LIBRARY NAMES ffi libffi)
        if(LIBFFI_INCLUDE_DIR AND LIBFFI_LIBRARY)
            set(UNDERC_LIBFFI_INCLUDE_DIRS "${LIBFFI_INCLUDE_DIR}")
            set(UNDERC_LIBFFI_LINK_LIBRARIES "${LIBFFI_LIBRARY}")
            set(UNDERC_LIBFFI_ORIGIN "${LIBFFI_LIBRARY} (found by find_library)")
        endif()
    endif()
    if(NOT UNDERC_LIBFFI_ORIGIN)
        message(FATAL_ERROR
            "UCL_LIBFFI=ON but no libffi was found: no libffi CMake package, no "
            "pkg-config module, and no ffi.h/libffi on the default search "
            "paths.  Name an existing libffi explicitly with "
            "-DLIBFFI_INCLUDE_DIR=<dir> -DLIBFFI_LIBRARY=<file>, add its "
            "prefix to CMAKE_PREFIX_PATH, or configure with -DUCL_LIBFFI=OFF "
            "to use the built-in native dispatcher where one exists.")
    endif()
    underc_probe_libffi(UNDERC_LIBFFI_LINKS
        "${UNDERC_LIBFFI_INCLUDE_DIRS}" "${UNDERC_LIBFFI_LINK_LIBRARIES}")
    if(NOT UNDERC_LIBFFI_LINKS)
        message(FATAL_ERROR
            "UCL_LIBFFI=ON and libffi was located (${UNDERC_LIBFFI_ORIGIN}), "
            "but a program using it cannot be compiled and linked by this "
            "toolchain, which targets ${UNDERC_HOST_BITS}-bit code.  See "
            "${CMAKE_BINARY_DIR}/CMakeFiles/CMakeError.log, and name a "
            "matching libffi with -DLIBFFI_INCLUDE_DIR and -DLIBFFI_LIBRARY.")
    endif()
    message(STATUS "UnderC: libffi from ${UNDERC_LIBFFI_ORIGIN}")
endif()
if(UCL_LIBFFI)
    target_compile_definitions(underc PRIVATE UCL_LIBFFI=1)
    if(UNDERC_LIBFFI_INCLUDE_DIRS)
        target_include_directories(underc PRIVATE ${UNDERC_LIBFFI_INCLUDE_DIRS})
    endif()
    target_link_libraries(underc PUBLIC ${UNDERC_LIBFFI_LINK_LIBRARIES})
endif()
if(UCL_DISABLE_NATIVE_ABI)
    target_compile_definitions(underc PRIVATE UCL_DISABLE_NATIVE_ABI=1)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(underc PRIVATE "$<$<NOT:$<CONFIG:Debug>>:-O1>")
    if(UCL_STRICT_CONVERSIONS)
        target_compile_options(underc PRIVATE -Wconversion -Wsign-conversion)
    endif()
    if(UCL_SANITIZERS)
        target_compile_options(underc PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(underc PUBLIC -fsanitize=address,undefined)
    endif()
endif()
if(UCL_USE_READLINE)
    find_path(READLINE_INCLUDE_DIR NAMES readline/readline.h REQUIRED)
    find_library(READLINE_LIBRARY NAMES readline REQUIRED)
    find_package(Curses REQUIRED)
    target_compile_definitions(underc PRIVATE _USE_READLINE)
    target_include_directories(underc PRIVATE "${READLINE_INCLUDE_DIR}" ${CURSES_INCLUDE_DIRS})
    target_link_libraries(underc PUBLIC "${READLINE_LIBRARY}" ${CURSES_LIBRARIES})
endif()
if(CMAKE_DL_LIBS)
    target_link_libraries(underc PUBLIC "${CMAKE_DL_LIBS}")
endif()
set_target_properties(underc PROPERTIES OUTPUT_NAME underc VERSION ${PROJECT_VERSION} SOVERSION 1)

# UCRI self-imports resolve names in the running process.  Keep the manifest
# address-free so it remains valid with PIE, ASLR, and 64-bit pointers.
set(UNDERC_SELFIMP_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../lib/uclr/self.imp"
    CACHE FILEPATH "Output path for the generated UCRI self-import manifest")
find_program(UNDERC_AWK_EXECUTABLE NAMES awk gawk)
if(CMAKE_NM AND UNDERC_AWK_EXECUTABLE)
    add_custom_command(
        OUTPUT "${UNDERC_SELFIMP_OUTPUT}"
        COMMAND "${CMAKE_COMMAND}"
            "-DNM_TOOL=${CMAKE_NM}"
            "-DAWK_TOOL=${UNDERC_AWK_EXECUTABLE}"
            "-DINPUT_FILE=$<TARGET_FILE:underc>"
            "-DAWK_SCRIPT=${CMAKE_CURRENT_SOURCE_DIR}/build/xnames.awk"
            "-DOUTPUT_FILE=${UNDERC_SELFIMP_OUTPUT}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/build/generate-selfimp.cmake"
        DEPENDS underc "${CMAKE_CURRENT_SOURCE_DIR}/build/xnames.awk"
            "${CMAKE_CURRENT_SOURCE_DIR}/build/generate-selfimp.cmake"
        COMMENT "Generating portable UCRI self-import manifest"
        VERBATIM)
    add_custom_target(selfimp DEPENDS "${UNDERC_SELFIMP_OUTPUT}")
else()
    add_custom_target(selfimp
        COMMAND "${CMAKE_COMMAND}" -E echo
            "selfimp requires nm and awk-compatible tools"
        COMMAND "${CMAKE_COMMAND}" -E false
        VERBATIM)
endif()

# dlsym(NULL, ...) can only see symbols from a statically linked consumer when
# the executable exports them. Shared-library consumers are harmlessly covered.
if(UNIX AND NOT APPLE)
    target_link_options(underc INTERFACE "-Wl,--export-dynamic")
elseif(APPLE)
    target_link_options(underc INTERFACE "-Wl,-export_dynamic")
endif()

if(BUILD_TESTING)
    add_executable(underc-regression-runner "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/runner.cpp")
    target_link_libraries(underc-regression-runner PRIVATE underc)
    add_executable(underc-embed-binding-test
        "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/embed-binding.cpp")
    target_link_libraries(underc-embed-binding-test PRIVATE underc)
    add_executable(underc-load-test
        "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/uc-load.cpp")
    target_link_libraries(underc-load-test PRIVATE underc)
    add_executable(underc-home-dir-api-test
        "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/home-dir-api.cpp")
    target_link_libraries(underc-home-dir-api-test PRIVATE underc)
    add_executable(underc-native-pocket-string-test
        "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/native-pocket-string.cpp")
    add_executable(underc-basename-handling-test
        "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/basename-handling.cpp")
    target_link_libraries(underc-basename-handling-test PRIVATE underc)
    target_include_directories(underc-basename-handling-test PRIVATE
        "${UNDERC_INCLUDE_ROOT}" "${UNDERC_PUBLIC_INCLUDE_DIR}")
    add_executable(underc-public-headers-test
        "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/public-headers.cpp")
    target_link_libraries(underc-public-headers-test PRIVATE underc)
    # Deliberately not linked against underc: this stands in for a consumer
    # that only has the installed headers, and so must not inherit the
    # interpreter's PUBLIC UNDERC_VM_BITS definition.
    add_executable(underc-host-abi-width-test
        "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/host-abi-width.cpp")
    target_include_directories(underc-host-abi-width-test PRIVATE
        "${UNDERC_INCLUDE_ROOT}" "${UNDERC_GENERATED_INCLUDE_DIR}")
    set(UNDERC_TEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
    add_test(NAME embed-variable-binding COMMAND underc-embed-binding-test)
    set_tests_properties(embed-variable-binding PROPERTIES
        ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}" TIMEOUT 15)
    add_test(NAME embed-source-loading COMMAND underc-load-test)
    set_tests_properties(embed-source-loading PROPERTIES
        WORKING_DIRECTORY "${UNDERC_TEST_ROOT}"
        ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}"
        PASS_REGULAR_EXPRESSION "Hello from underc" TIMEOUT 15)
    add_test(NAME home-dir-path-api
        COMMAND underc-home-dir-api-test "${UNDERC_TEST_ROOT}")
    set_tests_properties(home-dir-path-api PROPERTIES
        ENVIRONMENT "UC_HOME=" PASS_REGULAR_EXPRESSION "home-dir-api-ok" TIMEOUT 15)
    add_test(NAME native-pocket-string-api COMMAND underc-native-pocket-string-test)
    set_tests_properties(native-pocket-string-api PROPERTIES
        PASS_REGULAR_EXPRESSION "native-pocket-string-ok" TIMEOUT 15)
    add_test(NAME basename-handling COMMAND underc-basename-handling-test)
    set_tests_properties(basename-handling PROPERTIES
        PASS_REGULAR_EXPRESSION "basename-handling-ok" TIMEOUT 15)
    add_test(NAME public-header-layout COMMAND underc-public-headers-test)
    set_tests_properties(public-header-layout PROPERTIES
        PASS_REGULAR_EXPRESSION "public-header-layout=1.5.4" TIMEOUT 15)
    add_test(NAME host-abi-width COMMAND underc-host-abi-width-test)
    set_tests_properties(host-abi-width PROPERTIES
        PASS_REGULAR_EXPRESSION "host-abi-width=${UNDERC_HOST_BITS}" TIMEOUT 15)
    add_test(NAME interactive-default-bootstrap
        COMMAND "${CMAKE_COMMAND}"
            "-DUNDERC_EXECUTABLE=$<TARGET_FILE:underc-regression-runner>"
            "-DUNDERC_TEST_ROOT=${UNDERC_TEST_ROOT}"
            -P "${UNDERC_TEST_ROOT}/regressiontests/interactive-bootstrap.cmake")
    set_tests_properties(interactive-default-bootstrap PROPERTIES TIMEOUT 15)
    function(underc_add_regression name source)
        add_test(NAME "${name}" COMMAND underc-regression-runner
            "${UNDERC_TEST_ROOT}/regressiontests/${source}")
        set_tests_properties("${name}" PROPERTIES
            ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}" TIMEOUT 15)
    endfunction()
    underc_add_regression(runtime-pointer pointer.c)
    underc_add_regression(runtime-printf printf.c)
    underc_add_regression(bundled-c-library-exposure bundled-c-library.cpp)
    set_tests_properties(bundled-c-library-exposure PROPERTIES
        PASS_REGULAR_EXPRESSION
            "gcvt=12.5 bundled-c-library-ok atexit-ok")
    underc_add_regression(bundled-c-library-imports bundled-c-library-imports.cpp)
    set_tests_properties(bundled-c-library-imports PROPERTIES
        PASS_REGULAR_EXPRESSION "bundled-c-library-imports-ok")
    underc_add_regression(runtime-exception-handling exception-handling.cpp)
    set_tests_properties(runtime-exception-handling PROPERTIES
        PASS_REGULAR_EXPRESSION "exception-handling-ok")
    underc_add_regression(object-value-semantics object-value-semantics.cpp)
    set_tests_properties(object-value-semantics PROPERTIES
        PASS_REGULAR_EXPRESSION "object-value-semantics-ok")
    underc_add_regression(runtime-new-in-method runtime-new-in-method.cpp)
    underc_add_regression(runtime-reference-return reference-return.cpp)
    underc_add_regression(type-deep-pointer deep-pointer.cpp)
    add_test(NAME runtime-argv-pointer COMMAND underc-regression-runner
        "${UNDERC_TEST_ROOT}/regressiontests/argv-pointer.cpp" okay)
    set_tests_properties(runtime-argv-pointer PROPERTIES
        ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}" TIMEOUT 15)
    if(UCL_LIBFFI OR UNDERC_HAS_SYSV_X86_64)
        underc_add_regression(native-eight-arguments native-eight-arguments.cpp)
        add_executable(underc-libffi-callback-test
            "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/libffi-callback.cpp")
        target_link_libraries(underc-libffi-callback-test PRIVATE underc)
        add_test(NAME interpreted-native-callback COMMAND underc-libffi-callback-test)
        set_tests_properties(interpreted-native-callback PROPERTIES
            ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}" TIMEOUT 15)
    endif()
    if(UCL_LIBFFI)
        add_executable(underc-native-constant-arguments-test
            "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/native-constant-arguments.cpp")
        target_link_libraries(underc-native-constant-arguments-test PRIVATE underc)
        add_test(NAME native-constant-arguments COMMAND underc-native-constant-arguments-test)
        set_tests_properties(native-constant-arguments PROPERTIES
            ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}"
            PASS_REGULAR_EXPRESSION "native-constant-arguments-ok" TIMEOUT 15)
        add_executable(underc-native-shell-env-test
            "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/native-shell-env.cpp")
        target_link_libraries(underc-native-shell-env-test PRIVATE underc)
        add_test(NAME native-shell-env COMMAND underc-native-shell-env-test)
        set_tests_properties(native-shell-env PROPERTIES
            ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}"
            PASS_REGULAR_EXPRESSION "native-shell-env-ok" TIMEOUT 15)
        add_executable(underc-libffi-aggregate-test
            "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/libffi-aggregate.cpp")
        target_link_libraries(underc-libffi-aggregate-test PRIVATE underc)
        add_test(NAME libffi-aggregate-by-value COMMAND underc-libffi-aggregate-test)
        set_tests_properties(libffi-aggregate-by-value PROPERTIES
            ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}" TIMEOUT 15)
        add_test(NAME example-uccalc COMMAND underc-regression-runner
            "${UNDERC_TEST_ROOT}/examples/uccalc.cpp" "2 * (3 + 4)")
        set_tests_properties(example-uccalc PROPERTIES
            ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}" PASS_REGULAR_EXPRESSION "14" TIMEOUT 15)
        # *add 1.5.4 hand-named libffi paths - see VERSIONS.md.  Configures a
        # throwaway build tree with pkg-config disabled and libffi given as
        # -DLIBFFI_INCLUDE_DIR/-DLIBFFI_LIBRARY, which is the only mechanism
        # left on a host whose libffi has neither a CMake package nor a .pc
        # file.  Needs concrete paths, so it is skipped when libffi came from a
        # CMake package that exposes only an imported target.
        if(UNIX AND UNDERC_LIBFFI_LINK_LIBRARIES)
            list(GET UNDERC_LIBFFI_LINK_LIBRARIES 0 UNDERC_LIBFFI_TEST_LIBRARY)
            set(UNDERC_LIBFFI_TEST_INCLUDE_DIR "")
            foreach(UNDERC_LIBFFI_DIR IN LISTS UNDERC_LIBFFI_INCLUDE_DIRS)
                if(EXISTS "${UNDERC_LIBFFI_DIR}/ffi.h")
                    set(UNDERC_LIBFFI_TEST_INCLUDE_DIR "${UNDERC_LIBFFI_DIR}")
                    break()
                endif()
            endforeach()
            if(NOT UNDERC_LIBFFI_TEST_INCLUDE_DIR)
                # pkg-config reports no -I at all when ffi.h sits in a default
                # include directory.
                find_path(UNDERC_LIBFFI_HEADER_DIR NAMES ffi.h)
                set(UNDERC_LIBFFI_TEST_INCLUDE_DIR "${UNDERC_LIBFFI_HEADER_DIR}")
            endif()
            if(EXISTS "${UNDERC_LIBFFI_TEST_LIBRARY}"
                    AND EXISTS "${UNDERC_LIBFFI_TEST_INCLUDE_DIR}/ffi.h")
                add_test(NAME libffi-manual-paths
                    COMMAND "${CMAKE_COMMAND}"
                        "-DUNDERC_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
                        "-DLIBFFI_INCLUDE_DIR=${UNDERC_LIBFFI_TEST_INCLUDE_DIR}"
                        "-DLIBFFI_LIBRARY=${UNDERC_LIBFFI_TEST_LIBRARY}"
                        "-DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR}/libffi-manual-paths"
                        "-DGENERATOR=${CMAKE_GENERATOR}"
                        "-DCXX_COMPILER=${CMAKE_CXX_COMPILER}"
                        -P "${UNDERC_TEST_ROOT}/regressiontests/libffi-manual-paths.cmake")
                set_tests_properties(libffi-manual-paths PROPERTIES TIMEOUT 300)
            endif()
        endif()
    endif()
    underc_add_regression(grammar-bitwise-or bitwise-or.c)
    underc_add_regression(grammar-bitwise-precedence bitwise-precedence.cpp)
    underc_add_regression(grammar-switch-in-function switch-in-function.cpp)
    underc_add_regression(grammar-member-template member-template.cpp)
    underc_add_regression(iso-c-keywords iso-c-keywords.c)
    underc_add_regression(iso-cpp-keywords iso-cpp-keywords.cpp)
    foreach(UNDERC_OPT_LEVEL RANGE 0 3)
        add_test(NAME "bytecode-optimization-O${UNDERC_OPT_LEVEL}"
            COMMAND underc-regression-runner "-O${UNDERC_OPT_LEVEL}"
                "${UNDERC_TEST_ROOT}/regressiontests/bytecode-optimization.cpp")
        set_tests_properties("bytecode-optimization-O${UNDERC_OPT_LEVEL}" PROPERTIES
            ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}"
            PASS_REGULAR_EXPRESSION "optimized=54" TIMEOUT 15)
    endforeach()
    if(WIN32)
        set(UNDERC_PROCESS_TEST process-directory-listing-windows)
        underc_add_regression(${UNDERC_PROCESS_TEST} process-windows.c)
    else()
        set(UNDERC_PROCESS_TEST process-directory-listing-linux)
        underc_add_regression(${UNDERC_PROCESS_TEST} process-linux.c)
    endif()
    set_tests_properties(${UNDERC_PROCESS_TEST} PROPERTIES
        WORKING_DIRECTORY "${UNDERC_TEST_ROOT}"
        PASS_REGULAR_EXPRESSION "README.md")
    underc_add_regression(enum-compatible enum-redeclaration.cpp)
    underc_add_regression(container-vector-construct uc_vector_construct.cpp)
    underc_add_regression(uclstl-default-search uclstl-search.cpp)
    set_tests_properties(uclstl-default-search PROPERTIES
        PASS_REGULAR_EXPRESSION "uclstl-search-ok")
    underc_add_regression(container-vector-operations vector-operations.cpp)
    underc_add_regression(container-map-insert-destroy map-operations.cpp)
    # *add 1.5.0 heap and frame layout fixes - see VERSIONS.md
    underc_add_regression(local-slot-allocation local-slot-allocation.cpp)
    set_tests_properties(local-slot-allocation PROPERTIES
        PASS_REGULAR_EXPRESSION "local-slot-allocation-ok")
    underc_add_regression(new-array-construction new-array-construction.cpp)
    set_tests_properties(new-array-construction PROPERTIES
        PASS_REGULAR_EXPRESSION "new-array-construction-ok")
    underc_add_regression(container-vector-of-string vector-of-string.cpp)
    set_tests_properties(container-vector-of-string PROPERTIES
        PASS_REGULAR_EXPRESSION "vector-of-string-ok")
    underc_add_regression(container-map-copy-semantics map-copy-semantics.cpp)
    set_tests_properties(container-map-copy-semantics PROPERTIES
        PASS_REGULAR_EXPRESSION "map-copy-semantics-ok")
    underc_add_regression(container-map-of-vector-string map-of-vector-string.cpp)
    set_tests_properties(container-map-of-vector-string PROPERTIES
        PASS_REGULAR_EXPRESSION "map-of-vector-string-ok")
    underc_add_regression(array-allocation-churn array-allocation-churn.cpp)
    set_tests_properties(array-allocation-churn PROPERTIES
        PASS_REGULAR_EXPRESSION "array-allocation-churn-ok" TIMEOUT 120)
    underc_add_regression(abi-layout abi-layout.cpp)
    add_executable(underc-abi-layout-host-test
        "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/abi-layout-host.cpp")
    target_link_libraries(underc-abi-layout-host-test PRIVATE underc)
    add_test(NAME abi-layout-host-comparison COMMAND underc-abi-layout-host-test)
    set_tests_properties(abi-layout-host-comparison PROPERTIES
        ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}" TIMEOUT 15)
    underc_add_regression(ucri-self-import self-import.cpp)
    set_tests_properties(ucri-self-import PROPERTIES
        PASS_REGULAR_EXPRESSION "self-import:")
    add_executable(underc-ucri-bytecode-test
        "${CMAKE_CURRENT_SOURCE_DIR}/../regressiontests/ucri-bytecode.cpp")
    target_link_libraries(underc-ucri-bytecode-test PRIVATE underc)
    add_test(NAME ucri-bytecode-snapshot COMMAND underc-ucri-bytecode-test)
    set_tests_properties(ucri-bytecode-snapshot PROPERTIES
        ENVIRONMENT "UC_HOME=${UNDERC_TEST_ROOT}" TIMEOUT 15)
    underc_add_regression(enum-changed-rejected enum-redeclaration-changed.cpp)
    underc_add_regression(enum-missing-rejected enum-redeclaration-missing.cpp)
    set_tests_properties(enum-changed-rejected enum-missing-rejected PROPERTIES WILL_FAIL TRUE)
endif()

set(UNDERC_PUBLIC_HEADERS
    "${UNDERC_PUBLIC_INCLUDE_DIR}/export.h"
    "${UNDERC_PUBLIC_INCLUDE_DIR}/fblock.h"
    "${UNDERC_PUBLIC_INCLUDE_DIR}/listx.h"
    "${UNDERC_PUBLIC_INCLUDE_DIR}/mstring.h"
    "${UNDERC_PUBLIC_INCLUDE_DIR}/ucdl.h"
    "${UNDERC_PUBLIC_INCLUDE_DIR}/ucembed.h"
    "${UNDERC_PUBLIC_INCLUDE_DIR}/ucri.h"
    "${UNDERC_PUBLIC_INCLUDE_DIR}/vm_types.h"
    "${UNDERC_PUBLIC_INCLUDE_DIR}/xtrace.h")
install(TARGETS underc EXPORT UndercTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${UNDERC_PUBLIC_HEADERS}
    "${UNDERC_GENERATED_INCLUDE_DIR}/underc/version.h"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/underc)
install(DIRECTORY "${UNDERC_UCLSTL_INCLUDE_DIR}/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/underc/uclstl)
install(EXPORT UndercTargets FILE UndercTargets.cmake NAMESPACE Underc::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Underc)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUnderc.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Underc)
install(FILES "${UNDERC_SELFIMP_OUTPUT}" DESTINATION ${CMAKE_INSTALL_LIBDIR}/uclr OPTIONAL)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/uclr/defs.h"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/uclr)
