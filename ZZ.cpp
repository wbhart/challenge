/*
   Copyright (c) 2013, William Hart
   Copyright (c) 2013, Peter Luschny
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

#include "ZZ.h"  

/* w.b. hart */
ZZ_t::operator long int() const
{ 
   return this->size >= 0 ? this->n[0] : -this->n[0]; 
}

/* w.b. hart */
long ZZ_t::bits() const
{ 
   long s = this->size; 
   
   return s == 0 ? 0 : s*WORD_BITS - n_leading_zeroes(this->n[s - 1]);
}

/* w.b. hart */
int ZZ_t::operator==(const ZZ_t& b)
{
   return zz_cmp(this, &b) == 0;
}

/* w.b. hart */
int ZZ_t::operator==(long b) const
{ 
   return zz_cmp_1(this, b) == 0; 
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
ZZ_t ZZ_t::operator+(long b) const
{
   ZZ_t r;
   ZZ_t B(b);

   if (b >= 0)
      zz_add_1(&r, this, b);
   else
      zz_sub_1(&r, this, -b);

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
ZZ_t ZZ_t::operator-(long b) const
{
   ZZ_t r;
   ZZ_t B(b);

   if (b >= 0)
      zz_sub_1(&r, this, b);
   else
      zz_add_1(&r, this, -b);
 
   return r;
}

/* w.b. hart */
ZZ_t ZZ_t::operator*(long b) const
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
long ZZ_t::operator%(long b) const
{
   if (b >= 0 && (b & (b - 1)) == 0)
      return this->n[0] % b;
   else {
      ZZ_t q;
      return zz_divrem_1(&q, this, b);
   }
}

/* w.b. hart */
ZZ_t ZZ_t::operator>>(long b) const
{
   ZZ_t r;

   zz_div_2exp(&r, this, b);

   return r;
}

/* w.b. hart */
const ZZ_t ZZ_t::operator>>=(long b)
{
   ZZ_t r;

   zz_div_2exp(&r, this, b);
   zz_copy(this, &r);

   return r;
}

/* w.b. hart */
const ZZ_t ZZ_t::operator+=(const ZZ_t& b)
{
   ZZ_t r;

   zz_add(&r, this, &b);
   zz_copy(this, &r);

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

   zz_div(&q, this, &b);

   return q;
}

/* w.b. hart */
ZZ_t ZZ_t::operator%(const ZZ_t& b)
{
   ZZ_t q, r;

   zz_divrem(&q, &r, this, &b);

   return r;
}

/* w.b. hart */
ZZ_t ZZ_t::operator/(long b) const
{
   ZZ_t q;
   
   zz_divrem_1(&q, this, b);

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
void swap(ZZ_t& a, ZZ_t& b)
{
   zz_swap(&a, &b);
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
   return zz_set_str(&a, str);
}

/* w.b. hart */
ZZ_t larem(const ZZ_t& a, const ZZ_t& b)
{
   ZZ_t r;

   zz_larem(&r, &a, &b);

   return r;
}

/* w.b. hart */
ZZ_t gcd(const ZZ_t& a, const ZZ_t& b)
{
   ZZ_t g;

   zz_gcd(&g, &a, &b);

   return g;
}

/* Peter Luschny */
int jacobi(const ZZ_t& A, const ZZ_t& B)
{
   int j = 1, res, r8, remb4, remb8;
   ZZ_t a, b;
   
   if (A == 0L)
      return B == 1L;

   a = A;
   b = B;

   while (a != 0L) {
      remb4 = (b % 4) == 3L;

      if (a < 0L) {
         a = -a;
         j = remb4 ? -j : j;
      }

      remb8 = ((r8 = (b % 8)) == 3L || r8 == 5L);

      while ((a.n[0] % 2) == 0) {
         a >>= 1;
         if (remb8) j = -j;
      }
  
      j = (a % 4) == 3 && remb4 ? -j : j; 
  
      b = larem(b, a);
      swap(a, b);
   }
  
   res = b > 1L ? 0 : j;

   return res;
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
        a = (a+b) >> 1;
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
        return ((a + b) >> 1) * b - sign;
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

/* w.b. hart */
ZZ_t powmod(const ZZ_t& a, const ZZ_t& e, const ZZ_t & n)
{     
   ZZ_t res, pow, exp;

   if (n == 1 || a == 0)
      return ZZ_t(0);

   res = 1;
   pow = a;
   exp = e;

   if (exp != 0) {
      while ((exp % 2) == 0) {
         pow = (pow*pow) % n;
         exp >>= 1;
      }
     
      res = pow;

      while ((exp >>= 1) != 0) {
         pow = (pow*pow) % n;
         if ((exp % 2) == 1)
            res = (res*pow) % n;
      }
   }

   return res;
}

/* w.b. hart --  based on Peter Luschny's Python implementation */
int is_prime(const ZZ_t& n)
{
   ZZ_t k, m;
   long b, i, l;
   int j;

   if (n <= 1L)
      return 0;
   
   if (n <= 3L)
      return 1;

   if ((n % 2) == 0L)
      return 0;

   k = (n - 1) / 2;
   b = n.bits();

   l = (long) (0.96090602783640285*b*b); /* >= 2*log(n)^2 */
   l = b <= 8 ? MIN(long(n) - 1, l) : l;
   
   for (i = 2; i < l; i++) {
      j = jacobi(ZZ_t(i), n);
      if (j == 0)
         return 0;

      m = powmod(ZZ_t(i), k, n);

      if (j == 1) {
         if (m != 1) 
            return 0;
      } else {
         if (m != n - 1)
            return 0;   
      }
   }

   return 1;      
}
