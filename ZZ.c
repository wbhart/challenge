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

#include "ZZ.h"  

/******************************************************************************

   Constructors/destructors

******************************************************************************/

/* w.b. hart */
ZZ::ZZ(const char * str)
{
   int sgn = 0;
   long digits;
   
   if (str[0] == '-') {
      sgn = 1;
      str++;
   }

   digits = strspn(str, "0123456789");
   
   /* 0.0519... is log_{2^64}(10) */
   size = (long) ceil(0.0519051265 * digits * (64/WORD_BITS));
   n = (nn_t) malloc(sizeof(word_t)*size);
   alloc = size;

   digits = nn_set_str(n, &size, str);

   size = sgn ? -size : size;
}

/******************************************************************************

   Memory management

******************************************************************************/

/* w.b. hart */
void ZZ::fit(long m)
{
   if (m > alloc)
   {
      n = (nn_t) realloc(n, sizeof(word_t)*m);
      alloc = m;
   }
}

/* w.b. hart */
void ZZ::normalise()
{
   if (size < 0)
      size = -nn_normalise(n, -size);
   else
      size = nn_normalise(n, size);
}

/******************************************************************************

   I/O

******************************************************************************/

/* w.b. hart */
ostream& operator<<(ostream & os, ZZ& a)
{
   nn_t t;
   long usize = ABS(a.size);
   TMP_INIT;
   
   TMP_START;
   
   if (a.size < 0)
      os << "-";

   t = (nn_t) TMP_ALLOC(usize*sizeof(word_t));
  
   nn_copyi(t, a.n, usize);

   os << nn_get_str(t, usize);

   TMP_END;

   return os;
}

/* w.b. hart */
char * ZZ::to_string()
{
   nn_t t;
   long usize = ABS(size);
   char * str, * str2;
   TMP_INIT;
   
   TMP_START;
   
   t = TMP_ALLOC(usize*sizeof(word_t));

   nn_copyi(t, n, usize);

   str = nn_get_str(t, usize);

   TMP_END;

   if (size < 0) {
      long len = strlen(str);
      
      str2 = (char *) malloc(len + 1);
      str2[0] = '-';
      strcpy(str2 + 1, str); 
      
      free(str);
   } else
      str2 = str;

   return str2;
}

/******************************************************************************

   Assignment/swap

******************************************************************************/

ZZ& ZZ::operator=(int c)
{
   if (c == 0)
      size = 0;
   else if (c < 0)
   {
      fit(1);
      n[0] = -c;
      size = -1;
   } else
   {
      fit(1);
      n[0] = c;
      size = 1;
   }

   return *this;
}

ZZ& ZZ::operator=(long c)
{
   if (c == 0)
      size = 0;
   else if (c < 0)
   {
      fit(1);
      n[0] = -c;
      size = -1;
   } else
   {
      fit(1);
      n[0] = c;
      size = 1;
   }

   return *this;
}

ZZ& ZZ::operator=(const ZZ& c)
{
   long usize = ABS(c.size);

   if (this != &c)
   {
      fit(usize);
      nn_copyi(n, c.n, usize);
      size = c.size;
   }

   return *this;
}

/* w.b. hart */
void ZZ::swap(ZZ& b)
{
   nn_swap(n, b.n);
   SWAP(size, b.size);
   SWAP(alloc, b.alloc);
}

/******************************************************************************

   Comparison

******************************************************************************/

int ZZ::operator==(long c) const
{
   return c == 0 ? size == 0 : 
      (c < 0 ? size == -1 && n[0] == (word_t) -c : size == 1 && n[0] == (word_t) c);
}

int ZZ::operator==(const ZZ& c) const
{
   if (size != c.size)
      return 0;

   return nn_cmp(n, c.n, ABS(c.size)) == 0;
}

int ZZ::operator<(long c) const
{
   long csize;
   
   if (c == 0)
      return size < 0;

   csize = c < 0 ? -1 : 1;

   if (size < csize)
      return 1;
   else if (size > csize)
      return 0;
   else 
      return c < 0 ? (word_t) -c < n[0] : (word_t) c > n[0];
}

