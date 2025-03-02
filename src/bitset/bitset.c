#include "bitset.h"

// Создает битовое множество заданной ёмкости
BitSet bitset_create(size_t capacity) {
    BitSet set;
    set.capacity = capacity;
    set.size = (capacity + 63) >> 6; // Делим на 64, округляя вверх, так как каждый элемент — 64-битный блок
    set.bits = (uint64_t*)calloc(set.size, sizeof(uint64_t)); // Выделяем память под массив и обнуляем его
    return set;
}

// Освобождает память, занятую битовым множеством
void bitset_destroy(BitSet* set) {
    free(set->bits); // Освобождаем выделенную память
    set->bits = NULL;
    set->size = 0;
    set->capacity = 0;
}

// Добавляет элемент в битовое множество
void bitset_add(BitSet* set, int element) {
    if (element >= 0 && (size_t)element < set->capacity) {
        size_t index = element >> 6; // Определяем индекс 64-битного блока
        uint64_t mask = 1ULL << (element % 64); // Определяем бит внутри блока
        set->bits[index] |= mask; // Устанавливаем соответствующий бит
    }
}

// Проверяет, содержится ли элемент в множестве
bool bitset_contains(const BitSet* set, int element) {
    if (element >= 0 && (size_t)element < set->capacity) {
        size_t index = element >> 6; // Определяем индекс 64-битного блока
        uint64_t mask = 1ULL << (element % 64); // Определяем бит внутри блока
        return (set->bits[index] & mask) != 0; // Проверяем, установлен ли бит
    }
    return false;
}

// Подсчитывает количество установленных битов (элементов) в множестве
size_t count_num_bitset(BitSet* set) {
    size_t count = 0;
    for (size_t i = 0; i < set->capacity; i++) {
        if (set->bits[i >> 6] & (1ULL << (i % 64))) { // Проверяем каждый бит во всех блоках
            count++;
        }
    }
    return count;
}

// Проверяет, включается ли set1 в set2
void enabling_bitset(BitSet* set1, BitSet* set2) {
    char flag = 0;
    for (size_t i = 0; i < set1->capacity && flag == 0; i++) {
        if (set1->bits[i >> 6] & (1ULL << (i % 64))) { // Если бит установлен в set1
            if (!bitset_contains(set2, i)) { // Но отсутствует в set2
                printf("Множество не включается\n");
                flag = 1;
            }
        }
    }
    if (flag == 0) {
        printf("Множество включается\n");
    }
}

// Объединяет два множества (set1 |= set2)
void bitset_union(BitSet* set1, const BitSet* set2) {
    int flag = 0;
    if (set1->size < set2->size) {
        set1->bits = (uint64_t*)realloc(set1->bits, set2->size * sizeof(uint64_t)); // Расширяем массив
        if (set1->bits == NULL) {
            perror("Не удалось выделить память для set1");
            flag = 1;
        }
        if (flag == 0) {
            memset(set1->bits + set1->size, 0, (set2->size - set1->size) * sizeof(uint64_t)); // Обнуляем новые элементы
            set1->size = set2->size;
        }
    }
    if (set1->capacity < set2->capacity && flag == 0) {
        set1->capacity = set2->capacity;
    }
    for (size_t iter = 0; iter < set2->size && flag == 0; iter++) {
        set1->bits[iter] |= set2->bits[iter]; // Объединяем побитово
    }
}

// Пересечение множеств (set1 &= set2)
void bitset_intersection(BitSet* set1, const BitSet* set2) {
    size_t min_size = (set1->size < set2->size) ? set1->size : set2->size;
    for (size_t i = 0; i < min_size; i++) {
        set1->bits[i] &= set2->bits[i]; // Побитовое И для пересечения
    }
    for (size_t i = min_size; i < set1->size; i++) {
        set1->bits[i] = 0; // Очищаем остаток
    }
}

// Разность множеств (set1 -= set2)
void bitset_difference(BitSet* set1, const BitSet* set2) {
    size_t min_size = (set1->size < set2->size) ? set1->size : set2->size;
    for (size_t i = 0; i < min_size; i++) {
        set1->bits[i] &= ~set2->bits[i]; // Побитовое И с инверсией второго множества
    }
}

// Симметрическая разность (set1 ^= set2)
void bitset_symmetric_difference(BitSet* set1, const BitSet* set2) {
    size_t min_size = (set1->size < set2->size) ? set1->size : set2->size;
    for (size_t i = 0; i < min_size; i++) {
        set1->bits[i] ^= set2->bits[i]; // Побитовое XOR для нахождения различий
    }
}

// Дополнение множества относительно универсального множества
void bitset_complement(BitSet* set, const BitSet* universe) {
    for (size_t i = 0; i < universe->size; i++) {
        if (i < set->size) {
            set->bits[i] = ~set->bits[i] & universe->bits[i]; // Инвертируем set и ограничиваем universe
        } else {
            uint64_t new_block = ~0ULL & universe->bits[i]; // Заполняем недостающие блоки
            set->bits = (uint64_t*)realloc(set->bits, (i + 1) * sizeof(uint64_t)); // Расширяем массив
            set->size = i + 1;
            set->capacity = universe->capacity;
            set->bits[i] = new_block;
        }
    }
    for (size_t i = universe->size; i < set->size; i++) {
        set->bits[i] = 0; // Очищаем лишние элементы
    }
}

BitSet compute_expression(const BitSet* A, const BitSet* B, const BitSet* C, const BitSet* D, const BitSet* universe) {
    BitSet result = bitset_create(A->capacity); // Создаем пустое множество result с той же вместимостью, что и множество A


    BitSet temp1 = bitset_create(A->capacity); // Создаем временное множество temp1 с той же вместимостью, что и множество A

    // Вычисляем выражение: (A ∪ B) △ B̅ ∪ C
    bitset_union(&temp1, A); // 1) Объединяем множества A и B, результат сохраняем в temp1
    bitset_union(&temp1, B);
	bitset_symmetric_difference(&temp1, B); // 2) Выполняем симметрическую разность temp1 и B (A △ B)
    bitset_complement(&temp1, universe);    // 3) Вычисляем дополнение temp1 относительно универсального множества universe (B̅)
    bitset_union(&temp1, C); // 4) Объединяем результат с множеством C

    BitSet temp2 = bitset_create(D->capacity); // Создаем временное множество temp2 с той же вместимостью, что и множество D

    // Вычисляем выражение: (A ∩ D) ∪ B
    bitset_intersection(&temp2, A);	// 1) Выполняем пересечение множеств A и D, результат сохраняем в temp2
    bitset_intersection(&temp2, D);
    bitset_union(&temp2, B); // 2) Объединяем результат с множеством B

    BitSet temp3 = bitset_create(C->capacity); // Создаем временное множество temp3 с той же вместимостью, что и множество C

    // Вычисляем выражение: C ∩ D
    bitset_intersection(&temp3, C);	// 1. Выполняем пересечение множеств C и D, результат сохраняем в temp3
    bitset_intersection(&temp3, D);

    // Вычисляем финальное выражение: temp1 - temp2 - temp3
    bitset_difference(&temp1, &temp2); // 1. Вычитаем из temp1 множество temp2
    bitset_difference(&temp1, &temp3); // 2. Вычитаем из temp1 множество temp3

    bitset_union(&result, &temp1); // Объединяем результат с множеством result


    // Освобождаем память, выделенную для временных множеств
    bitset_destroy(&temp1);
    bitset_destroy(&temp2);
    bitset_destroy(&temp3);

    // Возвращаем итоговое множество result
    return result;
}

