#ifndef REVEALING_FIELDS_
#define REVEALING_FIELDS_

typedef struct checkField
{
    int x;
    int y;
    int isChecked;
    struct checkField *next;
} checkField, *checkFieldPtr;

int isContinue(boardPtr *list, int x, int y);

void revealingField(boardPtr list, int x, int y);

checkFieldPtr insertCheckedFields(checkFieldPtr list, int x, int y, int isChecked);

checkFieldPtr getFirstNotChecked(checkFieldPtr list);

int getValueByCords(boardPtr list, int x, int y);

int isFieldChecked(checkFieldPtr list, int x, int y);

int checkIfAnyNotChecked(checkFieldPtr list);

void revealingFreeFields(boardPtr *list, int x, int y);

#endif