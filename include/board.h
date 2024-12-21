#ifndef BOARD_
#define BOARD_

typedef struct field
{
    int x;
    int y;
    int fieldValue; // dla jasnosci [0] - neutralne, [1-8] - informacyjne, [9] jest bomba
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

fieldPtr createField(fieldPtr list, int x, int y, int fieldValue);

boardPtr createBoard(boardPtr list, int columns, int rows, int quantityOfBombs, field field);

int checkIfFieldExist(fieldPtr list, int x, int y);

int isFieldExist(int x, int y, int columns, int rows);

int getValueOfField(fieldPtr list, int x, int y, int columns, int rows);

void printFileds(fieldPtr list);

void generateBoard(char *mode, boardPtr *boardList, fieldPtr *fieldList);

void completeMins(fieldPtr *fieldList, int columns, int rows, int quantityOfMins);

void completeFileds(fieldPtr *fieldList, int columns, int rows);

#endif