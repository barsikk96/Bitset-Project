#ifndef OUTPUT_H
#define OUTPUT_H
#include "bitset.h"

void output_to_stdout(const BitSet* set);
void output_to_file(const char* path, const BitSet* set);

#endif
