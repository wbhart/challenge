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

#include "ZZ.h"

/* w.b. hart */
int ZZ_t::operator==(const ZZ_t& b)
{
   return zz_cmp(this, &b) == 0;
}

/* w.b. hart */
int ZZ_t::operator==(long z)
{
   return zz_equal_1(this, z);
}

/* w.b. hart */
ZZ_t const ZZ_t::operator-() const
{
   ZZ_t r;

   zz_neg(&r, this);

   return r;
}

/* w.b. hart */
ZZ_t ZZ_t::operator+(const ZZ_t& b)
{
   ZZ_t r;

   zz_add(&r, this, &b);

   return r;
}

/* w.b. hart */
ZZ_t ZZ_t::operator-(const ZZ_t& b)
{
   ZZ_t r;

   zz_sub(&r, this, &b);

   return r;
}

/* w.b. hart */
ZZ_t ZZ_t::operator*(long b)
{
   ZZ_t r;

   zz_mul_1(&r, this, b);

   return r;
}

/* w.b. hart */
ZZ_t ZZ_t::operator*(const ZZ_t& b)
{
   ZZ_t r;

   zz_mul(&r, this, &b);

   return r;
}

/* w.b. hart */
const ZZ_t ZZ_t::operator*=(const ZZ_t& b)
{
   ZZ_t r;

   zz_mul(&r, this, &b);
   zz_copy(this, &r);

   return r;
}

/* w.b. hart */
const ZZ_t ZZ_t::operator*=(long b)
{
   ZZ_t r;

   zz_mul_1(&r, this, b);
   zz_copy(this, &r);

   return r;
}

/* w.b. hart */
ZZ_t ZZ_t::operator/(const ZZ_t& b)
{
   ZZ_t q;

   long i;

   zz_div(&q, this, &b);

   return q;
}

/* w.b. hart */
const ZZ_t ZZ_t::operator/=(const ZZ_t& b)
{
   ZZ_t q;

   zz_div(&q, this, &b);
   zz_copy(this, &q);

   return q;
}

/* w.b. hart */
void divrem(ZZ_t& q, ZZ_t& r, const ZZ_t& a, const ZZ_t& b)
{
   zz_divrem(&q, &r, &a, &b);
}

/* w.b. hart */
ZZ_t::ZZ_t(const char * str)
{
   zz_init(this);
   zz_set_str(this, str);
}

/* w.b. hart */
long set_str(ZZ_t& a, const char * str)
{
   zz_set_str(&a, str);
}

/* w.b. hart */
ZZ_t gcd(const ZZ_t& a, const ZZ_t& b)
{
   ZZ_t g;

   zz_gcd(&g, &a, &b);

   return g;
}

/* w.b. hart */
ostream& operator<<(ostream& os, const ZZ_t& a)
{
   char * str = zz_get_str(&a);
   
   if (a.size < 0)
      os << "-";
   os << str;
   
   free(str);

   return os;
}

/* w.b. hart */
void randbits(ZZ_t& r, rand_t state, long bits)
{
   zz_randbits(&r, state, bits);
}

/* w.b. hart */
void random(ZZ_t& r, rand_t state, va_list args)
{
   long bits = va_arg(args, long);

   zz_randbits(&r, state, bits);
}

/* w.b. hart */
ZZ_t factorial(long start, long n)
{
   long i;
   
   if (n <= 16) {
      ZZ_t r(start);
      for (i = start + 1; i < start + n; i++)
         r *= i;
      return r;
   } else {
      i = n/2;
      return factorial(start, i) * factorial(start + i, n - i);
   }
}

/* w.b. hart */
ZZ_t fac(long n)
{
   return factorial(1, n);
}

/* f. johansson (takahashi's algorithm, requires n > 2) */
ZZ_t fib_takahashi(unsigned long n)
{
    ZZ_t a, b, c;
    long i, sign;
    sign = -1;
    a = b = 1;
    for (i = n_bitcount(n) - 2; i > 0; i--)
    {
        c = a*a;
        a = (a+b) / 2;
        a = (a*a)*2 - c*3 - 2*sign;
        b = c*5 + 2*sign;
        sign = 1;
        if (n & (1UL << i)) {
            c = a;
            a = (a+b) / 2;
            b = a+c+c;
            sign = -1;
        }
    }
    if (n & 1)
        return ((a + b) / 2) * b - sign;
    else
        return a * b;
}

ZZ_t fib(unsigned long n)
{
    if (n <= 2)
        return ZZ_t((long) (n - (n == 2)));
    else
        return fib_takahashi(n);
}

