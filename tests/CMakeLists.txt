add_library(ff INTERFACE)
target_sources(ff INTERFACE ${fatfs_SOURCE_DIR}/source/ff.c)
target_include_directories(ff INTERFACE ${fatfs_SOURCE_DIR}/source)
target_compile_definitions(ff INTERFACE FFCONF_DEF=80386)
target_compile_options(
    ff
    INTERFACE
    -include ${CMAKE_CURRENT_LIST_DIR}/include/custom_ffconf.h
)

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
target_include_directories(nanofi_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
# target_compile_definitions(
#     nanofi_tests
#     PRIVATE
#     FFCONF_DEF=1 # Disable fattime
# )
add_test(NAME nanofi_tests COMMAND nanofi_tests)