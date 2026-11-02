#include "generate.hpp"
#include "solovay_strassen.hpp"

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

mpz_class m_2p1p2(int bits, gmp_randclass& rng,
                  mpz_class& p1_out, mpz_class& p2_out)
{
    int h = bits / 2;
    if (h < 8) h = 8;
    while (true) {
        mpz_class p1 = prime(h, rng);
        mpz_class p2 = prime(h, rng);
        mpz_class m = 2 * p1 * p2 + 1;
        if (bit_length_local(m) != bits) continue;
        if (util::solovay_strassen(m, 40, rng)) {
            p1_out = p1; p2_out = p2;
            return m;
        }
    }
}

std::vector<TestCase> make_cases(const mpz_class& m,
                                 const mpz_class& p1, const mpz_class& p2)
{
    std::vector<TestCase> cases;

    cases.push_back({
        m, mpz_class(2), { mpz_class(2) }, 0.5
    });
    cases.push_back({
        m, 2 * p1, { mpz_class(2), p1 },
        0.5 * (1.0 - 1.0 / p1.get_d())
    });
    cases.push_back({
        m, m - 1, { mpz_class(2), p1, p2 },
        0.5 * (1.0 - 1.0 / p1.get_d()) * (1.0 - 1.0 / p2.get_d())
    });

    return cases;
}

}