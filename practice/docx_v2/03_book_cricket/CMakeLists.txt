cmake_minimum_required(VERSION 3.16)

project(docx_v2_book_cricket LANGUAGES CXX)

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

add_library(book_cricket
    src/BookCricketRules.cpp
    src/Innings.cpp
    src/Match.cpp
)
target_include_directories(book_cricket PUBLIC include)

add_executable(book_cricket_tests tests/BookCricketTest.cpp)
target_link_libraries(book_cricket_tests PRIVATE book_cricket GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(book_cricket_tests)
