CC = gcc

CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG -I$(SRC_DIR) -I$(BITSET_DIR) -I$(OUTPUT_DIR) -fsanitize=address

SRC_DIR = src
BITSET_DIR = $(SRC_DIR)/bitset
OUTPUT_DIR = $(SRC_DIR)/output
TESTS_DIR = tests

OBJ = $(SRC_DIR)/main.o $(BITSET_DIR)/bitset.o $(OUTPUT_DIR)/output.o
TEST_OBJ = $(TESTS_DIR)/tests.o $(BITSET_DIR)/bitset.o $(OUTPUT_DIR)/output.o

TARGET = bitset_main
TEST_TARGET = tests_run

SRCS = $(SRC_DIR)/main.c $(BITSET_DIR)/bitset.c $(OUTPUT_DIR)/output.c $(TESTS_DIR)/tests.c

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)
$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_TARGET)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(BITSET_DIR)%.o: $(BITSET_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OUTPUT_DIR)%.o: $(OUTPUT_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(TESTS_DIR)%.o: $(TESTS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

cppcheck:
	cppcheck --enable=all --suppress=missingInclude --suppress=missingIncludeSystem --platform=unix64 $(SRCS)

check: cppcheck
	@echo "Проверка cppcheck завершена."

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)

rebuild: clean $(TARGET) $(TEST_TARGET)
