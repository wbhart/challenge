/*
   Copyright (c) 2013, Peter Luschny
   Copyright (c) 2013, William Hart
   Copyright (c) 2013, Fredrik Johansson

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

#include "numthy.h"

/******************************************************************************

   Number theory

******************************************************************************/

/* Peter Luschny */
int jacobi(const ZZ& A, const ZZ& B)
{
   int j = 1, res;
   long r8, remb4, remb8;
   ZZ a, b, q;
   
   if (A == 0)
      return B == 1;

   a = A;
   b = B;

   while (a != 0) {
      remb4 = divrem(q, b, 4) == 3;

      if (a < 0) {
         neg(a, a);
         j = remb4 ? -j : j;
      }

      remb8 = ((r8 = divrem(q, b, 8)) == 3L || r8 == 5L);

      while (a.is_even()) {
         div_2exp(a, a, 1);
         if (remb8) j = -j;
      }
  
      j = divrem(q, a, 4) == 3 && remb4 ? -j : j; 
  
      larem(b, b, a);
      swap(a, b);
   }
  
   res = b > 1 ? 0 : j;

   return res;
}

/* w.b. hart */
void factorial(ZZ& a, long start, long n)
{
   long i;
   
   if (n <= 16) {
      a = start;

      for (i = start + 1; i < start + n; i++)
         mul(a, a, i);
   } else {
      ZZ p;
      
      i = n/2;

      factorial(p, start, i);
      factorial(a, start + i, n - i);

      mul(a, a, p); 
   }
}

/* w.b. hart */
void factorial(ZZ& a, long n)
{
   return factorial(a, 1, n);
}

/* f. johansson (Takahashi's algorithm, requires n > 2) */
void fib_takahashi(ZZ& t, unsigned long n)
{
    ZZ a(1), b(1), c;
    long i, sign = -1;
    
    for (i = n_bitcount(n) - 2; i > 0; i--) {
        mul(c, a, a);
        add(a, a, b);
        div_2exp(a, a, 1);
        mul(a, a, a);
        mul(a, a, 2);
        mul(t, c, 3);
        sub(a, a, t);
        sub(a, a, 2*sign);
        mul(b, c, 5);
        add(b, b, 2*sign);
        sign = 1;
        if (n & (1UL << i)) {
            c = a;
            add(a, a, b);
            div_2exp(a, a, 1);
            add(b, a, c);
            add(b, b, c);
            sign = -1;
        }
    }

    if (n & 1) {
        add(t, a, b);
        div_2exp(t, t, 1);
        mul(t, t, b);
        sub(t, t, sign);
    } else 
        mul(t, a, b);
}

void fibonacci(ZZ& t, unsigned long n)
{
    if (n <= 2)
        t = (long) (n - (n == 2));
    else
        fib_takahashi(t, n);
}

/* w.b. hart --  based on Peter Luschny's Python implementation */
int is_prime(const ZZ& n)
{
   ZZ k, m, q;
   long b, i, l;
   int j;

   if (n <= 1)
      return 0;
   
   if (n <= 3)
      return 1;

   if (n.is_even())
      return 0;

   sub(k, n, 1);
   div_2exp(k, k, 1);
   b = n.bits();

   l = (long) (0.96090602783640285*b*b); /* >= 2*log(n)^2 */
   l = b <= 8 ? MIN(divrem(q, n, 256) - 1, l) : l;
   
   for (i = 2; i < l; i++) {
      q = i;
      j = jacobi(q, n);
      if (j == 0)
         return 0;

      powmod(m, q, k, n);

      if (j == 1) {
         if (m != 1) 
            return 0;
      } else {
         sub(q, n, 1);

         if (m != q)
            return 0;   
      }
   }

   return 1;      
}
