#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/board.h"
#include "../include/revealing-fields.h"

#define MAX_PLAYERS 5
#define FILENAME "scoreboard.txt"
typedef struct {
    char nickname[50];
    int score;
} Player;

int load_scores(Player players[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0; 
    }

    int count = 0;
    while (fscanf(file, "%s %d\n", players[count].nickname, &players[count].score) == 2) {
        count++;
    }

    fclose(file);
    return count;
}

void save_scores(Player players[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Nie można otworzyć pliku do zapisu");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", players[i].nickname, players[i].score);
    }

    fclose(file);
}

void add_score(Player players[], int *count, const char *nickname, int score) {
    if (*count < MAX_PLAYERS) {
        strcpy(players[*count].nickname, nickname);
        players[*count].score = score;
        (*count)++;
    } else {
        int min_index = 0;
        for (int i = 1; i < *count; i++) {
            if (players[i].score < players[min_index].score) {
                min_index = i;
            }
        }

        if (score > players[min_index].score) {
            strcpy(players[min_index].nickname, nickname);
            players[min_index].score = score;
        }
    }
    for (int i = 0; i < *count - 1; i++) {
        for (int j = 0; j < *count - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char **argv)
{
    char *nickname = malloc(100);
    nickname = argc > 1 ? argv[1]: "bobas";
    printf("Siemano %s\n", nickname);
    int x_r = 9;
    boardPtr boardList = NULL;
    char *mode = malloc(3 * sizeof(char));
    if (argc > 2)
    {
        strcpy(mode, argv[2]);
        if(strcmp(argv[2], "-e")!=0)
            x_r = 16;
    }
    else
    {
        strcpy(mode, "-e");
        x_r = 9;
    }
    int rows = argc > 3 ? atoi(argv[3]) : 0;
    int columns = argc > 4 ? atoi(argv[4]) : 0;
    int quatityOfMins = argc > 5 ? atoi(argv[5]) : 0;
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
            printf("\nBrawo %s wygrales i zdobyles: %d punktow\n", nickname, score(boardList, mode));
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
            generateBoard(mode, &boardList, rows, columns, quatityOfMins, x, y);
            isFirstMove = 0;
        }
        // if(strcmp(user_choice, "-r")==0 && isFirstMove==0){
        //     revealingField(boardList, x, y);
        // }
        // if(strcmp(user_choice, "-f")==0 && isFirstMove==0){
        //     addFlag(boardList, x, y);
        // }

    } while (isContinue(&boardList, x, y, user_choice) == 1);
    
    //printFileds(boardList, x_r);
    add_score(players, &count, nickname, score(boardList, mode));
    save_scores(players, count, FILENAME);
    printf("Top %d gracze:\n", MAX_PLAYERS);
    for (int i = 0; i < count; i++) {
        printf("%s: %d\n", players[i].nickname, players[i].score);
    }
    
    return 0;
}