#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/board.h"
#include "../include/revealing-fields.h"
#include "../include/handling-score.h"
#include "../include/loading-borad.h"

#define MAX_PLAYERS 5
#define FILENAME "scoreboard.txt"

int main(int argc, char **argv)
{
    boardPtr boardList = NULL;
    movementsPtr moves = NULL;

    int rows = 0;
    int columns = 0;
    int mines = 0;
    char *nickname = malloc(50);
    int x_r = 9;
    char *mode = malloc(3 * sizeof(char));
    int opt;

    char filename[50];

    strcpy(mode, "-e");
    while ((opt = getopt(argc, argv, "emhpfah")) != -1)
    {
        switch (opt)
        {
        case 'e':
            strcpy(mode, "-e");
            x_r = 9;
            break;
        case 'm':
            strcpy(mode, "-m");
            x_r = 16;
            break;
        case 'h':
            strcpy(mode, "-h");
            x_r = 16;
            break;
        case 'p':
            strcpy(mode, "-p");
            if (optind + 2 < argc)
            {
                rows = atoi(argv[optind++]);
                columns = atoi(argv[optind++]);
                mines = atoi(argv[optind++]);
            }
            else
            {
                fprintf(stderr, "Opcja -p wymaga trzech argumentow: wiersze, kolumny, miny.\n");
                return 1;
            }
            break;
        case 'f':
            if (optind < argc)
            {
                loadFile(argv[optind++], &boardList, &moves);
                printf("Ruchy:\n");
                printMoves(moves);
                rows = getRows(boardList);
                printf("Plansza na zakonczenie gry:\n");
                printFileds(boardList, rows);
            }
            else
            {
                fprintf(stderr, "Opcja -f wymaga arguemntu.\n");
                return 1;
            }
            return 0;
        case 'a':
            printf("Mozliwe parametry do uruchomienia aplikacji:\n");
            printf("-e: Ustawienie trybu latwego [9x9] 9 min.\n");
            printf("-m: Ustawienie trybu sredniego [16x16] 40 min.\n");
            printf("-h: Ustawienie trybu trudnego [16x30] 99 min.\n");
            printf("-p [liczba kolumn] [liczba wierszy] [liczba min] - Ustawienie niestandardowej gry.\n");
            printf("-f [nazwa pliku] - Wczytywanie zapisanej gry.");
            printf("Parametry podczas dzialania aplikacji:\n");
            printf("-r [x] [y]: Odkrycie pola o podanych koordynatach.\n");
            printf("-f [x] [y]: Zasloniencie flaga lub odkrycie flagi na danym polu o podanych koordynatach.\n");
            return 0;
        default:
            fprintf(stderr, "Uzytko niepoprawnych parametrow.\n", argv[0]);
            return 1;
        }
    }

    if (rows > 0)
        x_r = rows;
    int x, y;
    int isFirstMove = 1;
    char *user_choice = malloc(5);
    Player players[MAX_PLAYERS];
    int count = load_scores(players, FILENAME);

    if (strcmp(mode, "-e") == 0)
    {
        columns = 9;
        rows = 9;
        mines = 10;
    }
    else if (strcmp(mode, "-m") == 0)
    {
        columns = 16;
        rows = 16;
        mines = 40;
    }
    else if (strcmp(mode, "-h") == 0)
    {
        columns = 16;
        rows = 30;
        mines = 40;
    }

    do
    {
        printf("Aktualny wynik: %d\n", score(boardList, mode));
        printFileds(boardList, x_r);

        if (checkifwin(boardList) == 1 && isFirstMove == 0)
        {
            printf("\nBrawo wygrales\n");
            break;
        }

        printf("Wpisz wybor i wspolrzedne -[r | f] [x] [y]: ");
        if (scanf("%s %d %d", user_choice, &x, &y) != 3)
        {
            printf("Niepoprawny format danych. Sprobuj ponownie.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (strcmp(user_choice, "-r") != 0 && strcmp(user_choice, "-f") != 0)
        {
            printf("Podano zly parametr: %s. Oczekiwano -r lub -f.\n", user_choice);
            while (getchar() != '\n')
                ;
            continue;
        }

        if (isFirstMove == 1)
        {
            generateBoard(mode, &boardList, rows, columns, mines, x, y);
            isFirstMove = 0;
        }

    } while (isContinue(&boardList, x, y, user_choice, mode, &moves) == 1);

    printf("Podaj swoj nick: ");
    scanf("%s", nickname);
    add_score(players, &count, nickname, score(boardList, mode));
    save_scores(players, count, FILENAME);
    printf("Top %d gracze:\n", MAX_PLAYERS);
    for (int i = 0; i < count; i++)
    {
        printf("%s: %d\n", players[i].nickname, players[i].score);
    }
    printf("Podaj plik do ktorego chcesz zapisac plansze: ");
    scanf("%s", filename);
    saveFile(filename, boardList, moves);

    return 0;
}