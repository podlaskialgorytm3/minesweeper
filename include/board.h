#ifndef BOARD_
#define BOARD_

typedef struct field
{
    int x;
    int y;
    int isBomb; // dla jasnosci [0] - neutralne, [1-8] - informacyjne, [9] jest bomba
    struct field *next;
} field, *fieldPtr;

typedef struct board
{
    int columns;
    int rows;
    int quantityOfBombs;
    fieldPtr field;
    struct board *next;
} board, *boardPtr;

fieldPtr createField(fieldPtr list, int x, int y, int isBomb);

boardPtr createBoard(boardPtr list, int columns, int rows, int quantityOfBombs, field field);

void printFileds(fieldPtr list);

void generateBoard(char *mode, boardPtr *boardList, fieldPtr *fieldList);

#endif