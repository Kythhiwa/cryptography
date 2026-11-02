#pragma once
#include <gmpxx.h>
#include <vector>

namespace generate
{

struct TestCase
{
    mpz_class m;
    mpz_class q;
    std::vector<mpz_class> qd;
    double p_theor;
};

mpz_class prime(int bits, gmp_randclass& rng);

mpz_class m_2p1p2(int bits, gmp_randclass& rng,
                  mpz_class& p1_out, mpz_class& p2_out);

std::vector<TestCase> make_cases(const mpz_class& m,
                                 const mpz_class& p1, const mpz_class& p2);

}