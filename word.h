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

#include "common.h"

#ifndef N_H
#define N_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(_MSC_VER)
#define n_leading_zeroes __lzcnt
#else
#define n_leading_zeroes __builtin_clzl
#endif

#define n_divrem_21(q, hi, lo, n)                                         \
   do {                                                                   \
      const dword_t __u = ((dword_t) (hi) << WORD_BITS) + (dword_t) (lo); \
      (q) = __u / (n);                                                    \
      (lo) = __u % (n);                                                   \
   } while (0)

#define n_div_21(q, hi, lo, n)                                            \
   do {                                                                   \
      const dword_t __u = ((dword_t) (hi) << WORD_BITS) + (dword_t) (lo); \
      (q) = __u / (n);                                                    \
   } while (0)

word_t n_randword(rand_t state);

word_t n_randint(rand_t state, word_t limit);

word_t n_randbits(rand_t state, unsigned int bits);

word_t n_bitcount(word_t n);

#ifdef __cplusplus
 }
#endif

#endif
