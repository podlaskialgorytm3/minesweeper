#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/board.h"

fieldPtr createField(fieldPtr list, int x, int y, int fieldValue)
{
    fieldPtr newField = (fieldPtr)malloc(sizeof(field));
    if (newField == NULL)
    {
        exit(1);
    }

    newField->x = x;
    newField->y = y;
    newField->fieldValue = fieldValue;

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
int checkIfFieldExist(fieldPtr list, int x, int y)
{
    while (list != NULL)
    {
        if (list->x == x && list->y == y)
        {
            return 0;
        }
        list = list->next;
    }
    return 1;
}

int isBombExist(fieldPtr list, int x, int y)
{
    while (list != NULL)
    {
        if (list->x == x && list->y == y)
        {
            return list->fieldValue == 9;
        }
        list = list->next;
    }
    return 0;
}

int isFieldExist(int x, int y, int columns, int rows)
{
    if (x < 1 || y < 1)
    {
        return 0;
    }
    else if (x > columns)
    {
        return 0;
    }
    else if (y > rows)
    {
        return 0;
    }
    return 1;
}

int getValueOfField(fieldPtr list, int x, int y, int columns, int rows)
{
    int fieldValue = 0;
    for (int moveY = -1; moveY <= 1; moveY++)
    {
        for (int moveX = -1; moveX <= 1; moveX++)
        {
            if (isFieldExist(x + moveX, y + moveY, columns, rows) && isBombExist(list, x + moveX, y + moveY) && !(moveX == 0 && moveY == 0))
            {
                fieldValue++;
            }
        }
    }
    return fieldValue;
}

void printFileds(fieldPtr list)
{
    while (list != NULL)
    {
        printf("x: %d y: %d value: %d\n", list->x, list->y, list->fieldValue);
        list = list->next;
    }
}

void generateBoard(char *mode, boardPtr *boardList, fieldPtr *fieldList)
{
    srand(time(NULL));
    if (strcmp(mode, "-e") == 0)
    {
        completeMins(fieldList, 9, 9, 10);
        completeFileds(fieldList, 9, 9);
    }
    else if (strcmp(mode, "-m") == 0)
    {
        completeMins(fieldList, 16, 16, 40);
        completeFileds(fieldList, 16, 16);
    }
    else if (strcmp(mode, "-h") == 0)
    {
        completeMins(fieldList, 16, 30, 99);
        completeFileds(fieldList, 16, 30);
    }
}

void completeMins(fieldPtr *fieldList, int columns, int rows, int quantityOfMins)
{
    int x, y, arleadyExist;
    for (int i = 0; i < quantityOfMins; i++)
    {
        do
        {
            x = 1 + rand() % columns;
            y = 1 + rand() % rows;
            arleadyExist = checkIfFieldExist(*fieldList, x, y);
        } while (arleadyExist == 0);
        *fieldList = createField(*fieldList, x, y, 9);
    }
}

void completeFileds(fieldPtr *fieldList, int columns, int rows)
{
    for (int y = 1; y < rows + 1; y++)
    {
        for (int x = 1; x < columns + 1; x++)
        {
            if (isBombExist(*fieldList, x, y) == 0)
            {
                int fieldValue = getValueOfField(*fieldList, x, y, columns, rows);
                *fieldList = createField(*fieldList, x, y, fieldValue);
            }
        }
    }
}