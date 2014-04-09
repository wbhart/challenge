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

void test_ZZ(rand_t state)
{
  cout << "ZZ...";
  
  ZZ a(1), b(0), c(-1);
  ZZ d(1L), e(0L), f(-1L);
  ZZ g("123");
  ZZ h("0"), i("-123");
  ZZ j("123456987987429387498237948273984792384793284");
  ZZ k("-123456987987429387498237948273984792384793284");
  ZZ l(h), m(j), n(k);
  ZZ o;

  cout << "PASS" << endl;
}

void test_assignment(rand_t state)
{
   ZZ a, b;
   long c, i;

   cout << "assignment...";
  
   /* ZZ to long */
   for (i = 0; i < 1000; i++)
   {
      long bits = n_randint(state, WORD_BITS) + 1;

      c = n_randbits(state, bits);

      b = c;

      if (b != c)
      {
         cout << "Assignment failed" << endl;
         cout << "a = " << c << endl;
         cout << "b = " << b << endl;
         abort();
      }
   }

   /* ZZ to ZZ */
   for (i = 0; i < 1000; i++)
   {
      long bits = n_randint(state, 200) + 1;

      a.randbits(state, -bits);

      b = a;

      if (b != a)
      {
         cout << "Assignment failed" << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         abort();
      }
   }

   cout << "PASS" << endl;
}

void test_zero(rand_t state)
{
   ZZ a;

   cout << "zero...";

   a.zero();

   if (!a.is_zero())
   {
      cout << "Not zero" << endl;
      cout << "a = " << a << endl;
      abort();
   }

   cout << "PASS" << endl;
}

void test_one(rand_t state)
{
   ZZ a;

   cout << "one...";

   a.one();

   if (!a.is_one())
   {
      cout << "Not one" << endl;
      cout << "a = " << a << endl;
      abort();
   }

   cout << "PASS" << endl;
}

void test_add_sub(rand_t state)
{
   ZZ a, b, c, r;
   long d, i;

   cout << "add/sub...";
  
   /* long: a + d - d == a */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, WORD_BITS) + 1;

      a.randbits(state, -bits1);
      d = n_randbits(state, bits2);
      if (n_randint(state, 2))
         d = -d;

      add(c, a, d);
      sub(r, c, d);

      if (r != a)
      {
         cout << "add/sub_1 failed" << endl;
         cout << "r = " << r << endl;
         cout << "a = " << a << endl;
         cout << "c = " << c << endl;
         cout << "d = " << d << endl;
         abort();
      }
   }

   /* ZZ: a + b - b == a */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, 200) + 1;

      a.randbits(state, -bits1);
      b.randbits(state, -bits2);

      add(c, a, b);
      sub(r, c, b);

      if (r != a)
      {
         cout << "add/sub failed" << endl;
         cout << "r = " << r << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "c = " << c << endl;
         abort();
      }
   }

   cout << "PASS" << endl;
}

void test_neg(rand_t state)
{
   ZZ a, b, c, r1, r2;
   long i;

   cout << "neg...";
  
   /* ZZ: a + (-b) == a - b */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, 200) + 1;

      a.randbits(state, -bits1);
      b.randbits(state, -bits2);

      neg(c, b);
      add(r1, a, c);
      sub(r2, a, b);

      if (r1 != r2)
      {
         cout << "neg failed" << endl;
         cout << "r1 = " << r1 << endl;
         cout << "r2 = " << r2 << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "c = " << c << endl;
         abort();
      }
   }

   cout << "PASS" << endl;
}

void test_abs(rand_t state)
{
   ZZ a, b, r, s;
   long i;

   cout << "abs...";
  
   /* abs(a) >= 0 */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      
      a.randbits(state, -bits1);
      
      abs(r, a);
      
      if (r < 0)
      {
         cout << "abs failed" << endl;
         cout << "r = " << r << endl;
         cout << "a = " << a << endl;
         abort();
      }
   }

   /* abs(-a) = abs(a) */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      
      a.randbits(state, -bits1);
      
      abs(r, a);
      neg(b, a);
      abs(s, b);

      if (r != s)
      {
         cout << "abs failed" << endl;
         cout << "r = " << r << endl;
         cout << "s = " << s << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         abort();
      }
   }

   cout << "PASS" << endl;
}

void test_mul_div_2exp(rand_t state)
{
   ZZ a, b, r;
   long i;

   cout << "mul_2exp/div_2exp...";
  
   /* long: a * 2^exp / 2^exp == a */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long exp = n_randint(state, 200) + 1;

      a.randbits(state, -bits1);
      
      mul_2exp(b, a, exp);
      div_2exp(r, b, exp);

      if (r != a)
      {
         cout << "mul/div_2exp failed" << endl;
         cout << "r = " << r << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "exp = " << exp << endl;
         abort();
      }
   }

   cout << "PASS" << endl;
}

