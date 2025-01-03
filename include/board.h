#ifndef BOARD_
#define BOARD_

typedef struct board
{
    int x;
    int y;
    int fieldValue; // [0] - Neutral , [1-8] - Inforamtion, [9] Is bomb.
    int isVisable;  // 0 - not visable, 1 - visable
    int isFlag;
    struct board *next;
} board, *boardPtr;

boardPtr createBoard(boardPtr list, int x, int y, int fieldValue);

void sortListByCords(boardPtr *list);

int score(boardPtr list, char *mode);

int checkIfFieldExist(boardPtr list, int x, int y);

int isFieldExist(int x, int y, int columns, int rows);

int getValueOfField(boardPtr list, int x, int y, int columns, int rows);

int getColumns(boardPtr list);

int getRows(boardPtr list);

void printFileds(boardPtr list, int x);

void generateBoard(char *mode, boardPtr *boardList, int rows, int columns, int quatityOfMins, int x, int y);

void completeMins(boardPtr *boardList, int columns, int rows, int quantityOfMins, int firstX, int firstY);

void completeFileds(boardPtr *boardList, int columns, int rows);

const char *getMode(boardPtr list);

#endif