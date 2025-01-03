#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/loading-borad.h"

loadedBoardPointer createMove(loadedBoardPointer moves, int x, int y, char *moveType)
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

    if (moves == NULL)
    {
        return newMove;
    }
    else
    {
        loadedBoardPointer temp = moves;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newMove;
        return moves;
    }
}

gameSettingsPointer createGameSettings(gameSettingsPointer settings, int columns, int rows, int mines)
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

    newSettings->next = settings;

    return newSettings;
}

void printSettingsAndMoves(gameSettingsPointer settings, loadedBoardPointer moves)
{
    while (settings != NULL)
    {
        printf("%d %d %d\n", settings->columns, settings->rows, settings->mines);
        settings = settings->next;
    }
    while (moves != NULL)
    {
        printf("%s %d %d\n", moves->moveType, moves->x, moves->y);
        moves = moves->next;
    }
}