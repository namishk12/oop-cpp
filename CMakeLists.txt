cmake_minimum_required(VERSION 3.16)

project(oop_cpp LANGUAGES CXX)

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

add_library(oop_core
    src/book/inheritance/Employee.cpp
    src/book/inheritance/Manager.cpp
    src/intro/NumberGuessGame.cpp
    src/intro/Point.cpp
    src/ooad/numberduel/Feedback.cpp
    src/ooad/numberduel/GameSummary.cpp
    src/ooad/numberduel/Guess.cpp
    src/ooad/numberduel/GuessHistory.cpp
    src/ooad/numberduel/NumberDuelGame.cpp
    src/ooad/numberduel/Player.cpp
    src/ooad/numberduel/PlayerProfile.cpp
    src/polymorphism/states/State.cpp
    src/Transaction.cpp
    src/Wallet.cpp
    src/WalletAnalyzer.cpp
)

target_include_directories(oop_core PUBLIC include)

if (MSVC)
    target_compile_options(oop_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(oop_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(intro_demo src/apps/intro_demo.cpp)
target_link_libraries(intro_demo PRIVATE oop_core)

add_executable(number_guess_game src/apps/number_guess_main.cpp)
target_link_libraries(number_guess_game PRIVATE oop_core)

add_executable(employee_tester src/apps/employee_tester.cpp)
target_link_libraries(employee_tester PRIVATE oop_core)

add_executable(states_tester src/apps/states_tester.cpp)
target_link_libraries(states_tester PRIVATE oop_core)

add_executable(number_duel_app src/apps/number_duel_main.cpp)
target_link_libraries(number_duel_app PRIVATE oop_core)

enable_testing()
include(GoogleTest)

add_executable(oop_tests
    tests/upi_wallet_tests.cpp
    tests/number_duel_tests.cpp
    tests/oop_examples_tests.cpp
)
target_link_libraries(oop_tests PRIVATE oop_core GTest::gtest_main)

gtest_discover_tests(oop_tests)
