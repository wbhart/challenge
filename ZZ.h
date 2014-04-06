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
#include <cstring>
#include <iostream>

#include "common.h"
#include "word.h"
#include "nn_t.h"

using namespace std;

#ifndef ZZ_CPP_H
#define ZZ_CPP_H

class ZZ {

   nn_t n;
   long size;
   long alloc;

public:

   explicit ZZ() {
      n = NULL;
      size = 0;
      alloc = 0;
   }

   explicit ZZ(long c) { 
      n = (nn_t) malloc(sizeof(word_t));
      size = c == 0 ? 0 : (c < 0 ? -1 : 1);
      alloc = 1;
      n[0] = c < 0 ? -c : c;
   }

   explicit ZZ(int c) { 
      n = (nn_t) malloc(sizeof(word_t));
      size = c == 0 ? 0 : (c < 0 ? -1 : 1);
      alloc = 1;
      n[0] = c < 0 ? -c : c;
   }

   explicit ZZ(const ZZ& c) {
      size = c.size;
      alloc = ABS(size);
      n = (nn_t) malloc(sizeof(word_t)*alloc);
      nn_copyi(n, c.n, alloc);
   }

   explicit ZZ(const char * str);

   ~ZZ() { 
      free(this->n);
   }

   ZZ& operator=(long c);

   ZZ& operator=(int c);

   ZZ& operator=(const ZZ& c);

   int operator==(const ZZ& c) const;
   
   int operator!=(const ZZ& c) const { 
      return !(*this == c); 
   }

   int operator==(long c) const;
   
   int operator!=(long c) const { 
      return !(*this == c); 
   }

   int operator<(long c) const;

   int operator>=(long c) const {
      return !(*this < c);
   }

   int operator<(const ZZ& c) const;
   
   int operator>=(const ZZ& c) const {
      return !(*this < c);
   }
   
   int operator>(long c) const;

   int operator<=(long c) const {
      return !(*this > c);
   }

   int operator>(const ZZ& c) const;
   
   int operator<=(const ZZ& c) const {
      return !(*this > c);
   }
   
   friend ostream& operator<<(ostream & os, ZZ& a);

   char * to_string();

   void fit(long m);

   void randbits(rand_t state, long bits);

   void normalise();

   int cmpabs(const ZZ& b) const;

   void zero() {
      size = 0;
   }

   int is_zero() const {
      return size == 0;
   }

   void one() {
      fit(1);
      size = 1;
      n[0] = 1;
   }

   int is_one() const {
      return size == 1 && n[0] == 1;
   }

   void swap(ZZ& b);

   friend void neg(ZZ& r, const ZZ& a);

   friend void abs(ZZ& r, const ZZ& a) {
      if (a < 0)
         neg(r, a);
      else
         r = a;
   }

   friend void add(ZZ& r, const ZZ& a, const ZZ& b);

   friend void sub(ZZ& r, const ZZ& a, const ZZ& b);

   friend void add(ZZ& r, const ZZ& a, long c);

   friend void sub(ZZ& r, const ZZ& a, long c);

   void add(ZZ& r, const ZZ& a, int c) {
      if (c < 0)
         sub(r, a, (long) -c);
      else
         add(r, a, (long) c);
   }

   void sub(ZZ& r, const ZZ& a, int c) {
      if (c < 0)
         add(r, a, (long) -c);
      else
         sub(r, a, (long) c);
   }

   friend void mul_2exp(ZZ& r, const ZZ& a, long exp);

   friend void div_2exp(ZZ& r, const ZZ& a, long exp);

   friend void mul(ZZ& q, const ZZ& a, long b);

   friend long divrem(ZZ& q, const ZZ& a, long b);

   friend void mul(ZZ& r, const ZZ& a, const ZZ& b);

   friend void divrem(ZZ& q, ZZ& r, const ZZ& a, const ZZ& b);

   friend void div(ZZ& q, const ZZ& a, const ZZ& b);

   friend void gcd(ZZ& g, const ZZ& a, const ZZ& b);
};

#endif

