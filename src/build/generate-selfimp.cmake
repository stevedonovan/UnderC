foreach(required NM_TOOL AWK_TOOL INPUT_FILE AWK_SCRIPT OUTPUT_FILE)
    if(NOT DEFINED ${required} OR "${${required}}" STREQUAL "")
        message(FATAL_ERROR "generate-selfimp.cmake requires ${required}")
    endif()
endforeach()

get_filename_component(output_directory "${OUTPUT_FILE}" DIRECTORY)
file(MAKE_DIRECTORY "${output_directory}")
set(temporary_output "${OUTPUT_FILE}.tmp")

execute_process(
    COMMAND "${NM_TOOL}" -g --defined-only "${INPUT_FILE}"
    COMMAND "${AWK_TOOL}" -f "${AWK_SCRIPT}"
    OUTPUT_FILE "${temporary_output}"
    RESULTS_VARIABLE command_results
    ERROR_VARIABLE command_error)

foreach(command_result IN LISTS command_results)
    if(NOT command_result EQUAL 0)
        file(REMOVE "${temporary_output}")
        message(FATAL_ERROR "Could not generate ${OUTPUT_FILE}: ${command_error}")
    endif()
endforeach()

file(RENAME "${temporary_output}" "${OUTPUT_FILE}")
