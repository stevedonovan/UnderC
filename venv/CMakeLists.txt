cmake_minimum_required(VERSION 3.16)

# CMP0091: drive the MSVC runtime library through MSVC_RUNTIME_LIBRARY, so venv
# can force /MD to match the shipped Release /MD underc.lib even in Debug.
cmake_policy(SET CMP0091 NEW)
project(venv VERSION 1.5.4 LANGUAGES C CXX)
include(GNUInstallDirs)

set(CMAKE_C_STANDARD 11)
# Extensions stay on: glibc only declares chroot() and `environ` with
# _DEFAULT_SOURCE active, which strict -std=c11 would switch off.
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 14)

# The interpreter installs FindUnderc.cmake and UndercTargets.cmake under
# <prefix>/${CMAKE_INSTALL_LIBDIR}/cmake/Underc.  Search every prefix the caller
# might point us at: entries on CMAKE_PREFIX_PATH, and the install prefix itself.
set(_UNDERC_SEARCH_PREFIXES ${CMAKE_PREFIX_PATH} "${CMAKE_INSTALL_PREFIX}")
foreach(UNDERC_PREFIX IN LISTS _UNDERC_SEARCH_PREFIXES)
    list(APPEND CMAKE_MODULE_PATH
        "${UNDERC_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cmake/Underc"
        "${UNDERC_PREFIX}/lib/cmake/Underc"
        "${UNDERC_PREFIX}/lib64/cmake/Underc")
endforeach()
find_package(Underc REQUIRED MODULE)

add_executable(venv
    src/main.c
    src/config.c
    src/cmdline.c
    src/process_spawner.c
    src/platform.c
    src/util.c
    src/underc_bridge.cpp
)
set_target_properties(venv PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
target_include_directories(venv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
if(WIN32)
    target_compile_definitions(venv PRIVATE PLATFORM_WINDOWS _CRT_SECURE_NO_WARNINGS)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(venv PRIVATE PLATFORM_LINUX)
endif()
target_link_libraries(venv PRIVATE Underc::underc)
install(TARGETS venv RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
