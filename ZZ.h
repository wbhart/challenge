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

#include <cstdlib>
#include <cstdarg>
#include <iostream>
#include <vector>

#include "common.h"
#include "word.h"
#include "zz_t.h"

using namespace std;

#ifndef ZZ_CPP_H
#define ZZ_CPP_H

class ZZ_t : public zz_struct {
public:

   explicit ZZ_t(long c) { 
      zz_init(this);
      zz_set_1(this, c);
   }

   explicit ZZ_t(int c) { 
      zz_init(this);
      zz_set_1(this, c); 
   }

   explicit ZZ_t() {
      zz_init(this);
   }

   explicit ZZ_t(const char * str);

   ~ZZ_t() { 
      zz_clear(this);
   }

   ZZ_t(const ZZ_t& b) {
      zz_init(this);
      zz_copy(this, &b);
   }

   ZZ_t(ZZ_t&& b) {
      zz_init(this);
      zz_copy(this, &b);
   }

   const ZZ_t operator=(const ZZ_t& b) {
      zz_copy(this, &b);
      return *this;
   }

   const ZZ_t operator=(ZZ_t&& b) {
      zz_copy(this, &b);
      return *this;
   }

   const ZZ_t operator=(long b) {
      zz_set_1(this, b);
      return *this;
   }

   explicit operator long int() const;

   int operator==(long b) const;
   int operator!=(long b) const { return !(*this == b); }

   int operator==(const ZZ_t& b);
   int operator!=(const ZZ_t& b) { return !(*this == b); }

   int operator<(const ZZ_t& b) { return zz_cmp(this, &b) < 0; }
   int operator>(const ZZ_t& b) { return zz_cmp(this, &b) > 0; }
   int operator<=(const ZZ_t& b) { return zz_cmp(this, &b) <= 0; }
   int operator>=(const ZZ_t& b) { return zz_cmp(this, &b) >= 0; }

   int operator<(long b) const { return zz_cmp_1(this, b) < 0; }
   int operator>(long b) const { return zz_cmp_1(this, b) > 0; }
   int operator<=(long b) const { return zz_cmp_1(this, b) <= 0; }
   int operator>=(long b) const { return zz_cmp_1(this, b) >= 0; }

   ZZ_t const operator-() const;
   
   ZZ_t operator+(const ZZ_t& b);
   ZZ_t operator+(long b) const;
   ZZ_t operator-(const ZZ_t& b);
   ZZ_t operator-(long b) const;
   ZZ_t operator*(const ZZ_t& b);
   ZZ_t operator*(long b) const;
   ZZ_t operator/(const ZZ_t& b);
   ZZ_t operator%(const ZZ_t& b);
   ZZ_t operator/(long b) const;
   long operator%(long b) const;
   ZZ_t operator>>(long b) const;
   
   const ZZ_t operator+=(const ZZ_t& b);
   const ZZ_t operator*=(long b);
   const ZZ_t operator*=(const ZZ_t& b);
   const ZZ_t operator/=(const ZZ_t& b);
   const ZZ_t operator>>=(long b);

   long bits() const;
};

static inline
int is_even(const ZZ_t& a)
{
   return a.size == 0 || (a.n[0] % 2) == 0;
}

static inline
int is_odd(const ZZ_t& a)
{
   return a.size != 0 && (a.n[0] % 2) == 1;
}

void swap(ZZ_t& a, ZZ_t& b);

void randbits(ZZ_t& r, rand_t state, long bits);

void random(ZZ_t& r, rand_t state, va_list args);

void divrem(ZZ_t& q, ZZ_t& r, const ZZ_t& a, const ZZ_t& b);

ZZ_t larem(const ZZ_t& a, const ZZ_t& b);

ZZ_t gcd(const ZZ_t & a, const ZZ_t & b);

int jacobi(const ZZ_t& a, const ZZ_t& b);

long set_str(ZZ_t& a, const char * str);

ostream& operator<<(ostream& os, const ZZ_t& z);

ZZ_t fac(long n);

ZZ_t fib(unsigned long n);

ZZ_t powmod(const ZZ_t& a, const ZZ_t& exp, const ZZ_t & n);

int is_prime(const ZZ_t& n);

#endif

