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

void test_addsub(rand_t state)
{
   ZZ_t a, b, c;
   long i;

   cout << "add/sub... ";

   for (i = 0; i < 10000; i++) {
      randbits(a, state, -(long)n_randint(state, 1000));
      randbits(b, state, -(long)n_randint(state, 1000));

      ZZ_t c = a + b;
      c = c - b;

      assert(a == c);
   }

   cout << "PASS" << endl;
}

void test_muldiv(rand_t state)
{
   ZZ_t a, b;
   long i;

   cout << "mul/div... ";

   for (i = 0; i < 10000; i++) {
      randbits(a, state, -(long)n_randint(state, 1000));   
      do {
         randbits(b, state, -(long)n_randint(state, 1000));
      } while (b == 0L);


      ZZ_t c = a * b;
      c /= b;
      
      assert(a == c);
   }

   cout << "PASS" << endl;
}

void test_divdivrem(rand_t state)
{
   ZZ_t a, b;
   long i;

   cout << "div/divrem... ";

   for (i = 0; i < 10000; i++) {
      randbits(a, state, -(long)n_randint(state, 1000));
      do {
         randbits(b, state, -(long)n_randint(state, 1000));
      } while (b == 0L);

      ZZ_t q1 = a / b, q2, r2;
      divrem(q2, r2, a, b);

      assert(q1 == q2);
   }

   cout << "PASS" << endl;
}

void test_gcd(rand_t state)
{
   ZZ_t a, b, c;
   ZZ_t g, s, t;
   long i;

   cout << "gcd... ";

   for (i = 0; i < 10000; i++)
   {
      do {
         randbits(a, state, n_randint(state, 500));
         randbits(b, state, n_randint(state, 500));
         g = gcd(a, b);
      } while (g != 1 && g != -1);

      randbits(c, state, -(long)n_randint(state, 500));
      
      a = a * c;
      b = b * c;

      g = gcd(a, b);
      
      assert(g == c);
   }

   cout << "PASS" << endl;
}

void test_jacobi(rand_t state)
{
   ZZ_t a, b, c, d;
   long i;
   int j1, j2;

   cout << "jacobi... ";

   for (i = 0; i < 1000; i++) {
      randbits(a, state, n_randint(state, 1000));
      do {
         randbits(b, state, n_randint(state, 1000));
      } while (is_even(b));

      randbits(c, state, n_randint(state, 1000));
      
      j1 = jacobi(a, b);
      j2 = jacobi(c, b);

      a *= c;
           
      assert(jacobi(a, b) == j1*j2);
   }

   for (i = 0; i < 1000; i++) {
      randbits(a, state, n_randint(state, 1000));
      do {
         randbits(b, state, n_randint(state, 1000));
      } while (is_even(b));

      do {
         randbits(d, state, n_randint(state, 1000));
      } while (is_even(d));


      j1 = jacobi(a, b);
      j2 = jacobi(a, d);

      b *= d;
           
      assert(jacobi(a, b) == j1*j2);
   }

   cout << "PASS" << endl;
}

void test_fib(rand_t state)
{
   ZZ_t a, b, c;
   long i;

   cout << "fib... ";

   for (i = 0; i < 500; i++)
   {
        a = fib(i);
        b = fib(i+1);
        c = fib(i+2);
        assert (a + b == c);
   }

   cout << "PASS" << endl;
}

void test_is_prime(rand_t state)
{
   ZZ_t a, b, c;
   long i, j;

   cout << "is_prime... ";

   for (i = 0; i < 100; i++) /* check primes have no small factors */
   {
        do {
           randbits(a, state, n_randint(state, 32));
        } while (!is_prime(a));
      
        for (j = 2; j < 100; j++)
           assert((a % j) != 0 || a == j);
   }

   for (i = 0; i < 100; i++) /* check composites don't pass */
   {
        do {
           randbits(a, state, n_randint(state, 32));
        } while (!is_prime(a));
      
        do {
           randbits(b, state, n_randint(state, 32));
        } while (!is_prime(b));
      
        assert(!is_prime(a*b));
   }

   cout << "PASS" << endl;
}

int main(void)
{
   rand_t state;
   randinit(state);
   
   test_addsub(state);
   test_muldiv(state);
   test_divdivrem(state);
   test_gcd(state);
   test_jacobi(state);
   test_fib(state);
   test_is_prime(state);

   return 0;
}
