#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/board.h"

fieldPtr createField(fieldPtr list, int x, int y, int isBomb)
{
    fieldPtr newField = (fieldPtr)malloc(sizeof(field));
    if (newField == NULL)
    {
        exit(1);
    }

    newField->x = x;
    newField->y = y;
    newField->isBomb = isBomb;

    newField->next = list;

    return newField;
}
boardPtr createBoard(boardPtr list, int columns, int rows, int quantityOfBombs, field field)
{
    if (list == NULL)
    {
        boardPtr newBoard = (boardPtr)malloc(sizeof(board));
        if (newBoard == NULL)
        {
            exit(1);
        }
        newBoard->columns = columns;
        newBoard->rows = rows;
        newBoard->quantityOfBombs = quantityOfBombs;
        newBoard->field = (fieldPtr)malloc(sizeof(field));
        if (newBoard->field == NULL)
        {
            exit(1);
        }
        *(newBoard->field) = field;
        newBoard->next = NULL;
        return newBoard;
    }
    else
    {
        list = createBoard(list, columns, rows, quantityOfBombs, field);
        return list;
    }
}

void printFileds(fieldPtr list)
{
    while (list != NULL)
    {
        printf("x: %d y: %d value: %d\n", list->x, list->y, list->isBomb);
        list = list->next;
    }
}

void generateBoard(char *mode, boardPtr *boardList, fieldPtr *fieldList)
{
    srand(time(NULL));
    int x, y;
    if (strcmp(mode, "-e") == 0)
    {
        int mins = 10;
        for (int i = 0; i < 10; i++)
        {
            x = 1 + rand() % (10 - 1);
            y = 1 + rand() % (10 - 1);
            *fieldList = createField(*fieldList, x, y, 9);
        }
    }
    else if (strcmp(mode, "-m") == 0)
    {
    }
    else if (strcmp(mode, "-h") == 0)
    {
    }
}