int ZZ::operator<(const ZZ& c) const
{
   if (size < c.size)
      return 1;
   else if (size > c.size)
      return 0;

   return nn_cmp(n, c.n, ABS(c.size)) < 0;
}

int ZZ::operator>(long c) const
{
   long csize;
   
   if (c == 0)
      return size > 0;

   csize = c < 0 ? -1 : 1;

   if (size > csize)
      return 1;
   else if (size < csize)
      return 0;
   else 
      return c < 0 ? (word_t) -c > n[0] : (word_t) c < n[0];
}

int ZZ::operator>(const ZZ& c) const
{
   if (size > c.size)
      return 1;
   else if (size < c.size)
      return 0;

   return nn_cmp(n, c.n, ABS(c.size)) > 0;
}

/* w.b. hart */
int cmpabs(const ZZ& a, const ZZ& b)
{
   long asize = ABS(a.size);
   long bsize = ABS(b.size);
   
   if (asize > bsize)
      return 1;
   else if (asize < bsize)
      return -1;

   return nn_cmp(a.n, b.n, asize);
}

/******************************************************************************

   Comparison

******************************************************************************/

/* w.b. hart */
void ZZ::randbits(rand_t state, long bits)
{
   long ubits = ABS(bits);
   size = (ubits + WORD_BITS - 1)/WORD_BITS;

   fit(size);

   nn_randbits(n, state, ubits);

   size = nn_normalise(n, size);
   size = (bits < 0 && n_randint(state, 2) == 0) ? -size : size;
}

/******************************************************************************

   Basic arithmetic

******************************************************************************/

/* w.b. hart */
void neg(ZZ& r, const ZZ& a)
{
   if (r != a) {
      long usize = ABS(a.size);
      r.fit(usize);
      
      nn_copyi(r.n, a.n, usize);
   }

   r.size = -a.size;
}

/* w.b. hart */
void add(ZZ& r, const ZZ& a, const ZZ& b)
{
   long asize = ABS(a.size);
   long bsize = ABS(b.size);
   long rsize;

   if (asize < bsize) {
      add(r, b, a);
      
      return;
   }
   
   r.fit(asize + 1);

   if ((a.size ^ b.size) < 0) {
      word_t bi = nn_sub(r.n, a.n, asize, b.n, bsize, 0);
      rsize = a.size;
      
      if (bi != 0) {
         nn_neg(r.n, r.n, asize, 0);
         rsize = -rsize;
      }
   } else {
      r.n[asize] = nn_add(r.n, a.n, asize, b.n, bsize, 0);
      rsize = asize + 1;
      if (a.size < 0) rsize = -rsize;
   }

   r.size = rsize;
   r.normalise();
}

/* w.b. hart */
void sub(ZZ& r, const ZZ& a, const ZZ& b)
{
   long asize = ABS(a.size);
   long bsize = ABS(b.size);
   long rsize;
   
   if (asize < bsize) {
      sub(r, b, a);
      r.size = -r.size;

      return;
   }
   
   r.fit(asize + 1);

   if ((a.size ^ b.size) >= 0) {
      word_t bi = nn_sub(r.n, a.n, asize, b.n, bsize, 0);
      rsize = a.size;
      
      if (bi) {
         nn_neg(r.n, r.n, asize, 0);
         rsize = -rsize;
      }
   } else {
      r.n[asize] = nn_add(r.n, a.n, asize, b.n, bsize, 0);
      rsize = asize + 1;
      if (a.size < 0) rsize = -rsize;
   }

   r.size = rsize;
   r.normalise();
}

/* w.b. hart */
void add(ZZ& r, const ZZ& a, long c)
{
   long usize = ABS(a.size);

   if (c < 0) {
      sub(r, a, -c);
       
      return;
   }

   r.fit(usize + 1);
   
   if (a.size >= 0) {
      r.n[usize] = nn_add_1(r.n, a.n, usize, c);
      r.size = nn_normalise(r.n, usize + 1);
   } else if (usize == 1) {
      word_t d = a.n[0];
      if (d == (word_t) c)
         r.size = 0;
      else {
         r.n[0] = d > (word_t) c ? d - c : c - d;
         r.size = d > (word_t) c ? -1 : 1;
      }
   } else {
      nn_sub_1(r.n, a.n, usize, c);
      r.size = -nn_normalise(r.n, usize);
   }
}

