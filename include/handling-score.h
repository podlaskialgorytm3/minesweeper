#ifndef HANDLING_SCORE_
#define HANDLING_SCORE_

typedef struct
{
    char nickname[50];
    int score;
} Player;

int loadScore(Player players[], const char *filename);

void saveScores(Player players[], int count, const char *filename);

void addScore(Player players[], int *count, const char *nickname, int score);

#endif