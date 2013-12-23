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
#include "nn_t.h"
#ifdef _MSC_VER
#include "malloc.h"
#endif

/**********************************************************************
 
    Linear functions

**********************************************************************/

/* w.b. hart */
void nn_copyi(nn_t a, nn_src_t b, long m)
{
   long i;

   for (i = 0; i < m; i++)
      a[i] = b[i];
}

/* w.b. hart */
void nn_copyd(nn_t a, nn_src_t b, long m)
{
   long i;

   for (i = m - 1; i >= 0; i--)
      a[i] = b[i];
}

/* w.b. hart */
void nn_zero(nn_t a, long m)
{
   long i;

   for (i = 0; i < m; i++)
      a[i] = 0;
}

/* w.b. hart */
long nn_normalise(nn_t a, long m)
{
   while ((m != 0) && (a[m - 1] == 0))
      m--;

   return m;
}

/* w.b. hart */
word_t nn_add_m(nn_t a, nn_src_t b, nn_src_t c, long m, word_t ci)
{
   dword_t t;
   long i;
   
   for (i = 0; i < m; i++) {
      t = (dword_t) b[i] + (dword_t) c[i] + (dword_t) ci;
      a[i] = (word_t) t;
      ci = (t >> WORD_BITS);
   }

   return ci;
}

/* w.b. hart */
word_t nn_sub_m(nn_t a, nn_src_t b, nn_src_t c, long m, word_t bi)
{
   dword_t t;
   long i;
   
   for (i = 0; i < m; i++) {
      t = (dword_t) b[i] - (dword_t) c[i] - (dword_t) bi;
      a[i] = (word_t) t;
      bi = -(sword_t)(t >> WORD_BITS);
   }

   return bi;
}

/* w.b. hart */
word_t nn_add_1(nn_t a, nn_src_t b, long m, word_t ci)
{
   dword_t t;
   long i;

   for (i = 0; i < m && ci != 0; i++) {
      t = (dword_t) b[i] + (dword_t) ci;
      a[i] = (word_t) t;
      ci = (t >> WORD_BITS);
   }

   if (a != b)
      for ( ; i < m; i++)
         a[i] = b[i];

   return ci;
}

/* w.b. hart */
word_t nn_sub_1(nn_t a, nn_src_t b, long m, word_t ci)
{
   dword_t t;
   long i;

   for (i = 0; i < m && ci != 0; i++) {
      t = (dword_t) b[i] - (dword_t) ci;
      a[i] = (word_t) t;
      ci = -(sword_t)(t >> WORD_BITS);
   }

   if (a != b)
      for ( ; i < m; i++)
         a[i] = b[i];

   return ci;
}

/* w.b. hart */
word_t nn_add(nn_t a, nn_src_t b, long m, nn_src_t c, long n, word_t ci)
{
   ci = nn_add_m(a, b, c, n, ci);

   return nn_add_1(a + n, b + n, m - n, ci);
}

/* w.b. hart */
word_t nn_sub(nn_t a, nn_src_t b, long m, nn_src_t c, long n, word_t bi)
{
   bi = nn_sub_m(a, b, c, n, bi);

   return nn_sub_1(a + n, b + n, m - n, bi);
}

/* w.b. hart */
word_t nn_shl(nn_t a, nn_src_t b, long m, int bits, word_t ci)
{
   dword_t t;
   long i;
   
   for (i = 0; i < m; i++) {
      t = (((dword_t) b[i]) << bits);
      a[i] = (word_t) t + ci;
      ci = (t >> WORD_BITS); 
   }

   return ci;
}

/* w.b. hart */
word_t nn_shr(nn_t a, nn_src_t b, long m, int bits, word_t ci)
{
   dword_t t;
   long i;

   bits = WORD_BITS - bits;
   
   for (i = m - 1; i >= 0L; i--) {
      t = (((dword_t) b[i]) << bits);
      a[i] = (t >> WORD_BITS) + ci;
      ci = (word_t) t; 
   }

   return ci;
}

/* w.b. hart */
int nn_cmp(nn_t a, nn_src_t b, long m)
{
   while (m--) {
      if (a[m] != b[m]) {
         if (a[m] > b[m])
            return 1;
         else
            return -1;
      }
   }

   return 0;
}

/* w.b. hart */
word_t nn_neg(nn_t a, nn_src_t b, long m, word_t ci)
{
   dword_t t;
   long i;

   ci = 1 - ci;

   /* -b = ~b + 1 */
   for (i = 0; i < m && ci != 0; i++) {
      t = (dword_t) ~b[i] + (dword_t) ci;
      a[i] = (word_t) t;
      ci = (t >> WORD_BITS);
   }

   /* no more carries, just complement */
   for ( ; i < m; i++)
      a[i] = ~b[i];

   return (word_t) 1 - ci;
}

/* w.b. hart */
word_t nn_mul_1(nn_t a, nn_src_t b, long m, word_t c, word_t ci)
{
   dword_t t;
   long i;
   
   for (i = 0; i < m; i++) {
      t = (dword_t) b[i] * (dword_t) c + (dword_t) ci;
      a[i] = (word_t) t;
      ci = (t >> WORD_BITS);
   }

   return ci;
}

