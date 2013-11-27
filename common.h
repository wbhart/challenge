#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

#if ULONG_MAX == 4294967295U /* 32 bit unsigned long */
typedef uint32_t word_t;
typedef int32_t sword_t;
typedef unsigned int dword_t __attribute__((mode(DI)));
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
      (nn_t) (__t = (__tmp_t *) alloca(sizeof(__tmp_t)), \
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

