add_executable(
    nanofi_tests
    ${CMAKE_CURRENT_LIST_DIR}/src/ut_processor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ut_process_group.cpp
)

target_link_libraries(
    nanofi_tests
    PRIVATE
    processor
    process_group

    gtest
    gtest_main
)
add_test(NAME nanofi_tests COMMAND nanofi_tests)