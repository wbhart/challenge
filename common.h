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

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

#ifdef _MSC_VER
#include "malloc.h"
#define ALLOCA _alloca
#else
#define ALLOCA alloca
#endif

#if ULONG_MAX == 4294967295U /* 32 bit unsigned long */
typedef uint32_t word_t;
typedef int32_t sword_t;
typedef uint64_t dword_t;
#define WORD_BITS 32

#else /* 64 bit unsigned long */
typedef uint64_t word_t;
typedef int64_t sword_t;
typedef unsigned int dword_t __attribute__((mode(TI)));
#define WORD_BITS 64
#endif

#define ABS(a) \
   ((a) >= 0 ? (a) : -(a))

#define MIN(a, b) \
   ((a) >= (b) ? (b) : (a))

#define MAX(a, b) \
   ((a) >= (b) ? (a) : (b))

#define SWAP(a, b)    \
   do {               \
      long __t = (a); \
      (a) = (b);      \
      (b) = __t;      \
   } while (0)

#define TMP_INIT \
   typedef struct __tmp_struct { \
      void * block; \
      struct __tmp_struct * next; \
   } __tmp_t; \
   __tmp_t * __tmp_root; \
   __tmp_t * __t

#define TMP_START \
   __tmp_root = NULL

#define TMP_ALLOC(size) \
   ((size) > 8192 ? \
      (nn_t) (__t = (__tmp_t *) ALLOCA(sizeof(__tmp_t)), \
       __t->next = __tmp_root, \
       __tmp_root = __t, \
       __t->block = (nn_t) malloc(size)) : \
      (nn_t) alloca(size))

#define TMP_END \
   while (__tmp_root) { \
      free(__tmp_root->block); \
      __tmp_root = __tmp_root->next; \
   }

typedef struct
{
    word_t __rand1;
    word_t __rand2;
} rand_s;

typedef rand_s rand_t[1];

static __inline__
void randinit(rand_t state)
{
#if WORD_BITS == 64
    state->__rand1 = 13845646450878251009UL;
    state->__rand2 = 13142370077570254774UL;
#else
    state->__rand1 = 4187301858UL;
    state->__rand2 = 3721271368UL;
#endif
}
#endif

