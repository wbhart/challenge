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

using namespace std;

#ifndef POLY_CPP_H
#define POLY_CPP_H

template <class T>
class Poly : public vector<T> {
public:
   
   Poly() : vector<T>() {}

   Poly(const char * str);

   int operator==(long c);
   int operator!=(long c) { return !(*this == c); }

   int operator==(const Poly<T>& b);
   int operator!=(const Poly<T>& b) { return !(*this == b); }

   Poly<T> operator-() const;

   Poly<T> operator+(const Poly<T>& b);
   Poly<T> operator-(const Poly<T>& b);
   Poly<T> operator*(const Poly<T>& b);

   const Poly<T> operator+=(const Poly<T>& b);
};

/* w.b. hart */
template <class T>
long set_str(Poly<T>& a, const char * str)
{
   long i, j, len = atoi(str);

   i = strspn(str, "0123456789");
   i += strspn(str + i, " \t\n\r");

   for (j = 0; j < len; j++) {
      a.push_back(T());
      i += set_str(a[j], str + i);
      i += strspn(str + i, " \t\n\r");
   }

   normalise(a);
}

/* w.b. hart */
template <class T>
Poly<T>::Poly(const char * str)
{
   set_str(*this, str);
}

/* w.b. hart */
template <class T>
void normalise(Poly<T>& a)
{
   while (!a.empty() && a.back() == 0)
      a.pop_back();
}

/* w.b. hart */
template <class T>
int Poly<T>::operator==(const Poly<T>& b)
{
   long i;
   long len1 = (*this).size(), len2 = b.size();

   if (len1 != len2)
      return 0;

   for (i = i; i < len1; i++) {
      if ((*this)[i] != b[i])
         return 0;
   }

   return 1;
}
   
/* w.b. hart */
template <class T>
int Poly<T>::operator==(long c)
{
   if (c == 0)
      return (*this).size() == 0;

   return (*this).size() == 1 && (*this)[0] == c;
}
   
/* w.b. hart */
template <class T>
Poly<T> Poly<T>::operator-() const
{
   long i, len = (*this).size();
   Poly<T> r;

   r.resize(len);

   for (i = 0; i < len; i++)
      r[i] = -(*this)[i];

   return r;
}

/* w.b. hart */
template <class T>
void random(Poly<T>& r, rand_t state, va_list dims)
{
   long i, len = va_arg(dims, long);
   va_list args;

   r.resize(len);

   for (i = 0; i < len; i++)
   {
      va_copy(args, dims);
      random(r[i], state, args);
      va_end(args);
   }

   normalise(r);
}

template <class T>
void random(Poly<T>& r, rand_t state, ...)
{
   va_list args;

   va_start(args, state);

   random(r, state, args);
      
   va_end(args);
}

/* w.b. hart */
template <class T>
Poly<T> Poly<T>::operator+(const Poly<T>& b)
{
   Poly<T> r;
   long len1 = (*this).size();
   long len2 = b.size(), i;
   long min = MIN(len1, len2);
   long max = MAX(len1, len2);

   r.resize(max);

   for (i = 0; i < min; i++)
      r[i] = (*this)[i] + b[i];
   
   for ( ; i < len1; i++)
      r[i] = (*this)[i];

   for ( ; i < len2; i++)
      r[i] = b[i];

   normalise(r);

   return r;
}

/* w.b. hart */
template <class T>
Poly<T> Poly<T>::operator-(const Poly<T>& b)
{
   Poly<T> r;
   long len1 = this->size();
   long len2 = b.size(), i;
   long min = MIN(len1, len2);
   long max = MAX(len1, len2);

   r.resize(max);

   for (i = 0; i < min; i++)
      r[i] = (*this)[i] - b[i];
   
   for ( ; i < len1; i++)
      r[i] = (*this)[i];

   for ( ; i < len2; i++)
      r[i] = -b[i];

   normalise(r);

   return r;
}

/* w.b. hart */
template <class T>
Poly<T> Poly<T>::operator*(const Poly<T>& b)
{
   Poly<T> r;
   long len1 = this->size();
   long len2 = b.size(), i, j;
   long rlen = len1 + len2;

   if (len1 == 0 || len2 == 0)
      return r;

   r.resize(rlen);

   for (i = 0; i < len1; i++)
      r[i] = (*this)[i]*b[0];

   for (j = 1; j < len2; j++)
      r[len1 + j - 1] = (*this)[len1 - 1]*b[j];

   for (i = 0; i < len1 - 1; i++)
      for (j = 1; j < len2; j++)
         r[i + j] += (*this)[i]*b[j];

   normalise(r);

   return r;
}

/* w.b. hart */
template <class T>
const Poly<T> Poly<T>::operator+=(const Poly<T>& b)
{
   Poly<T> r;

   r = (*this) + b;
   (*this) = r;
   return r;
}

/* w.b. hart */
template <class T>
ostream& operator<<(ostream& os, const Poly<T>& p)
{
   long i, len = p.size();

   os << len;

   for (i = 0; i < len; i++)
      cout << " " << p[i];

   return os;
}

#endif
