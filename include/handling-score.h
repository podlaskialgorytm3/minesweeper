#ifndef HANDLING_SCORE_
#define HANDLING_SCORE_

typedef struct {
    char nickname[50];
    int score;
} Player;

int load_scores(Player players[], const char *filename);

void save_scores(Player players[], int count, const char *filename);

void add_score(Player players[], int *count, const char *nickname, int score);

#endif