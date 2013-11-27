#include "n.h"

/**********************************************************************
 
    Precomputed inverse

**********************************************************************/

word_t n_preinv(word_t n)
{
   dword_t t = (~(dword_t) 0) - (((dword_t) n) << WORD_BITS);
   return t / n;
}

/**********************************************************************
 
    Random functions

**********************************************************************/

#if WORD_BITS == 64

word_t n_randword(rand_t state) 
{   
    state->__rand1 = (state->__rand1 * 13282407956253574709UL + 286824421UL);
    state->__rand2 = (state->__rand2 * 7557322358563246341UL + 286824421UL);

    return (state->__rand1 >> 32) + ((state->__rand2 >> 32) << 32);
}

#else

word_t n_randword(rand_t state) 
{   
    state->__rand1 = (state->__rand1 * 1543932465UL +  1626832771UL);
    state->__rand2 = (state->__rand2 * 2495927737UL +  1626832771UL);

    return (state->__rand1 >> 16) + ((state->__rand2 >> 16) << 16);
}

#endif

word_t n_randint(rand_t state, word_t limit) 
{
   if (limit == 0UL) return n_randword(state);
   else return n_randword(state) % limit;
}

word_t n_randbits(rand_t state, unsigned int bits)
{
   if (bits == 0) return 0UL;
   else return (1UL << (bits - 1)) | n_randint(state, 
                                    (bits == WORD_BITS ? 0 : 1UL << bits));
}