/* w.b. hart */
void sub(ZZ& r, const ZZ& a, long c)
{
   long usize = ABS(a.size);
   
   if (c < 0) {
      add(r, a, -c);
       
      return;
   }

   r.fit(usize + 1);
   
   if (a.size == 0) {
      r.size = -1;
      r.n[0] = c;
   } else {
      if (a.size < 0) {
         r.n[usize] = nn_add_1(r.n, a.n, usize, c);
         r.size = -nn_normalise(r.n, usize + 1);
      } else if (usize == 1) {
         word_t d = a.n[0];
         if (d == (word_t) c)
            r.size = 0;
         else {
            r.n[0] = d > (word_t) c ? d - c : c - d;
            r.size = d > (word_t) c ? 1 : -1;
         }
      } else {
         nn_sub_1(r.n, a.n, usize, c);
         r.size = nn_normalise(r.n, usize);
      }
   }
}

/* w.b. hart */
void mul_2exp(ZZ& r, const ZZ& a, long exp)
{
   if (a.size == 0)
      r.size = 0;
   else
   {
      int bits = exp & (WORD_BITS - 1);
      long words = exp / WORD_BITS;
      long usize = ABS(a.size);
      long rsize = usize + words;
   
      r.fit(rsize + (bits != 0));

      if (bits == 0)
         nn_copyd(r.n + words, a.n, usize);
      else {
         word_t ci = r.n[rsize] = nn_shl(r.n + words, a.n, usize, bits, 0);
         rsize += (ci != 0);  
      }

      nn_zero(r.n, words);
      r.size = a.size >= 0 ? rsize : -rsize;
   }
}

/* w.b. hart */
void div_2exp(ZZ& r, const ZZ& a, long exp)
{
   int bits = exp & (WORD_BITS - 1);
   long words = exp / WORD_BITS;
   long usize = ABS(a.size);
   long rsize = usize - words;
   
   if (rsize <= 0)
      r.size = 0;
   else {
      r.fit(rsize);

      if (bits == 0)
         nn_copyi(r.n, a.n + words, rsize);
      else {
         nn_shr(r.n, a.n + words, rsize, bits, 0);
         rsize -= (r.n[rsize - 1] == 0);  
      }

      r.size = a.size >= 0 ? rsize : -rsize;
   }
}

/* w.b. hart */
long divrem(ZZ& q, const ZZ& a, long b)
{
   long asize = ABS(a.size);
   long r, qsize = asize;
   ZZ t;

   if (asize == 0) {
      q.size = 0;
      r = b;
   } else {
      t = a;

      q.fit(qsize);
   
      r = nn_divrem_1(q.n, t.n, asize, ABS(b), 0);
         
      qsize -= q.n[qsize - 1] == 0;
      
      q.size = (a.size ^ b) >= 0 ? qsize : -qsize;
      r = a.size >= 0 ? r : -r;

      if (q.size < 0 && r != 0) {
         sub(q, q, 1);
         r += b;
      }
   }

   return r;
}

/* w.b. hart */
void mul(ZZ& r, const ZZ& a, long c)
{
   long usize = ABS(a.size);

   if (c < 0) {
      mul(r, a, -c);
      r.size = -r.size;

      return;
   }
   
   if (c == 0 || usize == 0)
      r.size = 0;
   else
   {
      r.fit(usize + 1);

      r.n[usize] = nn_mul_1(r.n, a.n, usize, c, 0);
      usize += (r.n[usize] != 0);

      r.size = a.size >= 0 ? usize : -usize;
   }
}

/******************************************************************************

   Quadratic time arithmetic

******************************************************************************/

