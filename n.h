#include "common.h"

#ifndef N_H
#define N_H

#ifdef __cplusplus
 extern "C" {
#endif

#define n_leading_zeroes __builtin_clzl

#define n_divrem_21(q, hi, lo, n)                                         \
   do {                                                                   \
      const dword_t __u = ((dword_t) (hi) << WORD_BITS) + (dword_t) (lo); \
      (q) = __u / (n);                                                    \
      (lo) = __u % (n);                                                   \
   } while (0)

#define n_div_21(q, hi, lo, n)                                            \
   do {                                                                   \
      const dword_t __u = ((dword_t) (hi) << WORD_BITS) + (dword_t) (lo); \
      (q) = __u / (n);                                                    \
   } while (0)

word_t n_preinv(word_t n);

word_t n_randword(rand_t state);

word_t n_randint(rand_t state, word_t limit);

word_t n_randbits(rand_t state, unsigned int bits);

#ifdef __cplusplus
 }
#endif

#endif
