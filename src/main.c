#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/board.h"
#include "../include/revealing-fields.h"

int main(int argc, char **argv)
{
    int x_r = 9;
    boardPtr boardList = NULL;
    char *mode = malloc(3 * sizeof(char));
    if (argc > 1)
    {
        strcpy(mode, argv[1]);
        if(strcmp(argv[1], "-e")!=0)
            x_r = 16;
    }
    else
    {
        strcpy(mode, "-e");
        x_r = 9;
    }
    int rows = argc > 2 ? atoi(argv[2]) : 0;
    int columns = argc > 3 ? atoi(argv[3]) : 0;
    int quatityOfMins = argc > 4 ? atoi(argv[4]) : 0;
    if(rows>0) x_r = rows;
    int x, y;
    int isFirstMove = 1;
    printf("%d\n", x_r);
    //generateBoard(mode, &boardList, rows, columns, quatityOfMins, 1, 1);
    do
    {
        printFileds(boardList, x_r);
        printf("Podaj wspolrzedne (x y): ");
        if (scanf("%d %d", &x, &y) != 2)
        {
            printf("Niepoprawny format danych. Sprobuj ponownie.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (isFirstMove == 1)
        {
            generateBoard(mode, &boardList, rows, columns, quatityOfMins, x, y);
            isFirstMove = 0;
        }

    } while (isContinue(&boardList, x, y) == 1);

    printFileds(boardList, x_r);

    return 0;
}