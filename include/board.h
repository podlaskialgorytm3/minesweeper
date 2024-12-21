#ifndef BOARD_
#define BOARD_

typedef struct board
{
    int x;
    int y;
    int fieldValue; // [0] - neutralne, [1-8] - informacyjne, [9] jest bomba
    struct board *next;
} board, *boardPtr;

boardPtr createBoard(boardPtr list, int x, int y, int fieldValue);

void sortListByCords(boardPtr *list);

int checkIfFieldExist(boardPtr list, int x, int y);

int isFieldExist(int x, int y, int columns, int rows);

int getValueOfField(boardPtr list, int x, int y, int columns, int rows);

void printFileds(boardPtr list);

void generateBoard(char *mode, boardPtr *boardList, int rows, int columns, int quatityOfMins);

void completeMins(boardPtr *boardList, int columns, int rows, int quantityOfMins);

void completeFileds(boardPtr *boardList, int columns, int rows);

#endif