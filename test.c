#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bloom_golomb.h"

#define PACKB(hi, lo) (((hi) << 4) | (lo))

int main(void) {
  /* 3100592650587. */
  uint8_t arr[] = {PACKB(3, 1), PACKB(0, 0), PACKB(5, 9), PACKB(2, 6),
                   PACKB(5, 0), PACKB(5, 8), PACKB(7, 0)};
  int n = 13;

  printf("Length with M=4: %i (should be 150)\n",
         bloom_compressed_bits_nibbles(arr, n, 4, 2));

  printf("Length with M=2: %i (should be 102)\n",
         bloom_compressed_bits_nibbles(arr, n, 2, 1));

  printf("Length with M=1: %i  (should be 62)\n",
         bloom_compressed_bits_nibbles(arr, n, 1, 0));


  //printf("Length with M=2: %i (should be 17)\n",
  //       bloom_compressed_bits_nibbles(arr, 5, 2, 1));
  // Lengths: 0, 0, 1, 3, 0, 0, 0, 0

  return 0;
}
