#ifndef LOADING_BOARD_
#define LOADING_BOARD_
#include "./board.h"

typedef struct movements
{
    char moveType[2];
    int x;
    int y;
    struct movements *next;
} movements, *movementsPtr;

movementsPtr createMove(movementsPtr moves, int x, int y, char *moveType);

void printMoves(movementsPtr moves);

void printBoard(boardPtr boardList);

void saveFile(char *fileName, boardPtr boradList, movementsPtr moves);

void loadFile(char *fileName, boardPtr *boardList, movementsPtr *moves);

int getCorrectSteps(movementsPtr moves, int isWin);

#endif