/* w.b. hart */
word_t nn_addmul_1(nn_t a, nn_src_t b, long m, word_t c, word_t ci)
{
   dword_t t;
   long i;

   for (i = 0; i < m; i++) {
      t = (dword_t) a[i] + (dword_t) b[i] * (dword_t) c + (dword_t) ci;
      a[i] = (word_t) t;
      ci = (t >> WORD_BITS);
   }

   return ci;
}

/* w.b. hart */
word_t nn_submul_1(nn_t a, nn_src_t b, long m, word_t c, word_t bi)
{
   dword_t t;
   long i;

   for (i = 0; i < m; i++) {
      t = (dword_t) a[i] - (dword_t) b[i] * (dword_t) c - (dword_t) bi;
      a[i] = (word_t) t;
      bi = -(sword_t)(t >> WORD_BITS);
   }

   return bi;
}

/* w.b. hart */
word_t nn_divrem_1(nn_t q, nn_t a, long m, word_t n, word_t ci)
{
   long i;
   
	for (i = m - 1; i >= 0; i--) {
		n_divrem_21(q[i], ci, a[i], n);	
      ci = a[i];
	}

   return ci;
}

/**********************************************************************
 
    Random functions

**********************************************************************/

/* w.b. hart */
void nn_randbits(nn_t a, rand_t state, long bits)
{
   long b = bits % WORD_BITS;
   long w = bits / WORD_BITS;
   long i;

   for (i = 0; i < w; i++)
      a[i] = n_randword(state);

   if (b)
      a[i] = n_randbits(state, bits);
}

/**********************************************************************
 
    Quadratic functions

**********************************************************************/

/* w.b. hart */
void nn_mul_classical(nn_t r, nn_src_t a, long m, nn_src_t b, long n)
{
   long i;
  
   r[m] = nn_mul_1(r, a, m, b[0], 0); 
   
   for (i = 1; i < n; i++)
      r[m + i] = nn_addmul_1(r + i, a, m, b[i], 0);
}

/* w.b. hart */
void nn_mul(nn_t p, nn_src_t a, long m, nn_src_t b, long n)
{
   long r;
   nn_t t;
   TMP_INIT;
   
   if (n <= 30) {
      nn_mul_classical(p, a, m, b, n);
      return;
   }

   if (n > (m + 1)/2) {
      nn_mul_kara(p, a, m, b, n);
      return;
   }

   r = m;

   while (r > n) r -= n;

   nn_mul(p, b, n, a, r);
  
   TMP_START;
   t = TMP_ALLOC((n + 1)*sizeof(word_t));
   while (m > r) {
      nn_copyi(t, p + r, n); /* temporarily save top n + 1 limbs */
      nn_mul(p + r, a + r, n, b, n);
      nn_add(p + r, p + r, 2*n, t, n, 0);
      r += n;
   }
   TMP_END;
}

/* w.b. hart */
word_t nn_divrem_classical(nn_t q, nn_t a, long m, nn_src_t d, long n, word_t ci)
{
   long i = m - 1, j = m - n;
   word_t d1 = d[n - 1], hi = 0;
   
   if (ci > d1 || (ci == d1 && nn_cmp(a + j + 1, d, n - 1) >= 0)) {
      ci -= d1 + nn_sub_m(a + j + 1, a + j + 1, d, n - 1, 0);
      hi = 1;
   }

   for ( ; i >= n - 1; i--, j--) {
      /* check for special case, a1 == d1 which would cause overflow */
      if (ci == d1) q[j] = ~(word_t) 0;
      else n_div_21(q[j], ci, a[i], d1);

      /* a -= d*q1 */
      ci -= nn_submul_1(a + j, d, n, q[j], 0);
      
      /* correct if remainder has become negative */
      while ((sword_t) ci < 0) {
         q[j]--;
         ci += nn_add_m(a + j, a + j, d, n, 0);
      }
      
      /* fetch next word */
      ci = a[i];
   }

   return hi;
}

/* w.b. hart */
void nn_divrem(nn_t q, nn_t a, long m, nn_src_t d, long n)
{
   long norm = n_leading_zeroes(d[n - 1]);
   nn_t b = (nn_t) d;
   word_t ci = 0;
   TMP_INIT;

   /* shift a and d left by norm(d) bits */
   if (norm) {
      TMP_START;
      b = TMP_ALLOC(n*sizeof(word_t));
      ci = nn_shl(a, a, m, norm, 0);
      nn_shl(b, d, n, norm, 0);
   } 

   /* do the division */
   if (n == 1) a[0] = nn_divrem_1(q, a, m, b[0], ci);
   else if (ci || m == n) nn_divrem_classical(q, a, m, b, n, ci);
   else q[m - n] = nn_divrem_classical(q, a, m - 1, b, n, a[m - 1]);

   /* shift remainder to the right by norm(d) bits */
   if (norm) {
      nn_shr(a, a, n, norm, 0);
      TMP_END;
   }
}

