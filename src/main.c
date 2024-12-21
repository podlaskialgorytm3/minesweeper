#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"

int main(int argc, char **argv)
{
    boardPtr boardList = NULL;
    fieldPtr fieldList = NULL;

    generateBoard("-e", &boardList, &fieldList);

    printFileds(fieldList);

    return 0;
}