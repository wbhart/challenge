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

#include <stdlib.h>
#include "zz.h"

/**********************************************************************
 
    Memory management

**********************************************************************/

void zz_init(zz_ptr r)
{
   r->n = NULL;
   r->size = 0;
   r->alloc = 0;
}

void zz_clear(zz_ptr r)
{
   free(r->n);
}

void zz_fit(zz_ptr r, long m)
{
   if (r->alloc < m) {
      r->n = (nn_t) realloc(r->n, sizeof(nn_t)*m);
      r->alloc = m;
   }
}

void zz_normalise(zz_ptr r)
{
   if (r->size < 0)
      r->size = -nn_normalise(r->n, -r->size);
   else
      r->size = nn_normalise(r->n, r->size);
}

/**********************************************************************
 
    Basic manipulation

**********************************************************************/

void zz_set_1(zz_ptr r, long c)
{
   if (c) {
      zz_fit(r, 1);
      r->n[0] = ABS(c);
      r->size = c >= 0 ? 1 : -1;
   } else
      r->size = 0;
}

int zz_equal_1(zz_srcptr r, long c)
{
   if (c == 0)
      return r->size == 0;
   else if (c > 0)
      return r->size == 1 && r->n[0] == c;
   else
      return r->size == -1 && r->n[0] == -c;
}

int zz_cmp(zz_srcptr a, zz_srcptr b)
{
   long asize = a->size;
   long bsize = b->size;
   int sgn;

   if (asize > bsize)
      return 1;
   else if (asize < bsize)
      return -1;

   sgn = nn_cmp(a->n, b->n, ABS(asize));
   return asize < 0 ? -sgn : sgn;
}

int zz_is_zero(zz_srcptr r)
{
   return r->size == 0;
}

/**********************************************************************
 
    Random

**********************************************************************/

void zz_randbits(zz_ptr a, rand_t state, long bits)
{
   long ubits = ABS(bits);
   long size = (ubits + WORD_BITS - 1)/WORD_BITS;

   zz_fit(a, size);

   nn_randbits(a->n, state, ubits);

   size = nn_normalise(a->n, size);
   a->size = bits < 0 & n_randint(state, 2) ? -size : size;
}

/**********************************************************************
 
    Linear functions

**********************************************************************/

void zz_copy(zz_ptr a, zz_srcptr b)
{
   long usize = ABS(b->size);
   
   if (a != b) {
      zz_fit(a, usize);
      nn_copyi(a->n, b->n, usize);
      a->size = b->size;
   }
}

void zz_swap(zz_ptr a, zz_ptr b)
{
   nn_swap(a->n, b->n);
   SWAP(a->size, b->size);
   SWAP(a->alloc, b->alloc);
}

void zz_zero(zz_ptr a)
{
   a->size = 0;
}

void zz_add(zz_ptr r, zz_srcptr a, zz_srcptr b)
{
   long asize = ABS(a->size);
   long bsize = ABS(b->size);
   long rsize;

   ZZ_ORDER(a, asize, b, bsize);
   
   zz_fit(r, asize + 1);

   if ((a->size ^ b->size) < 0) {
      word_t bi = nn_sub(r->n, a->n, asize, b->n, bsize, 0);
      rsize = a->size;
      
      if (bi) {
         nn_neg(r->n, r->n, asize, 0);
         rsize = -rsize;
      }
   } else {
      r->n[asize] = nn_add(r->n, a->n, asize, b->n, bsize, 0);
      rsize = asize + 1;
      if (a->size < 0) rsize = -rsize;
   }

   r->size = rsize;
   zz_normalise(r);
}

void zz_sub(zz_ptr r, zz_srcptr a, zz_srcptr b)
{
   long asize = ABS(a->size);
   long bsize = ABS(b->size);
   long rsize;
   int sign = (asize < bsize);

   ZZ_ORDER(a, asize, b, bsize);
   
   zz_fit(r, asize + 1);

   if ((a->size ^ b->size) >= 0) {
      word_t bi = nn_sub(r->n, a->n, asize, b->n, bsize, 0);
      rsize = a->size;
      
      if (bi) {
         nn_neg(r->n, r->n, asize, 0);
         rsize = -rsize;
      }
   } else {
      r->n[asize] = nn_add(r->n, a->n, asize, b->n, bsize, 0);
      rsize = asize + 1;
      if (a->size < 0) rsize = -rsize;
   }

   r->size = rsize;
   zz_normalise(r);

   if (sign) r->size = -r->size;
}

void zz_add_1(zz_ptr r, zz_srcptr a, word_t c)
{
   long usize = ABS(a->size);

   zz_fit(r, usize + 1);
   
   if (a->size >= 0) {
      r->n[usize] = nn_add_1(r->n, a->n, usize, c);
      r->size = nn_normalise(r->n, usize + 1);
   } else {
      nn_sub_1(r->n, a->n, usize, c);
      r->size = -nn_normalise(r->n, usize);
   }
}

void zz_sub_1(zz_ptr r, zz_srcptr a, word_t c)
{
   long usize = ABS(a->size);

   zz_fit(r, usize + 1);
   
   if (a->size == 0) {
      r->size = -1;
      r->n[0] = c;
   } else {
      if (a->size < 0) {
         r->n[usize] = nn_add_1(r->n, a->n, usize, c);
         r->size = -nn_normalise(r->n, usize + 1);
      } else {
         nn_sub_1(r->n, a->n, usize, c);
         r->size = nn_normalise(r->n, usize);
      }
   }
}

