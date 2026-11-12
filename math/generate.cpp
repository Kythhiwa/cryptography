#include "generate.hpp"
#include "solovay_strassen.hpp"

#include <stdexcept>
#include <utility>

namespace generate
{

namespace
{

int bit_length_local(const mpz_class& t)
{
    mpz_class x = t; int n = 0;
    while (x > 0) { x >>= 1; ++n; }
    return n;
}

const std::vector<mpz_class> SMALL_PRIMES = {
    mpz_class(3),  mpz_class(5),  mpz_class(7),  mpz_class(11),
    mpz_class(13), mpz_class(17), mpz_class(19), mpz_class(23),
    mpz_class(29), mpz_class(31), mpz_class(37), mpz_class(41)
};

}

mpz_class prime(int bits, gmp_randclass& rng)
{
    while (true) {
        mpz_class p = rng.get_z_bits(bits);
        p |= (mpz_class(1) << (bits - 1));
        p |= 1;
        if (util::solovay_strassen(p, 40, rng)) return p;
    }
}

mpz_class q_from_small_primes(int k, gmp_randclass& rng,
                              std::vector<mpz_class>& qd_out)
{
    int n = (int)SMALL_PRIMES.size();
    if (k < 1 || k > n)
        throw std::invalid_argument("k out of range");

    std::vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = i;
    for (int i = n - 1; i > 0; --i) {
        int j = (int)(mpz_class(rng.get_z_range(i + 1)).get_ui());
        std::swap(idx[i], idx[j]);
    }

    mpz_class q = 1;
    qd_out.clear();
    for (int i = 0; i < k; ++i) {
        q *= SMALL_PRIMES[idx[i]];
        qd_out.push_back(SMALL_PRIMES[idx[i]]);
    }
    return q;
}

mpz_class m_for_q(const mpz_class& q, int bits, gmp_randclass& rng,
                  mpz_class& R_out)
{
    int q_bits = bit_length_local(q);
    int R_bits = bits - 1 - q_bits;
    if (R_bits < 8) R_bits = 8;

    while (true) {
        mpz_class R = prime(R_bits, rng);
        mpz_class m = 2 * q * R + 1;
        if (bit_length_local(m) != bits) continue;
        if (util::solovay_strassen(m, 40, rng)) {
            R_out = R;
            return m;
        }
    }
}

}