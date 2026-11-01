#include <iostream>
#include <gmpxx.h>
#include "mod_arith.hpp"

using namespace modarith;

int main() {
    std::cout << mul_mod(mpz_class(7),    mpz_class(8),    mpz_class(13)) << '\n';  // 4
    std::cout << mul_mod(mpz_class(12345),mpz_class(6789), mpz_class(97)) << '\n';  // 30

    std::cout << pow_mod(mpz_class(2),  mpz_class(10), mpz_class(1000)) << '\n';    // 24
    std::cout << pow_mod(mpz_class(2),  mpz_class(0),  mpz_class(100))  << '\n';    // 1
    std::cout << pow_mod(mpz_class(2),  mpz_class(13), mpz_class(100))  << '\n';    // 92
    std::cout << pow_mod(mpz_class(123),mpz_class(456),mpz_class(1000000007)) << '\n';

    std::cout << gcd(mpz_class(12), mpz_class(8))  << '\n';   // 4
    std::cout << gcd(mpz_class(17), mpz_class(5))  << '\n';   // 1
    std::cout << gcd(mpz_class(48), mpz_class(18)) << '\n';   // 6
    std::cout << gcd(mpz_class(0),  mpz_class(5))  << '\n';   // 5

    mpz_class a("123456789012345678901234567890");
    mpz_class b("987654321098765432109876543210");
    mpz_class m("1000000007");
    std::cout << mul_mod(a, b, m) << '\n';
    std::cout << gcd(a, b) << '\n';

    return 0;
}