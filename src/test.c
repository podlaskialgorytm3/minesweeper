#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/board.h"
#include "../include/revealing-fields.h"
#include "../include/handling-score.h"
#include "../include/loading-borad.h"

void test_createBoard()
{
    boardPtr list = NULL;
    list = createBoard(list, 1, 2, 9);
    assert(list != NULL);
    assert(list->x == 1);
    assert(list->y == 2);
    assert(list->fieldValue == 9);
    printf("test_createBoard passed\n");
}
void test_addScore()
{
    Player players[10] = {0};
    int count = 0;
    addScore(players, &count, "Alice", 100);
    addScore(players, &count, "Bob", 200);
    assert(count == 2);
    printf("test_addScore passed\n");
}

void test_saveLoadScore()
{
    Player players[2] = {{"Alice", 100}, {"Bob", 200}};
    saveScores(players, 2, "scores_test.txt");
    Player loaded[10];
    int count = loadScore(loaded, "scores_test.txt");
    assert(count == 2);
    assert(strcmp(loaded[0].nickname, "Alice") == 0);
    assert(loaded[1].score == 200);
    printf("test_saveLoadScore passed\n");
}
void test_createMove()
{
    movementsPtr moves = NULL;
    moves = createMove(moves, 1, 1, "-r");
    assert(moves != NULL);
    assert(moves->x == 1 && moves->y == 1);
    assert(strcmp(moves->moveType, "-r") == 0);
    printf("test_createMove passed\n");
}

void test_saveLoadFile()
{
    boardPtr board = NULL;
    movementsPtr moves = NULL;

    board = createBoard(board, 1, 1, 0);
    board = createBoard(board, 2, 1, 0);
    board = createBoard(board, 1, 2, 0);
    board = createBoard(board, 2, 2, 0);
    moves = createMove(moves, 1, 1, "-r");

    saveFile("game_state.txt", board, moves);

    boardPtr loadedBoard = NULL;
    movementsPtr loadedMoves = NULL;
    loadFile("game_state.txt", &loadedBoard, &loadedMoves);

    assert(loadedBoard->x == 1 && loadedBoard->y == 1);
    assert(loadedMoves->x == 1 && loadedMoves->y == 1);
    printf("test_saveLoadFile passed\n");
}
void test_revealingField()
{
    boardPtr list = NULL;
    list = createBoard(list, 0, 0, 0);
    revealingField(list, 0, 0);
    assert(list->isVisable == 1);
    printf("test_revealingField passed\n");
}

void test_flagOperations()
{
    boardPtr list = NULL;
    list = createBoard(list, 0, 0, 0);
    addFlag(list, 0, 0);
    assert(is_flag(list, 0, 0) == 1);
    removeFlag(list, 0, 0);
    assert(is_flag(list, 0, 0) == 0);
    printf("test_flagOperations passed\n");
}
int main()
{
    test_createBoard();
    test_addScore();
    test_saveLoadScore();
    test_createMove();
    test_saveLoadFile();
    test_revealingField();
    test_flagOperations();

    printf("All tests passed!\n");
    return 0;
}