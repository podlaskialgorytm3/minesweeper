#ifndef LOADING_BOARD_
#define LOADING_BOARD_

typedef struct gameSettings
{
    int columns;
    int rows;
    int mines;
    struct gameSettings *next;
} gameSettings, *gameSettingsPointer;

typedef struct loadedBoard
{
    char moveType[2];
    int x;
    int y;
    struct loadedBoard *next;
} loadedBoard, *loadedBoardPointer;

gameSettingsPointer createGameSettings(gameSettingsPointer settings, int columns, int rows, int mines);

loadedBoardPointer createMove(loadedBoardPointer moves, int x, int y, char *moveType);

void printSettingsAndMoves(gameSettingsPointer settings, loadedBoardPointer moves);

#endif