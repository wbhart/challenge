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

#include <cassert>
#include "ZZ.h"
#include "Poly.h"

void test_addsub(rand_t state)
{
   Poly<ZZ_t> a1, b1, c1;
   Poly<Poly<Poly<ZZ_t>>> a2, b2, c2;
   long i;

   cout << "add/sub... ";

   for (i = 0; i < 10000; i++) {
      random(a1, state, 5, -12L);
      random(b1, state, 5, -12L);

      c1 = a1 + b1;
      c1 = c1 - b1;

      assert(a1 == c1);
   }

   for (i = 0; i < 10000; i++) {
      random(a2, state, 5, 4, 3, -12L);
      random(b2, state, 5, 4, 3, -12L);

      c2 = a2 + b2;
      c2 = c2 - b2;

      assert(a2 == c2);
   }

   cout << "PASS" << endl;   
}

void test_mul(rand_t state)
{
   Poly<ZZ_t> a1, b1, c1;
   Poly<Poly<ZZ_t>> a2, b2, c2;
   long i;

   cout << "mul... ";

   for (i = 0; i < 1000; i++) {
      random(a1, state, 5, -12L);
      random(b1, state, 5, -12L);
      random(c1, state, 5, -12L);

      assert((a1*b1)*c1 == a1*(b1*c1));
   }

   for (i = 0; i < 1000; i++) {
      random(a2, state, 5, 4, -12L);
      random(b2, state, 5, 4, -12L);
      random(c2, state, 5, 4, -12L);

      assert((a2*b2)*c2 == a2*(b2*c2));
   }

   cout << "PASS" << endl;   
}

int main(void)
{
   rand_t state;
   randinit(state);

   test_addsub(state);
   test_mul(state);
   
   return 0;
}
