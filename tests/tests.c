#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "../src/bitset/bitset.h"

// Тестирование создания/удаления множества
void test_create_destroy() {
	BitSet set = bitset_create(100);
	assert(set.bits != NULL && "Ошибка: множество не создано");
    bitset_destroy(&set);
	assert(set.bits == NULL && "Ошибка: множество не удалено");
    assert(set.size == 0 && "Ошибка: множество не удалено");
    assert(set.capacity == 0 && "Ошибка: множество не удалено");
}

// Тестирование добавления и проверки наличия элементов
void test_add_contains() {
	BitSet set = bitset_create(100);
	bitset_add(&set, 1);
	assert(bitset_contains(&set, 1) && "Ошибка: не удалось найти элемент");
	bitset_destroy(&set);
}

// Тестирование работы с некоторыми граничными значениями
void test_boundary() {
	BitSet set = bitset_create(65);
	bitset_add(&set, 0);
	bitset_add(&set, 64);
	assert(bitset_contains(&set, 0) && "Ошибка: 0 не найден");
	assert(bitset_contains(&set, 64) && "Ошибка: 64 не найден");
	bitset_destroy(&set);
}

// Тестирование времени выполнения
void test_performance() {
	const size_t N = 1000000;
	BitSet set = bitset_create(N);
	clock_t start = clock();
	for (size_t iter = 0; iter < N; iter++)
		bitset_add(&set, iter);
	clock_t end = clock();
	printf("Добавление %zu элементов заняло %.3f секунд.\n", N, (double)(end - start) / CLOCKS_PER_SEC);
	bitset_destroy(&set);
}

// Анализ утечек памяти (запускать с valgrind)
void test_memory_leak() {
	const size_t N = 1000;
	BitSet set = bitset_create(N);
	for (size_t iter = 0; iter < N; iter++)
		bitset_add(&set, iter);
	bitset_destroy(&set);
}

// Тестирование вычисления выражения
void test_compute_expression() {
    size_t capacity = 100;
    BitSet universe = bitset_create(capacity);
    for (size_t i = 0; i < capacity; i++) {
        bitset_add(&universe, i);
    }

    BitSet A = bitset_create(capacity);
    bitset_add(&A, 1);
    bitset_add(&A, 3);
    bitset_add(&A, 5);

    BitSet B = bitset_create(capacity);
    bitset_add(&B, 3);
    bitset_add(&B, 4);
    bitset_add(&B, 5);

    BitSet C = bitset_create(capacity);
    bitset_add(&C, 2);
    bitset_add(&C, 6);

    BitSet D = bitset_create(capacity);
    bitset_add(&D, 1);
    bitset_add(&D, 5);

    BitSet result = compute_expression(&A, &B, &C, &D, &universe);

    bitset_destroy(&A);
    bitset_destroy(&B);
    bitset_destroy(&C);
    bitset_destroy(&D);
    bitset_destroy(&universe);
    bitset_destroy(&result);
}

int main() {
    printf("Запуск тестов...\n");
	sleep(1);
    printf("Тестирование создания/удаления множества..\n");
    test_create_destroy();
    sleep(1);
	printf("Тестирование добавления и проверки наличия элементов\n");
	test_add_contains();
	sleep(1);
	printf("Тестирование работы с граничными значениями..\n");
    test_boundary();
	sleep(1);
	printf("Тестирование времени выполнения..\n");
    test_performance();
	sleep(1);
	printf("Анализ утечек памяти..\n");
    test_memory_leak();
	sleep(1);
	printf("Тестирование вычисления выражения..\n");
	test_compute_expression();
	sleep(1);
    printf("Все тесты пройдены!\n");
    return 0;
}
