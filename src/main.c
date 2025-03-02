#include <stdio.h>

#include "bitset.h"
#include "output.h"

int main() {
	BitSet A = bitset_create(100);
    BitSet B = bitset_create(100);
    BitSet C = bitset_create(100);
    BitSet D = bitset_create(100);
    BitSet universe = bitset_create(7);

    bitset_add(&A, 1);
    bitset_add(&A, 2);
    bitset_add(&A, 3);

    bitset_add(&B, 2);
    bitset_add(&B, 3);
    bitset_add(&B, 4);

    bitset_add(&C, 3);
    bitset_add(&C, 4);

    bitset_add(&D, 1);
    bitset_add(&D, 4);
    bitset_add(&D, 5);

    bitset_add(&universe, 1);
    bitset_add(&universe, 2);
    bitset_add(&universe, 3);
    bitset_add(&universe, 4);
    bitset_add(&universe, 5);
    bitset_add(&universe, 6);

    printf("A = ");
    output_to_stdout(&A);
    printf("B = ");
    output_to_stdout(&B);
    printf("C = ");
    output_to_stdout(&C);
    printf("D = ");
    output_to_stdout(&D);
    printf("Универсум = ");
    output_to_stdout(&universe);

    BitSet result = compute_expression(&A, &B, &C, &D, &universe);

    printf("Результат выражения (A △ B)' ∪ C − D ∩ A ∪ B − C ∩ D = ");
    output_to_stdout(&result);
	output_to_file("/home/ethelay/bitset_project/result.txt", &result);

    bitset_destroy(&A);
    bitset_destroy(&B);
    bitset_destroy(&C);
    bitset_destroy(&D);
    bitset_destroy(&universe);
    bitset_destroy(&result);

    return 0;
}
