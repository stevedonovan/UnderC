# Regression: a libffi named by hand is enough to configure the interpreter.
#
# A libffi installed into its own prefix (a --prefix=/opt/libffi build, say)
# frequently ships neither a CMake package nor a pkg-config .pc file.  Naming
# it with -DLIBFFI_INCLUDE_DIR and -DLIBFFI_LIBRARY must then be enough, and
# must be honoured ahead of any system copy.
#
# Configures a throwaway build tree of src/ with find_package(PkgConfig)
# disabled, so no automatic discovery mechanism is available, and requires the
# configure step to succeed and to report the library it was given.
#
# Required: UNDERC_SOURCE_DIR, LIBFFI_INCLUDE_DIR, LIBFFI_LIBRARY, WORK_DIR.
# Optional: GENERATOR, CXX_COMPILER.
if(NOT DEFINED UNDERC_SOURCE_DIR OR NOT DEFINED LIBFFI_INCLUDE_DIR
        OR NOT DEFINED LIBFFI_LIBRARY OR NOT DEFINED WORK_DIR)
    message(FATAL_ERROR
        "UNDERC_SOURCE_DIR, LIBFFI_INCLUDE_DIR, LIBFFI_LIBRARY and WORK_DIR are required")
endif()

file(REMOVE_RECURSE "${WORK_DIR}")
file(MAKE_DIRECTORY "${WORK_DIR}")

set(configure_command "${CMAKE_COMMAND}" -S "${UNDERC_SOURCE_DIR}" -B "${WORK_DIR}"
    "-DCMAKE_DISABLE_FIND_PACKAGE_PkgConfig=ON"
    "-DLIBFFI_INCLUDE_DIR=${LIBFFI_INCLUDE_DIR}"
    "-DLIBFFI_LIBRARY=${LIBFFI_LIBRARY}"
    "-DBUILD_TESTING=OFF"
    "-DUCL_USE_READLINE=OFF")
if(GENERATOR)
    list(APPEND configure_command -G "${GENERATOR}")
endif()
if(CXX_COMPILER)
    list(APPEND configure_command "-DCMAKE_CXX_COMPILER=${CXX_COMPILER}")
endif()

execute_process(
    COMMAND ${configure_command}
    RESULT_VARIABLE configure_result
    OUTPUT_VARIABLE configure_output
    ERROR_VARIABLE configure_error
    TIMEOUT 300)

set(configure_log "${configure_output}${configure_error}")
if(NOT configure_result EQUAL 0)
    message(FATAL_ERROR
        "configuring with an explicit libffi failed (${configure_result}):\n${configure_log}")
endif()
if(NOT configure_log MATCHES "UnderC: libffi from ${LIBFFI_LIBRARY}")
    message(FATAL_ERROR
        "the explicitly given libffi ${LIBFFI_LIBRARY} was not the one used:\n${configure_log}")
endif()
if(NOT configure_log MATCHES "given as LIBFFI_INCLUDE_DIR/LIBFFI_LIBRARY")
    message(FATAL_ERROR
        "libffi was rediscovered instead of taken from the given paths:\n${configure_log}")
endif()
message(STATUS "libffi-manual-paths-ok")
