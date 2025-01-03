#ifndef REVEALING_FIELDS_
#define REVEALING_FIELDS_

#include "loading-borad.h"

typedef struct checkField
{
    int x;
    int y;
    int isChecked;
    struct checkField *next;
} checkField, *checkFieldPtr;

int isContinue(boardPtr *list, int x, int y, char *user_choice, char *mode, loadedBoardPointer *moves);

void revealingField(boardPtr list, int x, int y);

void addFlag(boardPtr list, int x, int y);

void removeFlag(boardPtr list, int x, int y);

int is_flag(boardPtr list, int x, int y);

int checkifwin(boardPtr list);

checkFieldPtr insertCheckedFields(checkFieldPtr list, int x, int y, int isChecked);

checkFieldPtr getFirstNotChecked(checkFieldPtr list);

int getValueByCords(boardPtr list, int x, int y);

int isFieldChecked(checkFieldPtr list, int x, int y);

int checkIfAnyNotChecked(checkFieldPtr list);

void revealingFreeFields(boardPtr *list, int x, int y);

#endif