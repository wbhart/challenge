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
#include <iostream>
#include <vector>

#include "common.h"
#include "zz.h"

using namespace std;

#ifndef ZZ_CPP_H
#define ZZ_CPP_H

class ZZ_t : public zz_struct {
public:

   ZZ_t(long c) { 
      zz_init(this);
      zz_set_1(this, c);
   }

   ZZ_t(int c)  { 
      zz_init(this);
      zz_set_1(this, c); 
   }

   ZZ_t() {
      zz_init(this);
   }

   ZZ_t(const char * str);

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

   int operator==(long c);
   int operator!=(long c) { return !(*this == c); }

   int operator==(const ZZ_t& b);
   int operator!=(const ZZ_t& b) { return !(*this == b); }

   ZZ_t operator-();
   
   ZZ_t operator+(const ZZ_t& b);
   ZZ_t operator-(const ZZ_t& b);
   ZZ_t operator*(const ZZ_t& b);
   ZZ_t operator*(long b);
   ZZ_t operator/(const ZZ_t& b);
   
   const ZZ_t operator*=(long b);
   const ZZ_t operator*=(const ZZ_t& b);
   const ZZ_t operator/=(const ZZ_t& b);
};

void randbits(ZZ_t& r, rand_t state, long bits);

void divrem(ZZ_t& q, ZZ_t& r, const ZZ_t& a, const ZZ_t& b);

ZZ_t gcd(const ZZ_t & a, const ZZ_t & b);

ostream& operator<<(ostream& os, const ZZ_t& z);

ZZ_t fac(long n);

ZZ_t fib(unsigned long n);

#endif

