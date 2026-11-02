#include <cmath>

#include "runners.hpp"
#include "order_finder.hpp"
#include "solovay_strassen.hpp"


namespace runners
{
namespace
{

int count_N(const mpz_class& q, const std::vector<mpz_class>& qd, double PTarget)
{
    if (q <= 1)
        return 1;
    double p = 1.0;
    for (const auto& d : qd) {
        double pd = d.get_d();
        p *= (1.0 - 1.0 / pd);
    }
    return (int)std::ceil(std::log(1.0 - PTarget) / std::log(1.0 - p));
}
}

double run_find_element_with_order(const mpz_class& q, const std::vector<mpz_class>& qd, const mpz_class& m,
                                   gmp_randclass& rng, double PTarget, int l)
{
    if (l <= 0)
        throw std::invalid_argument("l must be > 0");
    if (m <= 1)
        throw std::invalid_argument("m must be > 1");
    if (q <= 0)
        throw std::invalid_argument("q must be positive");
    if (gcd(q, m - 1) != q)
        throw std::invalid_argument("q must divide m-1");
    if (!util::solovay_strassen(m, 40, rng))
        throw std::invalid_argument("m must be prime"); // здесь, чтобы не проверять на простоту l раз
    int rounds = count_N(q, qd, PTarget);
    int correct = 0;
    for (int i = 0; i < l; ++i)
    {
        if (modarith::find_element_with_order(q, qd, m, rng, rounds) != mpz_class(-1))
            correct++;
    }
    return (double)correct / l;
}
}
