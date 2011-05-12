/* Golomb coding for compressed Bloom filters.
 * 
 * This provides the basic code for encoding and decoding counting
 * bloom filters with a Golomb code. Technically a Rice code, since it
 * only supports divisors that are powers of two. From this base, you
 * can make a compressed Bloom filter without much additional trouble.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bloom_golomb.h"

#define HIGH_NIBBLE(byte) (((byte) & 0xF0) >> 4)
#define LOW_NIBBLE(byte)  ((byte) & 0x0F)

/* Return number of bits in the Rice-encoded representation of x,
   where M is a power of two. For efficiency, also pass in
   log_2(M). */
int bloom_compressed_bits(int x, int M, int log2_M) {
  return (x/M + 1) + log2_M;
}

/* Get number of bits needed for compressed version of a nibble
   array of length n. */
int bloom_compressed_bits_nibbles(uint8_t *array, int n, int M, int log2_M) {
  int bits = 0;
  uint8_t byte = 0;

  for (int i = 0; i < n/2; i++) {
    byte = array[i];
    bits += bloom_compressed_bits(HIGH_NIBBLE(byte), M, log2_M);
    bits += bloom_compressed_bits(LOW_NIBBLE(byte), M, log2_M);
  }
  
  /* Deal with odd-numbered nibble arrays. */
  if (n & 1) {
    bits += bloom_compressed_bits(HIGH_NIBBLE(array[n/2]), M, log2_M);
  }
  
  return bits;
}


/* Bit vector operations: we need to be able to support two writing
 * operations:
 *
 * 1. Write n zeros, followed by a 1.
 * 2. Write an n-bit value in binary.
 *
 * Each of these is relative to a current index. We also need the
 * reading equivalents of these: return number of zeros until the next
 * 1 (can be accelerated with the __builtin_clz GCC intrinsic) and get
 * the value of the next n bits. Also we should have one to skip the
 * next n bits.
 *
 * All this is accessed via high-level traversal macros.
 */

/* Get bit i from bitvector. No bounds checking. */
inline int getbit_bv(uint8_t *bitvec, int i) {
  int byte = i / 8;
  int offset = i % 8;

  return ((bitvec[byte] << offset) & 128) >> 7;
}

/* Set bit i in a bitvector. No bounds-checking. IMPORTANT: only works
   if the current value is zero! */
inline void setbit_bv(uint8_t *bitvec, int i) {
  int byte = i / 8;
  int offset = i % 8;

  bitvec[byte] |= 128 >> offset;
}

/* Print a bit vector of length n. */
void print_bitvec(uint8_t *bitvec, int n) {
  for (int i = 0; i < n; i++)
    putchar(getbit_bv(bitvec, i) ? '1' : '0');
  putchar('\n');
}

/* Allocate and return a new bit vector of length n. */
uint8_t *new_bitvec(int n) {
  int bytes = n / 8;
  return malloc(bytes + ((n % 8) ? 1 : 0));
}

