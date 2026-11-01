#pragma once
#include <gmpxx.h>

namespace util
{

bool solovay_strassen(const mpz_class& m, int k, gmp_randclass& rng);

}
