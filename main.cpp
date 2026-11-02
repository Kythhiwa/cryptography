#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <vector>
#include <gmpxx.h>

#include "generate.hpp"
#include "runners.hpp"

int main()
{
    gmp_randclass rng(gmp_randinit_mt);
    rng.seed(42);

    std::ofstream summary("summary.csv");
    std::ofstream hist_csv("rounds.csv");
    summary  << "bits,q,p_theor,N,P_actual,P_obs\n";
    hist_csv << "bits,q,R,N_R\n";

    const double PTarget = 0.95;

    for (int bits : {32, 64, 128}) {
        mpz_class p1, p2;
        mpz_class m = generate::m_2p1p2(bits, rng, p1, p2);

        for (const auto& tc : generate::make_cases(m, p1, p2)) {
            int N = runners::count_N(tc.q, tc.qd, PTarget);
            double P_actual = 1.0 - std::pow(1.0 - tc.p_theor, N);

            std::vector<int> rounds;
            double P_obs = runners::run_find_element_with_order(
                tc.q, tc.qd, tc.m, rng, PTarget, 1000, rounds, 50);

            summary << bits << "," << tc.q << "," << tc.p_theor << ","
                    << N << "," << P_actual << "," << P_obs << "\n";

            std::map<int,int> h;
            for (int R : rounds) h[R]++;
            for (auto& [R, cnt] : h)
                hist_csv << bits << "," << tc.q << "," << R << "," << cnt << "\n";
        }
    }

    std::cout << "written summary.csv, rounds.csv\n";
    return 0;
}