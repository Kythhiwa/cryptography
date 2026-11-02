#include <iostream>
#include <iomanip>
#include <cmath>
#include <gmpxx.h>

#include "generate.hpp"
#include "runners.hpp"

int main()
{
    gmp_randclass rng(gmp_randinit_mt);
    rng.seed(42);

    const double PTarget = 0.95;
    const int M = 1000;

    for (int bits : {32, 64, 128}) {
        mpz_class p1, p2;
        mpz_class m = generate::m_2p1p2(bits, rng, p1, p2);

        std::cout << "\n=== bits = " << bits << " ===\n";
        std::cout << "m = 2*p1*p2 + 1 = " << m << "\n\n";
        std::cout << std::setw(10) << "q"
                  << std::setw(10) << "p_theor"
                  << std::setw(6)  << "N"
                  << std::setw(10) << "P_obs" << "\n";

        for (const auto& tc : generate::make_cases(m, p1, p2)) {
            int N = (int)std::ceil(std::log(1.0 - PTarget) / std::log(1.0 - tc.p_theor));
            double P_obs = runners::run_find_element_with_order(
                tc.q, tc.qd, tc.m, rng, PTarget, M);

            std::cout << std::setw(10) << tc.q.get_str().substr(0, 8)
                      << std::setw(10) << std::fixed << std::setprecision(4) << tc.p_theor
                      << std::setw(6)  << N
                      << std::setw(10) << std::setprecision(4) << P_obs << "\n";
        }
    }

    return 0;
}