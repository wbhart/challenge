#include "ZZ.h"


int ZZ_t::operator==(const ZZ_t& b)
{
   return zz_cmp(this, &b) == 0;
}

int ZZ_t::operator==(long z)
{
   return zz_equal_1(this, z);
}

ZZ_t ZZ_t::operator-()
{
   ZZ_t r;

   zz_neg(&r, this);

   return r;
}

ZZ_t ZZ_t::operator+(const ZZ_t& b)
{
   ZZ_t r;

   zz_add(&r, this, &b);

   return r;
}

ZZ_t ZZ_t::operator-(const ZZ_t& b)
{
   ZZ_t r;

   zz_sub(&r, this, &b);

   return r;
}

ZZ_t ZZ_t::operator*(long b)
{
   ZZ_t r;

   zz_mul_1(&r, this, b);

   return r;
}

ZZ_t ZZ_t::operator*(const ZZ_t& b)
{
   ZZ_t r;

   zz_mul(&r, this, &b);

   return r;
}

const ZZ_t ZZ_t::operator*=(const ZZ_t& b)
{
   ZZ_t r;

   zz_mul(&r, this, &b);
   zz_copy(this, &r);

   return r;
}

const ZZ_t ZZ_t::operator*=(long b)
{
   ZZ_t r;

   zz_mul_1(&r, this, b);
   zz_copy(this, &r);

   return r;
}

ZZ_t ZZ_t::operator/(const ZZ_t& b)
{
   ZZ_t q;

   long i;

   zz_div(&q, this, &b);

   return q;
}

const ZZ_t ZZ_t::operator/=(const ZZ_t& b)
{
   ZZ_t q;

   zz_div(&q, this, &b);
   zz_copy(this, &q);

   return q;
}

void divrem(ZZ_t& q, ZZ_t& r, const ZZ_t& a, const ZZ_t& b)
{
   zz_divrem(&q, &r, &a, &b);
}

/*ZZ_t::ZZ_t(const char * str)
{
}
*/

ZZ_t gcd(const ZZ_t& a, const ZZ_t& b)
{
   ZZ_t g;

   zz_gcd(&g, &a, &b);

   return g;
}

ostream& operator<<(ostream& os, const ZZ_t& a)
{
   char * str = zz_get_str(&a);
   
   if (a.size < 0)
      os << "-";
   os << str;
   
   free(str);

   return os;
}

void randbits(ZZ_t& r, rand_t state, long bits)
{
   zz_randbits(&r, state, bits);
}

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

ZZ_t fac(long n)
{
   return factorial(1, n);
}
