#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/board.h"

boardPtr createBoard(boardPtr list, int x, int y, int fieldValue)
{
    boardPtr newField = (boardPtr)malloc(sizeof(board));
    if (newField == NULL)
    {
        exit(1);
    }

    newField->x = x;
    newField->y = y;
    newField->fieldValue = fieldValue;
    newField->isVisable = 0;

    newField->next = list;

    return newField;
}
void sortListByCords(boardPtr *list)
{
    if (*list == NULL || (*list)->next == NULL)
    {
        return;
    }
    boardPtr sorted = NULL;
    while (*list != NULL)
    {
        boardPtr current = *list;
        *list = (*list)->next;
        if (sorted == NULL || current->y < sorted->y || (current->y == sorted->y && current->x < sorted->x))
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            boardPtr temp = sorted;
            while (temp->next != NULL && (temp->next->y < current->y || (temp->next->y == current->y && temp->next->x < current->x)))
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    *list = sorted;
}

int checkIfFieldExist(boardPtr list, int x, int y)
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

int isBombExist(boardPtr list, int x, int y)
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

int getValueOfField(boardPtr list, int x, int y, int columns, int rows)
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

void printFileds(boardPtr list)
{
    while (list != NULL)
    {
        if (list->isVisable == 1)
        {
            if (list->fieldValue == 9)
            {
                printf("* ");
            }
            else if (list->fieldValue == 0)
            {
                printf("  ");
            }
            else
            {
                printf("%d ", list->fieldValue);
            }
        }
        else if (list->isVisable == 0)
        {
            printf("X ");
        }
        if (list->next != NULL && list->x > list->next->x)
        {
            printf("\n");
        }
        list = list->next;
    }
    printf("\n");
}

void generateBoard(char *mode, boardPtr *boardList, int rows, int columns, int quatityOfMins)
{
    srand(time(NULL));
    if (strcmp(mode, "-e") == 0)
    {
        completeMins(boardList, 9, 9, 10);
        completeFileds(boardList, 9, 9);
    }
    else if (strcmp(mode, "-m") == 0)
    {
        completeMins(boardList, 16, 16, 40);
        completeFileds(boardList, 16, 16);
    }
    else if (strcmp(mode, "-h") == 0)
    {
        completeMins(boardList, 16, 30, 99);
        completeFileds(boardList, 16, 30);
    }
    else if (strcmp(mode, "-p") == 0)
    {
        completeMins(boardList, rows, columns, quatityOfMins);
        completeFileds(boardList, rows, columns);
    }

    sortListByCords(boardList);
}

void completeMins(boardPtr *boardList, int columns, int rows, int quantityOfMins)
{
    int x, y, arleadyExist;
    for (int i = 0; i < quantityOfMins; i++)
    {
        do
        {
            x = 1 + rand() % columns;
            y = 1 + rand() % rows;
            arleadyExist = checkIfFieldExist(*boardList, x, y);
        } while (arleadyExist == 0);
        *boardList = createBoard(*boardList, x, y, 9);
    }
}

void completeFileds(boardPtr *boardList, int columns, int rows)
{
    for (int y = 1; y < rows + 1; y++)
    {
        for (int x = 1; x < columns + 1; x++)
        {
            if (isBombExist(*boardList, x, y) == 0)
            {
                int fieldValue = getValueOfField(*boardList, x, y, columns, rows);
                *boardList = createBoard(*boardList, x, y, fieldValue);
            }
        }
    }
}