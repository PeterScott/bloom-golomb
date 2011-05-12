Golomb coding for compressed Bloom filters. (Work in progress)
===========================================

This provides the basic code for encoding and decoding counting bloom
filters with a Golomb code. Technically a Rice code, since it only
supports divisors that are powers of two. From this base, you can make
a compressed Bloom filter without much additional trouble.

API
---

To determine the length of the compressed form, there is a function
`bloom_compressed_bits(int x, int M)` which will return the number of
bits in the Rice-compressed representation of x, where M is a power of
two. Use this to determine how big an array to allocate for the
compressed values.

You can use `bloom_compressed_bits_nibbles()` on an array of 4-bit
nibbles to get the number of bits after compression. FIXME: have this tell the intervals, not the numbers themselves.

FIXME: expand on this as the code expands.
