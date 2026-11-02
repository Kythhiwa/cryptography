cmake_minimum_required(VERSION 3.15)

project(Crypto_lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_library(GMP_LIB NAMES gmp REQUIRED)
find_library(GMPXX_LIB NAMES gmpxx REQUIRED)

add_executable(prog
    main.cpp
    math/mod_arith.cpp
    math/jacobi.cpp
    math/solovay_strassen.cpp
    math/order_finder
)

target_include_directories(prog PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/math
)
target_link_libraries(prog PRIVATE ${GMPXX_LIB} ${GMP_LIB})