/* w.b. hart */
void mul(ZZ& r, const ZZ& a, const ZZ& b)
{
   long asize = ABS(a.size);
   long bsize = ABS(b.size);
   long rsize = asize + bsize;
   
   if (asize == 0 || bsize == 0)
      r.size = 0;
   else {
      if (asize < bsize) {
         mul(r, b, a);
         
         return;
      }

      r.fit(rsize);

      nn_mul(r.n, a.n, asize, b.n, bsize);
      rsize -= (r.n[rsize - 1] == 0);

      r.size = (a.size ^ b.size) < 0 ? -rsize : rsize;
   }
}

/* w.b. hart */
void divrem(ZZ& q, ZZ& r, const ZZ& a, const ZZ& b)
{
   long asize = ABS(a.size);
   long bsize = ABS(b.size);
   long rsize = bsize;
   long qsize = asize - bsize + 1;
   
   r = a;

   if (asize < bsize)
      q.size = 0;
   else {
      q.fit(qsize);
   
      nn_divrem(q.n, r.n, asize, b.n, bsize);
         
      qsize -= q.n[qsize - 1] == 0;
      rsize = nn_normalise(r.n, rsize);

      q.size = (a.size ^ b.size) >= 0 ? qsize : -qsize;
      r.size = a.size >= 0 ? rsize : -rsize;

      if (q.size < 0 && r.size != 0) {
         sub(q, q, 1);
         add(r, r, b);
      }
   }
}

void div(ZZ& q, const ZZ& a, const ZZ& b)
{
   long asize = ABS(a.size);
   long bsize = ABS(b.size);
   long rsize = bsize;
   long qsize = asize - bsize + 1;
   long qsign = (a.size ^ b.size);
   
   if (asize < bsize)
      q.size = 0;
   else {
      ZZ r(a);

      q.fit(qsize);
   
      if (qsign < 0) {
         nn_divrem(q.n, r.n, asize, b.n, bsize);
         rsize = nn_normalise(r.n, rsize);
      } else
         nn_div(q.n, r.n, asize, b.n, bsize);

      qsize -= q.n[qsize - 1] == 0;
      q.size = qsign >= 0 ? qsize : -qsize;
      
      if (q.size < 0 && rsize != 0)
         sub(q, q, 1);
   }
}

/* w.b. hart -- inspired by Peter Luschny's implementation */
void larem(ZZ& r, const ZZ& a, const ZZ& b)
{
   long asize = ABS(a.size);
   long bsize = ABS(b.size);
   long rsize = bsize;
   long qsize = asize - bsize + 1;
   ZZ q, h, t(a);

   h.fit(asize);

   div_2exp(h, a, 1);
   if (a.size < 0)
      add(h, h, 1);

   if (asize >= bsize) {
      q.fit(qsize);
   
      nn_divrem(q.n, t.n, asize, b.n, bsize);
         
      rsize = nn_normalise(t.n, rsize);

      t.size = a.size >= 0 ? rsize : -rsize;

      if ((a.size ^ b.size) < 0 && t.size != 0 && cmpabs(t, h) >= 0)
         add(t, t, b);
      else if (cmpabs(t, h) >= 0)
         sub(t, t, b);
   }

   t.swap(r);
}

/* w.b. hart */
void gcd(ZZ& g, const ZZ& a, const ZZ& b)
{
   long asize = ABS(a.size);
   long bsize = ABS(b.size);
   long size;
   nn_t ta, tb;
   TMP_INIT;

   if (asize == 0)
      g = b;
   else if (bsize == 0)
      g = a;
   else {
      if (asize < bsize) {
         gcd(g, b, a);
         
         return;
      }
      
      TMP_START;

      ta = TMP_ALLOC(asize*sizeof(word_t));
      tb = TMP_ALLOC(bsize*sizeof(word_t));

      nn_copyi(ta, a.n, asize);
      nn_copyi(tb, b.n, bsize);

      g.fit(bsize);
      size = nn_gcd(g.n, ta, asize, tb, bsize);
      
      g.size = (a.size & b.size) < 0 ? -size : size;

      TMP_END;
   }
}
