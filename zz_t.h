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

#ifndef ZZ_H
#define ZZ_H

#include "common.h"
#include "word.h"
#include "nn_t.h"

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{
   nn_t n;
   long size;
   long alloc;
} zz_struct;

typedef zz_struct zz_t[1];

typedef zz_struct * zz_ptr;

typedef const zz_struct * zz_srcptr;

#define ZZ_SWAP(a, b)      \
   do {                    \
      zz_srcptr __t = a;   \
      a = b;               \
      b = __t;             \
   } while (0)

#define ZZ_ORDER(a, an, b, bn) \
   do {                        \
      if (an < bn) {           \
         SWAP(an, bn);         \
         ZZ_SWAP(a, b);        \
      }                        \
   } while (0)

/**********************************************************************
 
    Memory management

**********************************************************************/

void zz_init(zz_ptr r);

void zz_clear(zz_ptr r);

void zz_fit(zz_ptr r, long m);

void zz_normalise(zz_ptr r);

/**********************************************************************
 
    Basic manipulation

**********************************************************************/
void zz_set_1(zz_ptr r, long c);

int zz_equal_1(zz_srcptr r, long c);

int zz_cmp(zz_srcptr a, zz_srcptr b);

int zz_cmp_1(zz_srcptr a, long b);

int zz_cmpabs(zz_srcptr a, zz_srcptr b);

int zz_is_zero(zz_srcptr r);

/**********************************************************************
 
    Basic manipulation

**********************************************************************/

void zz_randbits(zz_ptr a, rand_t state, long bits);

/**********************************************************************
 
    Linear functions

**********************************************************************/

void zz_copy(zz_ptr a, zz_srcptr b);

void zz_swap(zz_ptr a, zz_ptr b);

void zz_zero(zz_ptr a);

void zz_add(zz_ptr r, zz_srcptr a, zz_srcptr b);

void zz_sub(zz_ptr r, zz_srcptr a, zz_srcptr b);

void zz_add_1(zz_ptr r, zz_srcptr a, word_t c);

void zz_sub_1(zz_ptr r, zz_srcptr a, word_t c);

void zz_mul_2exp(zz_ptr r, zz_srcptr a, long exp);

void zz_div_2exp(zz_ptr r, zz_srcptr a, long exp);

int zz_cmp(zz_srcptr a, zz_srcptr b);

void zz_neg(zz_ptr r, zz_srcptr a);

void zz_mul_1(zz_ptr r, zz_srcptr a, word_t c);

long zz_divrem_1(zz_ptr q, zz_srcptr a, long b);

void zz_shr_1(zz_ptr r, zz_srcptr a, long bits);

/**********************************************************************
 
    Quadratic functions

**********************************************************************/

void zz_mul(zz_t ptr, zz_srcptr a, zz_srcptr b);

void zz_divrem(zz_ptr q, zz_ptr r, zz_srcptr a, zz_srcptr b);

void zz_larem(zz_ptr r, zz_srcptr a, zz_srcptr b);

void zz_div(zz_ptr q, zz_srcptr a, zz_srcptr b);

void zz_gcd(zz_ptr q, zz_srcptr a, zz_srcptr b);

/**********************************************************************
 
    Input/output

**********************************************************************/

char * zz_get_str(zz_srcptr a);

long zz_set_str(zz_t a, const char * str);

#ifdef __cplusplus
 }
#endif

#endif
