#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/board.h"
#include "../include/revealing-fields.h"
#include "../include/file_reader.h"

#define MAX_PLAYERS 5
#define FILENAME "scoreboard.txt"

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
