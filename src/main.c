#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/board.h"
#include "../include/revealing-fields.h"
#include "../include/file_reader.h"
#include <unistd.h>

#define MAX_PLAYERS 5
#define FILENAME "scoreboard.txt"

int main(int argc, char **argv)
{   
    int rows = 0;
    int columns = 0;
    int mines = 0;
    char *nickname = malloc(50);
    int x_r = 9;
    boardPtr boardList = NULL;
    char *mode = malloc(3 * sizeof(char));
    int opt;
    strcpy(mode, "-e");
    while ((opt = getopt(argc, argv, "emhpl:")) != -1) {
        //printf("Prosze podac tryb\n");
        switch (opt) {
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
                // Przetwarzanie opcji -p, która wymaga dodatkowych parametrów
                if (optind < argc) {
                    rows = atoi(argv[optind++]);
                    columns = atoi(argv[optind++]);
                    mines = atoi(argv[optind++]);
                } else {
                    fprintf(stderr, "Opcja -p wymaga trzech argumentow: wiersze, kolumny, miny.\n");
                    return 1;
                }
                break;
            case 'l':
                // Obsługuje opcję -h (pomoc)
                printf("Help message:\n");
                printf("-e: Set mode to easy\n");
                printf("-r <value>: Set number of rows\n");
                printf("-c <value>: Set number of columns\n");
                printf("-m <nickname>: Set the nickname\n");
                printf("-h: Show this help message\n");
                return 0;
            default:
                fprintf(stderr, "Usage: %s [-e] [-r <rows>] [-c <columns>] [-m <nickname>] [-h]\n", argv[0]);
                return 1;
        }
    }
    //printf("%s %d %d %d\n", mode, rows, columns, mines);
    if(rows>0) x_r = rows;
    int x, y;
    int isFirstMove = 1;
    char *user_choice = malloc(5);
    Player players[MAX_PLAYERS];
    int count = load_scores(players, FILENAME);
    do
    {
        // -r x y odkrywa
        // -f x y dodaje flage
        printf("Aktualny wynik: %d\n", score(boardList, mode));
        printFileds(boardList, x_r);
        if(checkifwin(boardList)==1 && isFirstMove==0){
            printf("\nBrawo wygrales\n");
            break;
        }
        printf("Wpisz wybor i wspolrzedne (x y): ");
        if (scanf("%s %d %d",user_choice, &x, &y) != 3)
        {
            printf("Niepoprawny format danych. Sprobuj ponownie.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (isFirstMove == 1)
        {
            generateBoard(mode, &boardList, rows, columns, mines, x, y);
            isFirstMove = 0;
        }


    } while (isContinue(&boardList, x, y, user_choice, mode) == 1);

    printf("Podaj swoj nick: ");
    scanf("%s", nickname);
    add_score(players, &count, nickname, score(boardList, mode));
    save_scores(players, count, FILENAME);
    printf("Top %d gracze:\n", MAX_PLAYERS);
    for (int i = 0; i < count; i++) {
        printf("%s: %d\n", players[i].nickname, players[i].score);
    }
    
    return 0;
}