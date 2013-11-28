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
#include "n.h"

#ifndef NN_H
#define NN_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef word_t * nn_t;

typedef const word_t * nn_src_t;

#define nn_swap(a, b) \
   do { \
      nn_t __t = (a); \
      (a) = (b); \
      (b) = __t; \
   } while (0)

nn_t nn_init(long m);

void nn_clear(nn_t a);

void nn_copyi(nn_t a, nn_src_t b, long m);

void nn_copyd(nn_t a, nn_src_t b, long m);

void nn_zero(nn_t a, long m);

long nn_normalise(nn_t a, long m);

word_t nn_add_m(nn_t a, nn_src_t b, nn_src_t c, long m, word_t ci);

word_t nn_sub_m(nn_t a, nn_src_t b, nn_src_t c, long m, word_t bi);

word_t nn_add_1(nn_t a, nn_src_t b, long m, word_t ci);

word_t nn_sub_1(nn_t a, nn_src_t b, long m, word_t ci);

word_t nn_add(nn_t a, nn_src_t b, long m, nn_src_t c, long n, word_t ci);

word_t nn_sub(nn_t a, nn_src_t b, long m, nn_src_t c, long n, word_t bi);

word_t nn_shl(nn_t a, nn_src_t b, long m, int bits, word_t ci);

word_t nn_shr(nn_t a, nn_src_t b, long m, int bits, word_t ci);

int nn_cmp(nn_t a, nn_src_t b, long m);

word_t nn_neg(nn_t a, nn_src_t b, long m, word_t ci);

word_t nn_mul_1(nn_t a, nn_src_t b, long m, word_t c, word_t ci);

word_t nn_addmul_1(nn_t a, nn_src_t b, long m, word_t c, word_t ci);

word_t nn_submul_1(nn_t a, nn_src_t b, long m, word_t c, word_t bi);

word_t nn_divrem_1(nn_t q, nn_t a, long m, word_t n, word_t ci);

void nn_randbits(nn_t a, rand_t state, long bits);

void nn_mul_classical(nn_t r, nn_src_t a, long m1, nn_src_t b, long m2);

void nn_mul(nn_t r, nn_src_t a, long m, nn_src_t b, long n);

word_t nn_divrem_classical(nn_t q, nn_t a, long m, nn_src_t d, long n, word_t ci);

void nn_divrem(nn_t q, nn_t a, long m, nn_src_t d, long n);

void nn_div(nn_t q, nn_t a, long m, nn_src_t d, long n);

long nn_gcd(nn_t g, nn_t a, long m, nn_t b, long n);

void nn_mul_kara(nn_t p, nn_src_t a, long m, nn_src_t b, long n);

char * nn_get_str(nn_t a, long m);

long nn_set_str(nn_t a, long * len, const char * str);

#ifdef __cplusplus
 }
#endif

#endif
