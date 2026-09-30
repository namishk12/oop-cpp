cmake_minimum_required(VERSION 3.16)

project(upi_wallet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(upi_wallet
    src/Transaction.cpp
    src/Wallet.cpp
    src/WalletAnalyzer.cpp
)

target_include_directories(upi_wallet PUBLIC include)

if (MSVC)
    target_compile_options(upi_wallet PRIVATE /W4 /permissive-)
else()
    target_compile_options(upi_wallet PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()

add_executable(upi_wallet_tests
    tests/upi_wallet_tests.cpp
)
target_link_libraries(upi_wallet_tests PRIVATE upi_wallet)

add_test(NAME upi_wallet_tests COMMAND upi_wallet_tests)
