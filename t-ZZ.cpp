#include <cassert>
#include "ZZ.h"

void test_addsub(rand_t state)
{
   ZZ_t a, b, c;
   long i;

   cout << "add/sub... ";

   for (i = 0; i < 10000; i++) {
      randbits(a, state, n_randint(state, 1000));
      randbits(b, state, n_randint(state, 1000));

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
      randbits(a, state, -n_randint(state, 1000));   
      do {
         randbits(b, state, -n_randint(state, 1000));
      } while (b == 0);


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
      randbits(a, state, -n_randint(state, 1000));
      do {
         randbits(b, state, -n_randint(state, 1000));
      } while (b == 0);

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

      randbits(c, state, -n_randint(state, 500));
      
      a = a * c;
      b = b * c;

      g = gcd(a, b);
      
      assert(g == c);
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
      
   return 0;
}