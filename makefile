# Zmienne
# CC = gcc
# OBJ_DIR = build\object-files
# EXEC = program.exe
Target = program
# Lista plików źródłowych i obiektowych
# SRC = src/main.c src/board.c src/revealing-fields.c src/handling-score.c
# OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
$(Target):
	gcc src/main.c src/board.c src/revealing-fields.c src/handling-score.c -o program
test:
	./program -e
# # Domyślny cel: kompilacja programu
# all: $(EXEC)
# # Kompilacja programu
# $(EXEC): $(OBJ)
# 	$(CC) $^ -o $@
# # Kompilacja plików obiektowych
# $(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
# 	$(CC) -c $< -o $@
# # Tworzenie katalogu na pliki obiektowe
# $(OBJ_DIR):
# 	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
# test: $(EXEC)
# 	./$(EXEC) -e
# # Cel czyszczący pliki obiektowe i program
# clean:
# 	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
# 	@if exist $(EXEC) del $(EXEC)