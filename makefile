# Zmienne
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = program
TEST_TARGET = tests
SRC = src/main.c src/board.c src/revealing-fields.c src/handling-score.c
TEST_SRC = tests.c src/board.c src/revealing-fields.c src/handling-score.c

# Domyślny cel: kompilacja programu
all: $(TARGET)

# Kompilacja programu głównego
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Kompilacja i uruchomienie testów
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

# Czyszczenie plików wykonywalnych
clean:
	rm -f $(TARGET) $(TEST_TARGET)
