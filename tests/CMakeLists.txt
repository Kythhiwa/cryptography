cmake_minimum_required(VERSION 3.15)
project(Testing)

enable_testing()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

find_library(GMP_LIB NAMES gmp REQUIRED)
find_library(GMPXX_LIB NAMES gmpxx REQUIRED)

add_executable(Testing 
    main.cpp
    test_jacobi.cpp
    test_gcd.cpp
    test_mul_mod.cpp
    test_pow_mod.cpp
    test_solovay_strassen.cpp
    ../math/jacobi.cpp  
    ../math/mod_arith.cpp 
    ../math/solovay_strassen.cpp
)

target_include_directories(Testing PRIVATE
    ../math
)
target_link_libraries(Testing PRIVATE 
    GTest::gtest
    ${GMP_LIB} 
    ${GMPXX_LIB}
)

include(GoogleTest)
gtest_discover_tests(Testing)