void zz_mul_2exp(zz_ptr r, zz_srcptr a, long exp)
{
   int bits = exp & (WORD_BITS - 1);
   long words = exp / WORD_BITS;
   long usize = ABS(a->size);
   long rsize;
   word_t ci;

   zz_fit(r, usize + words + (bits != 0));

   if (!bits) {
      nn_copyd(r->n + words, a->n, usize);
      rsize = usize + words;
   } else {
      word_t ci = r->n[usize + words] = nn_shl(r->n + words, a->n, usize, bits, 0);
      rsize = usize + words + (ci != 0);  
   }

   r->size = a->size >= 0 ? rsize : -rsize;
}

void zz_div_2exp(zz_ptr r, zz_srcptr a, long exp)
{
   int bits = exp & (WORD_BITS - 1);
   long words = exp / WORD_BITS;
   long usize = ABS(a->size);
   long rsize = usize - words;
   
   if (rsize <= 0)
      r->size = 0;
   else {
      zz_fit(r, rsize);

      if (bits == 0)
         nn_copyi(r->n, a->n + words, rsize);
      else {
         nn_shr(r->n, a->n + words, rsize, bits, 0);
         rsize -= (r->n[rsize - 1] == 0);  
      }

      r->size = a->size >= 0 ? rsize : -rsize;
   }
}

void zz_neg(zz_ptr r, zz_srcptr a)
{
   if (r != a) {
      long usize = ABS(a->size);
      zz_fit(r, usize);
      
      nn_copyi(r->n, a->n, usize);
   }

   r->size = -a->size;
}

void zz_mul_1(zz_ptr r, zz_srcptr a, word_t c)
{
   long usize = ABS(a->size);
   
   if (c == 0 || usize == 0)
      r->size = 0;
   else
   {
      zz_fit(r, usize + 1);

      r->n[usize] = nn_mul_1(r->n, a->n, usize, c, 0);
      usize += (r->n[usize] != 0);

      r->size = a->size >= 0 ? usize : -usize;
   }
}

/**********************************************************************
 
    Quadratic functions

**********************************************************************/

void zz_mul(zz_ptr r, zz_srcptr a, zz_srcptr b)
{
   long asize = ABS(a->size);
   long bsize = ABS(b->size);
   long rsize = asize + bsize;
   
   if (asize == 0 || bsize == 0)
      rsize = 0;
   else {
      zz_fit(r, rsize);

      ZZ_ORDER(a, asize, b, bsize);

      nn_mul(r->n, a->n, asize, b->n, bsize);
      rsize -= (r->n[rsize - 1] == 0);

      r->size = (a->size ^ b->size) < 0 ? -rsize : rsize;
   }
}

void zz_divrem(zz_ptr q, zz_t r, zz_srcptr a, zz_srcptr b)
{
   long asize = ABS(a->size);
   long bsize = ABS(b->size);
   long rsize = bsize;
   long qsize = asize - bsize + 1;

   zz_copy(r, a);

   if (asize < bsize)
      q->size = 0;
   else {
      zz_fit(q, qsize);
   
      nn_divrem(q->n, r->n, asize, b->n, bsize);
         
      qsize -= q->n[qsize - 1] == 0;
      rsize = nn_normalise(r->n, rsize);

      q->size = (a->size ^ b->size) >= 0 ? qsize : -qsize;
      r->size = a->size >= 0 ? rsize : -rsize;

      if (q->size < 0 && r->size != 0) {
         zz_sub_1(q, q, 1);
         zz_add(r, r, b);
      }
   }
}

void zz_div(zz_ptr q, zz_srcptr a, zz_srcptr b)
{
   long asize = ABS(a->size);
   long bsize = ABS(b->size);
   long rsize = bsize;
   long qsize = asize - bsize + 1;
   int qsign = (a->size ^ b->size);
   zz_t r;

   if (asize < bsize)
      q->size = 0;
   else {
      zz_init(r);
      zz_copy(r, a);

      zz_fit(q, qsize);
   
      if (qsign < 0) {
         nn_divrem(q->n, r->n, asize, b->n, bsize);
         rsize = nn_normalise(r->n, rsize);
      } else
         nn_div(q->n, r->n, asize, b->n, bsize);

      qsize -= q->n[qsize - 1] == 0;
      q->size = qsign >= 0 ? qsize : -qsize;
      
      if (q->size < 0 && rsize != 0)
         zz_sub_1(q, q, 1);

      zz_clear(r);
   }
}

void zz_gcd(zz_ptr g, zz_srcptr a, zz_srcptr b)
{
   long asize = ABS(a->size);
   long bsize = ABS(b->size);
   long size;
   nn_t ta, tb;
   TMP_INIT;

   if (asize == 0)
      zz_copy(g, b);
   else if (bsize == 0)
      zz_copy(g, a);
   else {
      TMP_START;

      ZZ_ORDER(a, asize, b, bsize);

      ta = TMP_ALLOC(asize*sizeof(word_t));
      tb = TMP_ALLOC(bsize*sizeof(word_t));

      nn_copyi(ta, a->n, asize);
      nn_copyi(tb, b->n, bsize);

      zz_fit(g, bsize);
      size = nn_gcd(g->n, ta, asize, tb, bsize);
      
      g->size = (a->size & b->size) < 0 ? -size : size;

      TMP_END;
   }
}

/**********************************************************************
 
    Input/output

**********************************************************************/

char * zz_get_str(zz_srcptr a)
{
   nn_t t;
   long size = ABS(a->size);
   char * str;
   TMP_INIT;
   
   TMP_START;
   
   t = TMP_ALLOC(size*sizeof(word_t));
  
   nn_copyi(t, a->n, size);

   str = nn_get_str(t, size);

   TMP_END;

   return str;
}
