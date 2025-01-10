#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/loading-borad.h"
#include "../include/board.h"

movementsPtr createMove(movementsPtr moves, int x, int y, char *moveType)
{
    movementsPtr newMove = (movementsPtr)malloc(sizeof(struct movements));
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
        movementsPtr temp = moves;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newMove;
        return moves;
    }
}

void printMoves(movementsPtr moves)
{

    while (moves != NULL)
    {
        printf("%s %d %d\n", moves->moveType, moves->x, moves->y);
        moves = moves->next;
    }
}
void printBoard(boardPtr boardList)
{
    while (boardList != NULL)
    {
        printf("x: %d, y: %d, fieldValue: %d\n", boardList->x, boardList->y, boardList->fieldValue);
        boardList = boardList->next;
    }
}

void saveFile(char *fileName, boardPtr boradList, movementsPtr moves)
{

    char filePath[256];
    snprintf(filePath, sizeof(filePath), "./data/%s", fileName);
    FILE *file = fopen(filePath, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file for writing\n");
        return;
    }

    boardPtr currentBoard = boradList;
    while (currentBoard != NULL)
    {
        fprintf(file, "%d %d %d %d %d\n", currentBoard->x, currentBoard->y, currentBoard->fieldValue, currentBoard->isVisable, currentBoard->isFlag);
        currentBoard = currentBoard->next;
    }

    movementsPtr currentMove = moves;
    while (currentMove != NULL)
    {
        fprintf(file, "%s %d %d\n", currentMove->moveType, currentMove->x, currentMove->y);
        currentMove = currentMove->next;
    }

    fclose(file);
}
void loadFile(char *fileName, boardPtr *boardList, movementsPtr *moves)
{
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "./data/%s", fileName);
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file for reading\n");
        return;
    }

    char line[100];
    *boardList = NULL;
    *moves = NULL;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] == '-')
        {
            char moveType[10];
            int x, y;

            if (sscanf(line, "%s %d %d", moveType, &x, &y) == 3)
            {
                *moves = createMove(*moves, x, y, moveType);
            }
            else
            {
                fprintf(stderr, "Invalid move format: %s\n", line);
            }
        }
        else
        {
            int x, y, fieldValue, isVisable, isFlag;

            if (sscanf(line, "%d %d %d %d %d", &x, &y, &fieldValue, &isVisable, &isFlag) == 5)
            {
                boardPtr newBoard = (boardPtr)malloc(sizeof(struct board));
                if (newBoard == NULL)
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                newBoard->x = x;
                newBoard->y = y;
                newBoard->fieldValue = fieldValue;
                newBoard->isVisable = isVisable;
                newBoard->isFlag = isFlag;

                newBoard->next = *boardList;
                *boardList = newBoard;
            }
            else
            {
                fprintf(stderr, "Invalid board format: %s\n", line);
            }
        }
    }

    sortListByCords(boardList);
    fclose(file);
}

int getCorrectSteps(movementsPtr moves, int isWin)
{
    int correctSteps = 0;
    while (moves != NULL)
    {
        if (strcmp(moves->moveType, "-r") == 0)
        {
            correctSteps++;
        }
        moves = moves->next;
    }
    return correctSteps - 1 + isWin;
}