void test_mul_divrem(rand_t state)
{
   ZZ a, b, c, rem, q;
   long r, i, d;

   cout << "mul/divrem...";
  
   /* long: a * d / d == a */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, WORD_BITS) + 1;

      a.randbits(state, -bits1);
      d = n_randbits(state, bits2);

      mul(b, a, d);
      r = divrem(q, b, d);

      if (q != a || r != 0)
      {
         cout << "mul/div_1 failed" << endl;
         cout << "q = " << q << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "d = " << d << endl;
         cout << "r = " << r << endl;
         abort();
      }
   }

   /* long: a = d*q + r */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, WORD_BITS) + 1;

      a.randbits(state, -bits1);
      d = n_randbits(state, bits2);

      r = divrem(q, a, d);
      mul(b, q, d);
      add(b, b, r);

      if (a != b)
      {
         cout << "mul/divrem_1 failed" << endl;
         cout << "q = " << q << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "d = " << d << endl;
         cout << "r = " << r << endl;
         abort();
      }
   }

   /* ZZ: a * b / b == a */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, 200) + 1;

      a.randbits(state, -bits1);
      b.randbits(state, -bits2);

      mul(c, a, b);
      divrem(q, rem, c, b);

      if (q != a || rem != 0)
      {
         cout << "mul/divrem failed" << endl;
         cout << "q = " << q << endl;
         cout << "rem = " << rem << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "c = " << c << endl;
         abort();
      }
   }

   /* long: a = b*q + rem */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, 200) + 1;

      a.randbits(state, -bits1);
      b.randbits(state, -bits2);

      divrem(q, rem, a, b);
      mul(c, q, b);
      add(c, c, rem);

      if (c != a)
      {
         cout << "divrem failed" << endl;
         cout << "q = " << q << endl;
         cout << "rem = " << rem << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "c = " << c << endl;
         abort();
      }
   }
   
   cout << "PASS" << endl;
}

void test_mul_div(rand_t state)
{
   ZZ a, b, c, q;
   long i;

   cout << "mul/div...";
  
   /* ZZ: a * b / b == a */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, 200) + 1;

      a.randbits(state, -bits1);
      b.randbits(state, -bits2);

      mul(c, a, b);
      div(q, c, b);

      if (q != a)
      {
         cout << "mul/div failed" << endl;
         cout << "q = " << q << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "c = " << c << endl;
         abort();
      }
   }

   cout << "PASS" << endl;
}

void test_gcd(rand_t state)
{
   ZZ a, b, a2, b2, c, g;
   long i;

   cout << "gcd...";
  
   /* ZZ: a * b / b == a */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, 200) + 1;
      long bits3 = n_randint(state, 200) + 1;

      do {
         a.randbits(state, -bits1);
         b.randbits(state, -bits2);
         gcd(g, a, b);
      } while (g != 1);

      c.randbits(state, bits3);
         
      mul(a2, a, c);
      mul(b2, b, c);
      gcd(g, a2, b2);
      abs(g, g);

      if (g != c)
      {
         cout << "gcd failed" << endl;
         cout << "g = " << g << endl;
         cout << "a = " << a << endl;
         cout << "b = " << b << endl;
         cout << "a2 = " << a2 << endl;
         cout << "b2 = " << b2 << endl;
         cout << "c = " << c << endl;
         abort();
      }
   }

   cout << "PASS" << endl;
}

void test_powmod(rand_t state)
{
   ZZ a, e1, e2, e, n, q, r1, r2, r3;
   long i;

   cout << "powmod...";
  
   /* ZZ: a * b / b == a */
   for (i = 0; i < 1000; i++)
   {
      long bits1 = n_randint(state, 200) + 1;
      long bits2 = n_randint(state, 200) + 1;
      
      a.randbits(state, bits1);
      e1.randbits(state, bits2);
      e2.randbits(state, bits2);
      n.randbits(state, bits1);
      
      divrem(q, a, a, n);
      
      mul(e, e1, e2);

      powmod(r1, a, e1, n);
      powmod(r1, r1, e2, n);

      powmod(r2, a, e2, n);
      powmod(r2, r2, e1, n);

      powmod(r3, a, e, n);

      if (r1 != r2 || r2 != r3)
      {
         cout << "powmod failed" << endl;
         cout << "a = " << a << endl;
         cout << "e = " << e << endl;
         cout << "n = " << n << endl;
         cout << "r1 = " << r1 << endl;
         cout << "r2 = " << r2 << endl;
         cout << "r3 = " << r3 << endl;
         abort();
      }
   }

   cout << "PASS" << endl;
}

int main(void)
{   
   rand_t state;
   randinit(state);

   test_ZZ(state);
   test_assignment(state);
   test_zero(state);
   test_one(state);
   test_add_sub(state);
   test_neg(state);
   test_abs(state);
   test_mul_div_2exp(state);
   test_mul_divrem(state);
   test_mul_div(state);
   test_gcd(state);
   test_powmod(state);

   return 0;
}
