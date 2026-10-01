cmake_minimum_required(VERSION 3.16)

project(oop_midsem_practice LANGUAGES CXX)

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

enable_testing()
include(GoogleTest)

function(configure_practice_target target)
    target_compile_features(${target} PRIVATE cxx_std_17)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

# These are deliberately separate targets. Attempt one question at a time;
# the starter implementations are expected to have failing tests until solved.
add_library(day_contract
    01_day_contract/src/Day.cpp
)
target_include_directories(day_contract PUBLIC 01_day_contract/include)
configure_practice_target(day_contract)

add_executable(day_contract_tests 01_day_contract/tests/DayTest.cpp)
target_link_libraries(day_contract_tests PRIVATE day_contract GTest::gtest_main)
configure_practice_target(day_contract_tests)
gtest_discover_tests(day_contract_tests)

add_library(shape_polymorphism
    02_shape_polymorphism/src/Shape.cpp
    02_shape_polymorphism/src/Circle.cpp
    02_shape_polymorphism/src/Rectangle.cpp
    02_shape_polymorphism/src/ShapeCatalog.cpp
)
target_include_directories(shape_polymorphism PUBLIC 02_shape_polymorphism/include)
configure_practice_target(shape_polymorphism)

add_executable(shape_polymorphism_tests 02_shape_polymorphism/tests/ShapeTest.cpp)
target_link_libraries(shape_polymorphism_tests PRIVATE shape_polymorphism GTest::gtest_main)
configure_practice_target(shape_polymorphism_tests)
gtest_discover_tests(shape_polymorphism_tests)

add_library(wallet_audit
    03_wallet_audit/src/Transaction.cpp
    03_wallet_audit/src/Wallet.cpp
    03_wallet_audit/src/WalletAnalyzer.cpp
)
target_include_directories(wallet_audit PUBLIC 03_wallet_audit/include)
configure_practice_target(wallet_audit)

add_executable(wallet_audit_tests 03_wallet_audit/tests/WalletTest.cpp)
target_link_libraries(wallet_audit_tests PRIVATE wallet_audit GTest::gtest_main)
configure_practice_target(wallet_audit_tests)
gtest_discover_tests(wallet_audit_tests)

add_library(number_duel_practice
    04_number_duel/src/Player.cpp
    04_number_duel/src/NumberDuelGame.cpp
)
target_include_directories(number_duel_practice PUBLIC 04_number_duel/include)
configure_practice_target(number_duel_practice)

add_executable(number_duel_practice_tests 04_number_duel/tests/NumberDuelTest.cpp)
target_link_libraries(number_duel_practice_tests PRIVATE number_duel_practice GTest::gtest_main)
configure_practice_target(number_duel_practice_tests)
gtest_discover_tests(number_duel_practice_tests)
