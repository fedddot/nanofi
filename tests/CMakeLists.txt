add_library(ff STATIC ${fatfs_SOURCE_DIR}/source/ff.c)
target_include_directories(ff PUBLIC ${fatfs_SOURCE_DIR}/source)

add_executable(
    nanofi_tests
    ${CMAKE_CURRENT_LIST_DIR}/src/ut_processor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ut_process_group.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ut_fatfs.cpp
)

target_link_libraries(
    nanofi_tests
    PRIVATE
    processor
    process_group
    ff

    gtest
    gtest_main
)

# target_compile_definitions(
#     nanofi_tests
#     PRIVATE
#     FF_FS_NORTC=1 # Disable fattime
# )
add_test(NAME nanofi_tests COMMAND nanofi_tests)