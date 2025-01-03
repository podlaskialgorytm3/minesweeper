#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/loading-borad.h"

loadedBoardPointer createMove(int x, int y, char moveType)
{
    loadedBoardPointer newMove = (loadedBoardPointer)malloc(sizeof(struct loadedBoard));
    if (newMove == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newMove->x = x;
    newMove->y = y;
    strcpy(newMove->moveType, moveType);
    newMove->next = NULL;
    return newMove;
}

gameSettingsPointer createGameSettings(int columns, int rows, int mines)
{
    gameSettingsPointer newSettings = (gameSettingsPointer)malloc(sizeof(struct gameSettings));
    if (newSettings == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newSettings->columns = columns;
    newSettings->rows = rows;
    newSettings->mines = mines;
    return newSettings;
}