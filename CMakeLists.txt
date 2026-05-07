cmake_minimum_required(VERSION 3.16)

project(nanofi C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(processor INTERFACE)
target_include_directories(processor INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(connection INTERFACE)
target_include_directories(connection INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(process_group INTERFACE)
target_include_directories(process_group INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(process_group INTERFACE processor connection)

include(FetchContent)
option(NANOFI_TESTS "Build the project's test suite" ON)
if(NANOFI_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG		 v1.17.0
    )
    FetchContent_MakeAvailable(googletest)
    enable_testing()
endif()

FetchContent_Declare(
    fatfs
    GIT_REPOSITORY  https://github.com/abbrev/fatfs.git
    GIT_TAG         R0.16
)
FetchContent_MakeAvailable(fatfs)

if (NANOFI_TESTS)
    add_subdirectory(tests)
endif()