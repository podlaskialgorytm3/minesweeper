# Kompilator i flagi
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Katalogi
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Pliki źródłowe i obiektowe
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(filter-out $(BUILD_DIR)/test.o, $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES)))

# Plik wynikowy
TARGET = program

# Reguła główna
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Reguła testowa dla src/test.c
test: $(BUILD_DIR)/test.o $(filter-out $(BUILD_DIR)/main.o, $(OBJ_FILES))
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/test.o: $(SRC_DIR)/test.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Reguły czyszczenia
clean:
	rm -rf $(BUILD_DIR) $(TARGET) test

.PHONY: all clean test
