#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/board.h"
#include "../include/revealing-fields.h"
#include "../include/handling-score.h"

#define MAX_PLAYERS 5
#define FILENAME "scoreboard.txt"

int loadScore(Player players[], const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s %d\n", players[count].nickname, &players[count].score) == 2)
    {
        count++;
    }

    fclose(file);
    return count;
}

void saveScores(Player players[], int count, const char *fileName)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        perror("Nie można otworzyć pliku do zapisu");
        exit(1);
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s %d\n", players[i].nickname, players[i].score);
    }

    fclose(file);
}

void addScore(Player players[], int *count, const char *nickname, int score)
{
    if (*count < MAX_PLAYERS)
    {
        strcpy(players[*count].nickname, nickname);
        players[*count].score = score;
        (*count)++;
    }
    else
    {
        int minIndex = 0;
        for (int i = 1; i < *count; i++)
        {
            if (players[i].score < players[minIndex].score)
            {
                minIndex = i;
            }
        }

        if (score > players[minIndex].score)
        {
            strcpy(players[minIndex].nickname, nickname);
            players[minIndex].score = score;
        }
    }
    for (int i = 0; i < *count - 1; i++)
    {
        for (int j = 0; j < *count - i - 1; j++)
        {
            if (players[j].score < players[j + 1].score)
            {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}
