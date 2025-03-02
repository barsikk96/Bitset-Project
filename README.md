# BitSet Project

## Описание
BitSet Project — это реализация битового множества на языке C, позволяющая эффективно выполнять операции над множествами, такие как объединение, пересечение, разность и симметрическая разность. Проект включает в себя поддержку операций над битовыми множествами и функцию вычисления сложного выражения.

## Структура проекта
```
bitset_project/
│── src/
│ │── bitset/
│ │ │── bitset.c
│ │ │── bitset.h
│ │── output/
│ │ │── output.c
│ │ │── output.h
│ │── main.c
│── tests/
│ │── tests.c
│── Makefile
│── result.txt
│── README.md
```

### Основные файлы:
- **bitset.c / bitset.h**: Реализация структуры `BitSet` и операций над битовыми множествами.
- **output.c / output.h**: Функции вывода множества на экран и в файл.
- **main.c**: Главная программа, демонстрирующая работу с битовыми множествами.
- **tests.c**: Набор тестов для проверки корректности работы битового множества.
- **Makefile**: Файл сборки проекта.
- **result.txt**: Файл для сохранения результатов вычислений.

## Компиляция и запуск

### Сборка проекта:
Для сборки проекта используйте команду:
```sh
make
```

### Запуск программы:
После успешной сборки выполните:
```sh
./bitset_project
```

## Функциональность
### Основные операции с множествами:
- `bitset_create(size_t capacity)`: Создает множество заданной ёмкости.
- `bitset_destroy(BitSet* set)`: Освобождает память, занятую множеством.
- `bitset_add(BitSet* set, int element)`: Добавляет элемент в множество.
- `bitset_contains(const BitSet* set, int element)`: Проверяет, содержится ли элемент в множестве.
- `bitset_union(BitSet* set1, const BitSet* set2)`: Объединяет два множества.
- `bitset_intersection(BitSet* set1, const BitSet* set2)`: Выполняет пересечение множеств.
- `bitset_difference(BitSet* set1, const BitSet* set2)`: Вычисляет разность множеств.
- `bitset_symmetric_difference(BitSet* set1, const BitSet* set2)`: Вычисляет симметрическую разность.
- `bitset_complement(BitSet* set, const BitSet* universe)`: Дополняет множество относительно универсального множества.

### Вычисление выражения:
Реализована функция `compute_expression`, вычисляющая следующее выражение:
```
(A △ B)' ∪ C − D ∩ A ∪ B − C ∩ D
```

## Тестирование

### Запуск тестов
Для проверки корректности работы битового множества выполните:
```sh
make test
./tests_run
```
Тесты проверяют:
- Создание и удаление множеств.
- Добавление и проверку наличия элементов.
- Граничные значения.
- Производительность операций.

## Авторы
Проект разработан для демонстрации работы с битовыми множествами в языке C.

## Лицензия
Этот проект распространяется под лицензией MIT.

------------------------------------------------------------------------------------------------------------------------------------------------------------

# BitSet Project  

## Description  
BitSet Project is an implementation of a bit set in C, allowing efficient set operations such as union, intersection, difference, and symmetric difference. The project includes:  

## Project Structure  
```
bitset_project/
│── src/
│ │── bitset/
│ │ │── bitset.c
│ │ │── bitset.h
│ │── output/
│ │ │── output.c
│ │ │── output.h
│ │── main.c
│── tests/
│ │── tests.c
│── Makefile
│── result.txt
│── README.md
```  

### Main Files:  
- **bitset.c / bitset.h**: Implementation of the `BitSet` structure and bit set operations.  
- **output.c / output.h**: Functions for displaying the set on screen and writing to a file.  
- **main.c**: The main program demonstrating bit set operations.  
- **tests.c**: A set of tests to verify the correctness of the bit set implementation.  
- **Makefile**: The project's build file.  
- **result.txt**: A file for storing computation results.  

## Compilation and Execution  

### Building the Project:  
To build the project, use the following command:  
```sh
make
```  

### Running the Program:  
After successful compilation, run:  
```sh
./bitset_project
```  

## Functionality  

### Main Set Operations:  
- `bitset_create(size_t capacity)`: Creates a set with the specified capacity.  
- `bitset_destroy(BitSet* set)`: Frees the memory occupied by the set.  
- `bitset_add(BitSet* set, int element)`: Adds an element to the set.  
- `bitset_contains(const BitSet* set, int element)`: Checks whether an element is in the set.  
- `bitset_union(BitSet* set1, const BitSet* set2)`: Performs a union of two sets.  
- `bitset_intersection(BitSet* set1, const BitSet* set2)`: Performs an intersection of two sets.  
- `bitset_difference(BitSet* set1, const BitSet* set2)`: Computes the difference between two sets.  
- `bitset_symmetric_difference(BitSet* set1, const BitSet* set2)`: Computes the symmetric difference of two sets.  
- `bitset_complement(BitSet* set, const BitSet* universe)`: Computes the complement of a set relative to the universal set.  

### Expression Computation:  
The project implements the function `compute_expression`, which evaluates the following expression:  
```
(A △ B)' ∪ C − D ∩ A ∪ B − C ∩ D
```  

## Testing  

### Running Tests  
To verify the correctness of the bit set implementation, run:  
```sh
make test
./tests_run
```  
The tests check:  
- Creation and deletion of sets.  
- Adding elements and checking for their presence.  
- Boundary values.  
- Performance of operations.  

## Authors  
This project was developed to demonstrate bit set operations in C.  

## License  
This project is distributed under the MIT license.  
