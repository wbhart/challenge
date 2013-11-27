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

#endif

