#ifndef LOADING_BOARD_
#define LOADING_BOARD_

typedef struct movements
{
    char moveType[2];
    int x;
    int y;
    struct movements *next;
} movements, *movementsPtr;

movementsPtr createMove(movementsPtr moves, int x, int y, char *moveType);

void printMoves(movementsPtr moves);

#endif