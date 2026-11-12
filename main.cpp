#include <iostream>
#include <gmpxx.h>
#include <stdexcept>

#include "order_finder.hpp"
#include "mod_arith.hpp"
#include "solovay_strassen.hpp"

void check_qd(const mpz_class& q, const std::vector<mpz_class>& qd,
              gmp_randclass& rng)
{
    mpz_class qd_product = 1;
    for (const auto& d : qd)
    {
        if (!util::solovay_strassen(d, 40, rng))
            throw std::invalid_argument("qd element must be prime");
        if (gcd(q, d) != d)
            throw std::invalid_argument("qd element is not a divisor of q");
        qd_product *= d;
    }
    if (qd_product != q)
        throw std::invalid_argument("qd must be exactly the prime divisors of q");
}

int main(int argc, char** argv)
{
    if (argc < 4) {
        std::cerr << "usage: " << argv[0] << " <m> <q> <p1> [p2 ...]\n";
        return 1;
    }

    mpz_class m(argv[1]);
    mpz_class q(argv[2]);

    std::vector<mpz_class> qd;
    for (int i = 3; i < argc; ++i)
        qd.emplace_back(argv[i]);

    gmp_randclass rng(gmp_randinit_mt);
    rng.seed(42);

    try {
        if (m <= 1)
            throw std::invalid_argument("m must be > 1");
        if (q <= 0)
            throw std::invalid_argument("q must be positive");

        check_qd(q, qd, rng);

        if (!util::solovay_strassen(m, 40, rng))
            throw std::invalid_argument("m must be prime");

        if (gcd(q, m - 1) != q)
            throw std::invalid_argument("q must divide m-1");

        auto res = modarith::find_element_with_order(q, qd, m, rng, 200);

        if (res.x == mpz_class(-1))
            std::cout << "not found in 200 rounds\n";
        else
            std::cout << "x = " << res.x
                      << "  (round " << res.round << ")\n";
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}