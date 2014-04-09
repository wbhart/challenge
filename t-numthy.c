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
#include "numthy.h"

void test_jacobi(rand_t state)
{
   ZZ a, b, c, d;
   long i;
   int j1, j2, j;

   cout << "jacobi... ";

   for (i = 0; i < 1000; i++) {
      a.randbits(state, n_randint(state, 1000));
      do {
         b.randbits(state, n_randint(state, 1000));
      } while (b.is_even());

      c.randbits(state, n_randint(state, 1000));
      
      j1 = jacobi(a, b);
      j2 = jacobi(c, b);

      mul(a, a, c);
           
      j = jacobi(a, b);
      
      if (j != j1*j2) {
         cout << "jacobi numerators failed" << endl;
         cout << j << " " << j1 << " " << j2 << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "c = " << c << endl;
         abort();
      }
   }

   for (i = 0; i < 1000; i++) {
      a.randbits(state, n_randint(state, 1000));
      do {
         b.randbits(state, n_randint(state, 1000));
      } while (b.is_even());

      do {
         d.randbits(state, n_randint(state, 1000));
      } while (d.is_even());


      j1 = jacobi(a, b);
      j2 = jacobi(a, d);

      mul(b, b, d);
        
      j = jacobi(a, b);

      if (j != j1*j2) {
         cout << "jacobi denominators failed" << endl;
         cout << j << " " << j1 << " " << j2 << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "d = " << d << endl;
         abort();
      }
   }

   cout << "PASS" << endl;
}

void test_fibonacci(rand_t state)
{
   ZZ a, b, c, d;
   long i;

   cout << "fibonacci... ";

   for (i = 0; i < 1000; i++)
   {
        fibonacci(a, i);
        fibonacci(b, i+1);
        fibonacci(c, i+2);

        add(d, a, b);
        
        if (d != c) {
           cout << "fibonacci failed" << endl;
           cout << i << endl;
           cout << a << endl;
           cout << b << endl;
           cout << c << endl;
           cout << c << endl;
        }
   }

   cout << "PASS" << endl;
}

void test_is_prime(rand_t state)
{
   ZZ a, b, c, q;
   long i, j;

   cout << "is_prime... ";

   for (i = 0; i < 500; i++) { /* check primes have no small factors */
        do {
           a.randbits(state, n_randint(state, 32));
        } while (!is_prime(a));
      
        for (j = 2; j < 100; j++)
           if (divrem(q, a, j) == 0 && a != j) {
              cout << "is_prime yields prime with small factors" << endl;
              cout << a << endl;
              cout << j << endl;
              abort();
           }
   }

   for (i = 0; i < 500; i++) { /* check composites don't pass */
        do {
           a.randbits(state, n_randint(state, 32));
        } while (!is_prime(a));
      
        do {
           b.randbits(state, n_randint(state, 32));
        } while (!is_prime(b));
      
        mul(c, a, b);
        
        if (is_prime(c)) {
           cout << "is_prime passes composites" << endl;
           cout << a << endl;
           cout << b << endl;
           cout << c << endl;
        }
   }

   cout << "PASS" << endl;
}

int main(void)
{   
   rand_t state;
   randinit(state);

   test_jacobi(state);
   test_fibonacci(state);
   test_is_prime(state);

   return 0;
}
