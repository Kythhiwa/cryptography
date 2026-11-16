#include "utils.hpp"


namespace utils 
{



int bit_length(const mpz_class& t)
{
    mpz_class x = t;
    int n = 0;
    while (x > 0)
    {
        x >>= 1;
        ++n;
    }
    return n;
}


}
