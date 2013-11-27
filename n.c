/*
   Copyright (c) 2013, William Hart
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this
   list of conditions and the following disclaimer in the documentation and/or other
   materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
   SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
   DAMAGE.
*/

#include "n.h"

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

word_t n_bitcount(word_t n)
{
    if (n == 0)
        return 0;
    else
        return WORD_BITS - n_leading_zeroes(n);
}

