#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/loading-borad.h"

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