#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/board.h"
#include "../include/revealing-fields.h"

int main(int argc, char **argv)
{
    boardPtr boardList = NULL;
    char *mode = malloc(3 * sizeof(char));
    if (argc > 1)
    {
        strcpy(mode, argv[1]);
    }
    else
    {
        strcpy(mode, "-e");
    }
    int rows = argc > 2 ? atoi(argv[2]) : 0;
    int columns = argc > 3 ? atoi(argv[3]) : 0;
    int quatityOfMins = argc > 4 ? atoi(argv[4]) : 0;
    generateBoard(mode, &boardList, rows, columns, quatityOfMins);

    int x, y;
    do
    {
        printFileds(boardList);
        printf("Podaj wspolrzedne (x y): ");
        if (scanf("%d %d", &x, &y) != 2)
        {
            printf("Niepoprawny format danych. Sprobuj ponownie.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

    } while (isContinue(&boardList, x, y) == 1);

    printFileds(boardList);

    return 0;
}