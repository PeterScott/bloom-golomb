#ifndef __BLOOM_GOLOMB_H
#define __BLOOM_GOLOMB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int bloom_compressed_bits(int x, int M, int log2_M);
int bloom_compressed_bits_nibbles(uint8_t *array, int n, int M, int log2_M);

#endif
