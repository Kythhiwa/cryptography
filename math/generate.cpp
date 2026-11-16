#include "generate.hpp"
#include "solovay_strassen.hpp"

#include <stdexcept>
#include <utility>

namespace generate
{

namespace
{

const std::vector<mpz_class> SMALL_PRIMES = {
    mpz_class(3),  mpz_class(5),  mpz_class(7),  mpz_class(11),
    mpz_class(13), mpz_class(17), mpz_class(19), mpz_class(23),
    mpz_class(29), mpz_class(31), mpz_class(37), mpz_class(41)
};

}

mpz_class prime(int bits, gmp_randclass& rng)
{
    while (true)
    {
        mpz_class p = rng.get_z_bits(bits);
        p |= (mpz_class(1) << (bits - 1));
        p |= 1;
        if (util::solovay_strassen(p, 40, rng))
            return p;
    }
}

mpz_class q_from_small_primes(int k, gmp_randclass& rng,
                              std::vector<mpz_class>& qd_out)
{
    const std::size_t n = SMALL_PRIMES.size();
    if (k < 1 || k > n)
        throw std::invalid_argument("k out of range");

    std::vector<std::size_t> idx(n);
    for (std::size_t i = 0; i < n; ++i)
        idx[i] = i;

    // n >= 1
    for (std::size_t i = n - 1; i > 0; --i) 
    {
        const std::size_t j = static_cast<std::size_t>(
            mpz_class(rng.get_z_range(i + 1)).get_ui());
        std::swap(idx[i], idx[j]);
    }

    mpz_class q = 1;
    qd_out.clear();
    qd_out.reserve(k);
    for (std::size_t i = 0; i < k; ++i)
    {
        q *= SMALL_PRIMES[idx[i]];
        qd_out.emplace_back(SMALL_PRIMES[idx[i]]);
    }
    return q;
}

mpz_class m_for_q(const mpz_class& q, int bits, gmp_randclass& rng,
                  mpz_class& R_out)
{
    const int q_bits = utils::bit_length(q);
    const int R_bits = std::max(bits - 1 - q_bits, 8);

    while (true)
    {
        mpz_class R = prime(R_bits, rng);
        mpz_class m = 2 * q * R + 1;
        if (utils::bit_length(m) != bits)
            continue;
        if (util::solovay_strassen(m, 40, rng))
        {
            R_out = R;
            return m;
        }
    }
}

}
