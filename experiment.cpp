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
    summary  << "k,trial,q,p_theor,N,P_actual,P_obs,R_avg\n";
    hist_csv << "k,trial,R,N_R\n";

    const double PTarget = 0.95;
    const int    M       = 1000;
    const int    bits    = 64;
    const int    TRIALS  = 5;
    const int    K_MAX   = 8;

    for (int k = 1; k <= K_MAX; ++k) {
        std::cout << "k = " << k << ":\n";

        for (int t = 0; t < TRIALS; ++t) {
            std::vector<mpz_class> qd;
            mpz_class q = generate::q_from_small_primes(k, rng, qd);

            mpz_class R;
            mpz_class m = generate::m_for_q(q, bits, rng, R);

            double p_theor = 1.0;
            for (auto& d : qd)
                p_theor *= (1.0 - 1.0 / d.get_d());

            int N = (int)std::ceil(std::log(1.0 - PTarget) / std::log(1.0 - p_theor));
            double P_actual = 1.0 - std::pow(1.0 - p_theor, N);

            std::vector<int> rounds;
            double P_obs = runners::run_find_element_with_order(
                q, qd, m, rng, PTarget, M, rounds, 50);

            double R_avg = 0;
            for (int r : rounds) R_avg += r;
            if (!rounds.empty()) R_avg /= (double)rounds.size();

            summary << k << "," << t << "," << q << ","
                    << p_theor << "," << N << ","
                    << P_actual << "," << P_obs << "," << R_avg << "\n";

            std::map<int,int> h;
            for (int r : rounds) h[r]++;
            for (auto& [Rv, cnt] : h)
                hist_csv << k << "," << t << "," << Rv << "," << cnt << "\n";

            std::cout << "  trial " << t
                      << ": q = " << q
                      << ", p = " << p_theor
                      << ", N = " << N
                      << ", P_obs = " << P_obs
                      << ", R_avg = " << R_avg << "\n";
        }
    }

    std::cout << "written summary.csv, rounds.csv\n";
    return 0;
}