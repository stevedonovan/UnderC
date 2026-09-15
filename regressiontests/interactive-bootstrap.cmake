if(NOT DEFINED UNDERC_EXECUTABLE OR NOT DEFINED UNDERC_TEST_ROOT)
    message(FATAL_ERROR "UNDERC_EXECUTABLE and UNDERC_TEST_ROOT are required")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env "UC_HOME=${UNDERC_TEST_ROOT}"
        "${UNDERC_EXECUTABLE}"
    WORKING_DIRECTORY "${UNDERC_TEST_ROOT}"
    INPUT_FILE "${UNDERC_TEST_ROOT}/regressiontests/interactive-bootstrap.in"
    RESULT_VARIABLE bootstrap_result
    OUTPUT_VARIABLE bootstrap_output
    ERROR_VARIABLE bootstrap_error
    TIMEOUT 10)

set(bootstrap_log "${bootstrap_output}${bootstrap_error}")
if(NOT bootstrap_result EQUAL 0)
    message(FATAL_ERROR
        "interactive bootstrap exited with ${bootstrap_result}:\n${bootstrap_log}")
endif()
if(NOT bootstrap_log MATCHES "interactive resource bootstrap loaded")
    message(FATAL_ERROR
        "interactive bootstrap did not load the string library:\n${bootstrap_log}")
endif()
if(NOT bootstrap_log MATCHES "Quit session")
    message(FATAL_ERROR
        "interactive bootstrap did not show the compiled-in #help text:\n${bootstrap_log}")
endif()
if(bootstrap_log MATCHES "Cannot find 'string'" OR
        bootstrap_log MATCHES "Cannot open defs.h")
    message(FATAL_ERROR
        "interactive bootstrap reported a definitions error:\n${bootstrap_log}")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env "UC_HOME=${UNDERC_TEST_ROOT}"
        "${UNDERC_EXECUTABLE}" --help
    WORKING_DIRECTORY "${UNDERC_TEST_ROOT}"
    RESULT_VARIABLE command_help_result
    OUTPUT_VARIABLE command_help_output
    ERROR_VARIABLE command_help_error
    TIMEOUT 10)

set(command_help_log "${command_help_output}${command_help_error}")
if(NOT command_help_result EQUAL 0)
    message(FATAL_ERROR
        "--help exited with ${command_help_result}:\n${command_help_log}")
endif()
if(NOT command_help_log MATCHES "Override UC_HOME")
    message(FATAL_ERROR
        "--help did not show the compiled-in command-line help text:\n${command_help_log}")
endif()