/* w.b. hart */
void nn_div(nn_t q, nn_t a, long m, nn_src_t d, long n)
{     
   long s = m - n + 1;
      
   if (s + 2 >= n)
      nn_divrem(q, a, m, d, n);
   else {
      long norm = n_leading_zeroes(d[n - 1]), inc = 0;
      nn_t t1, t2, t3;
      TMP_INIT;

      TMP_START;

      t1 = TMP_ALLOC((m + 1)*sizeof(word_t)); /* new a */
      t3 = TMP_ALLOC(n*sizeof(word_t)); /* new d */

      t1[m] = nn_shl(t1, a, m, norm, 0);
      nn_shl(t3, d, n, norm, 0);
      inc = (t1[m] != 0);

      t2 = TMP_ALLOC((s + 1 + inc)*sizeof(word_t));
      
      nn_divrem(t2, t1 + m - 2*s - 1, 2*s + 1 + inc, t3 + n - s - 1, s + 1);
      nn_copyi(q, t2 + 1, s);
      
      if (t2[0] == 0) { /* quotient may be one too large */
         nn_mul(t1, d, n, t2 + 1, s);
         if (nn_sub_m(a, a, t1, n, 0))
            nn_sub_1(q, t2 + 1, s, 1);
      }

      TMP_END;
   }
}

/* w.b. hart */
long nn_gcd(nn_t g, nn_t a, long m, nn_t b, long n)
{
   nn_t q;
   TMP_INIT;

   TMP_START;
   q = TMP_ALLOC((m - n + 1)*sizeof(word_t));

   /* a = bq + r; a = b; b = r; */
   while (n) {
      nn_divrem(q, a, m, b, n);
      nn_swap(a, b);
      m = n;
      n = nn_normalise(b, n);
   }

   /* write out GCD */
   nn_copyi(g, a, m);
   
   TMP_END;

   return m;
}

/**********************************************************************
 
    Subquadratic functions

**********************************************************************/

/* w.b. hart */
void nn_mul_kara(nn_t p, nn_src_t a, long m, nn_src_t b, long n)
{
   long m2 = (m + 1)/2;
   long h1 = m - m2;
   long h2 = n - m2;
   word_t ci;

   nn_t t;
   TMP_INIT;

   p[m2]       = nn_add(p, a, m2, a + m2, h1, 0);
   p[2*m2 + 1] = nn_add(p + m2 + 1, b, m2, b + m2, h2, 0);
   
   TMP_START;
   t = TMP_ALLOC((2*m2 + 2)*sizeof(word_t));
   
   nn_mul(t, p + m2 + 1, m2 + 1, p, m2 + 1); 
   nn_mul(p, a, m2, b, m2);
   nn_mul(p + 2*m2, a + m2, h1, b + m2, h2);
   
   ci = -(sword_t)nn_sub(t, t, 2*m2 + 1, p, 2*m2, 0);
   t[2*m2 + 1] = ci - nn_sub(t, t, 2*m2 + 1, p + 2*m2, h1 + h2, 0);
   
   nn_add(p + m2, p + m2, m + h2, t, 2*m2 + 1, 0);
   
   TMP_END;
}

/**********************************************************************
 
    Input/output

**********************************************************************/

/* w.b. hart */
char * nn_get_str(nn_t a, long m)
{
   /* 9.63... is log_10(2^32) */
   long i = 0, j;
   long digits = (long) ceil(m * 9.632959861247398 * (WORD_BITS/32)) + (m == 0);
   char * str = (char *) malloc(digits + 1);
   word_t ci, d = 10L << (WORD_BITS - 4);
   nn_t q1, q2;
   TMP_INIT;

   if (m == 0)
      str[0] = '0';
   else {
      TMP_START;
      q1 = TMP_ALLOC(m*sizeof(word_t));
      q2 = TMP_ALLOC(m*sizeof(word_t));
      nn_copyi(q1, a, m);

      /* compute digits in reverse order */
      for (i = digits; m > 0; i--) {
         ci = nn_shl(q1, q1, m, WORD_BITS - 4, 0);
         str[i - 1] = 48 + (char) (nn_divrem_1(q2, q1, m, d, ci) >> (WORD_BITS - 4));
         nn_swap(q1, q2);
         m = nn_normalise(q1, m);
      }

      TMP_END;

      /* didn't get the right number of digits, shift */
      if (i) {
         for (j = i; j < digits; j++)
            str[j - i] = str[j];
      }
   }

   str[digits - i] = '\0';

   return str;
}

/* w.b. hart */
long nn_set_str(nn_t a, long * len, const char * str)
{
   long i, m = 1, digits = strspn(str, "0123456789");
   word_t ci;

   if (digits == 1 && str[0] == '0')
      return 0;

   a[0] = (word_t) str[0] - 48;
   for (i = 1; i < digits; i++) {
      ci = nn_mul_1(a, a, m, 10, 0);
      ci += nn_add_1(a, a, m, (word_t) str[i] - 48);
      if (ci) a[m++] = ci;
   }

   *len = m;
   return digits;
}
