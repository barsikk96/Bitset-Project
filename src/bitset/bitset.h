#ifndef BITSET_H
#define BITSET_H
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	uint64_t* bits;
	size_t size;
	size_t capacity;
} BitSet;

BitSet bitset_create(size_t capacity);

void bitset_destroy(BitSet* set);

void bitset_add(BitSet* set, int element);

bool bitset_contains(const BitSet* set, int element);

size_t count_num_bitset(BitSet* set);

void enabling_bitset(BitSet* set1, BitSet* set2);

void bitset_union(BitSet* set1, const BitSet* set2);

void bitset_intersection(BitSet* set1, const BitSet* set2);

void bitset_difference(BitSet* set1, const BitSet* set2);

void bitset_symmetric_difference(BitSet* set1, const BitSet* set2);

void bitset_complement(BitSet* set, const BitSet* universe);

BitSet compute_expression(const BitSet* A, const BitSet* B, const BitSet* C, const BitSet* D, const BitSet* universe);

#endif
