#ifndef FILE_READER_
#define FILE_READER_

typedef struct {
    char nickname[50];
    int score;
} Player;

int load_scores(Player players[], const char *filename);

void save_scores(Player players[], int count, const char *filename);

void add_score(Player players[], int *count, const char *nickname, int score);

#endif