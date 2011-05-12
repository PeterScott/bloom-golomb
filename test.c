#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bloom_golomb.h"

#define PACKB(hi, lo) (((hi) << 4) | (lo))

int main(void) {
  /* 3141592653587. The 0 is padding. Best M is 4. */
  uint8_t arr[] = {PACKB(3, 1), PACKB(4, 1), PACKB(5, 9), PACKB(2, 6),
                   PACKB(5, 3), PACKB(5, 8), PACKB(7, 0)};
  int n = 13;

  printf("Length with M=4: %i (should be 49)\n",
         bloom_compressed_bits_nibbles(arr, n, 4, 2));

  printf("Length with M=2: %i (should be 51)\n",
         bloom_compressed_bits_nibbles(arr, n, 2, 1));

  return 0;
}
