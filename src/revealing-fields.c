#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/revealing-fields.h"

int isContinue(boardPtr *list, int x, int y)
{
    boardPtr current = *list;
    int rows = getRows(current);
    int columns = getColumns(current);
    if (isFieldExist(x, y, columns, rows) == 0)
    {
        printf("Podano nie istniejace wsporzledne!\n");
        return 1;
    }
    int fieldValue = getValueByCords(current, x, y);

    if (fieldValue == 9)
    {
        revealingField(current, x, y);
        return 0;
    }
    else if (fieldValue > 0 && fieldValue < 9)
    {
        revealingField(current, x, y);
        return 1;
    }
    else if (fieldValue == 0)
    {
        revealingFreeFields(&current, x, y);
        return 1;
    }
}

void revealingField(boardPtr list, int x, int y)
{
    while (list != NULL)
    {
        if (list->x == x && list->y == y)
        {
            list->isVisable = 1;
        }
        list = list->next;
    }
}

checkFieldPtr insertCheckedFields(checkFieldPtr list, int x, int y, int isChecked)
{
    checkFieldPtr newList = (checkFieldPtr)malloc(sizeof(checkField));
    if (newList == NULL)
    {
        exit(1);
    }

    newList->x = x;
    newList->y = y;
    newList->isChecked = isChecked;
    newList->next = list;

    return newList;
}
checkFieldPtr getFirstNotChecked(checkFieldPtr list)
{
    while (list != NULL)
    {
        if (list->isChecked == 0)
        {
            return list;
        }
        list = list->next;
    }
}

void checkingField(checkFieldPtr *list, int x, int y)
{
    checkFieldPtr temp = *list;
    while (temp != NULL)
    {
        if (temp->x == x && temp->y == y)
        {
            temp->isChecked = 1;
        }
        temp = temp->next;
    }
}
int getValueByCords(boardPtr list, int x, int y)
{
    if (list == NULL)
    {
        return -1;
    }

    boardPtr current = list;

    while (current != NULL)
    {
        if (current->x == x && current->y == y)
        {
            list = current;
            return current->fieldValue;
        }
        current = current->next;
    }
    list = current;
    return -1;
}

int isFieldChecked(checkFieldPtr list, int x, int y)
{
    while (list != NULL)
    {
        if (list->x == x && list->y == y)
        {
            return list->isChecked;
        }

        list = list->next;
    }
    return 0;
}

int checkIfAnyNotChecked(checkFieldPtr list)
{
    int checked = 0;
    while (list != NULL)
    {
        if (list->isChecked == 0)
        {
            checked++;
        }
        list = list->next;
    }
    return checked;
}

void revealingFreeFields(boardPtr *list, int x, int y)
{
    boardPtr current = *list;

    checkFieldPtr queue = NULL;
    queue = insertCheckedFields(queue, x, y, 0);
    revealingField(current, x, y);

    int leftValue, topValue, rightValue, bottomValue;
    do
    {
        leftValue = getValueByCords(current, x - 1, y);
        topValue = getValueByCords(current, x, y - 1);
        rightValue = getValueByCords(current, x + 1, y);
        bottomValue = getValueByCords(current, x, y + 1);

        if (leftValue == 0 && !isFieldChecked(queue, x - 1, y))
        {
            queue = insertCheckedFields(queue, x - 1, y, 0);
            revealingField(current, x - 1, y);
        }
        else if (leftValue > 0)
        {
            revealingField(current, x - 1, y);
        }

        if (topValue == 0 && !isFieldChecked(queue, x, y - 1))
        {
            queue = insertCheckedFields(queue, x, y - 1, 0);
            revealingField(current, x, y - 1);
        }
        else if (topValue > 0)
        {
            revealingField(current, x, y - 1);
        }

        if (rightValue == 0 && !isFieldChecked(queue, x + 1, y))
        {
            queue = insertCheckedFields(queue, x + 1, y, 0);
            revealingField(current, x + 1, y);
        }
        else if (rightValue > 0)
        {
            revealingField(current, x + 1, y);
        }

        if (bottomValue == 0 && !isFieldChecked(queue, x, y + 1))
        {
            queue = insertCheckedFields(queue, x, y + 1, 0);
            revealingField(current, x, y + 1);
        }
        else if (bottomValue > 0)
        {
            revealingField(current, x, y + 1);
        }

        checkingField(&queue, x, y);
        if (checkIfAnyNotChecked(queue) > 0)
        {
            x = getFirstNotChecked(queue)->x;
            y = getFirstNotChecked(queue)->y;
        }
    } while (checkIfAnyNotChecked(queue) > 0);
}
