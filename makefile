CFLAGS = -O3 -Wall --std=gnu99

all: test

test: test.o bloom_golomb.o bloom_golomb.h
