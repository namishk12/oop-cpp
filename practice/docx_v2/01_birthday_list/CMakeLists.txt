cmake_minimum_required(VERSION 3.16)

project(docx_v2_birthday_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
FetchContent_MakeAvailable(googletest)

add_library(birthday_list
    src/Day.cpp
    src/BirthdayList.cpp
)
target_include_directories(birthday_list PUBLIC include)

add_executable(birthday_list_tests tests/BirthdayListTest.cpp)
target_link_libraries(birthday_list_tests PRIVATE birthday_list GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(birthday_list_tests)
