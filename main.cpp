#include <iostream>
#include <gmpxx.h>

int main() {
    mpz_class a("123456789012345678901234567890");
    mpz_class b("987654321098765432109876543210");
    mpz_class c = a * b;

    std::cout << "Result: " << c << '\n';
    return 0;
}
