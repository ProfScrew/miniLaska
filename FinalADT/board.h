#ifndef BOARD_H
#define BOARD_H
#include "move.h"
typedef struct gameBoard{
   char*** Board;
   char winner;
   char turn;
}gBoard;

void createBoard(gBoard *temp);
void destroyBoard(gBoard *temp);
void initBoard(gBoard *temp);
void initPlayers(gBoard *temp);
void copyBoard(gBoard *copy, gBoard *original);

void changeTurn(gBoard *temp);
char getTurn(gBoard *temp);
char getWinner(gBoard *temp);
void selectWinner(gBoard *temp);
void drawGame(gBoard *temp);

void normalMovement(gBoard *temp, movement *list, int move);
void eatMovement(gBoard *temp, movement *list, int move);

void checkWhite(gBoard *temp, movement *list);
void checkBlack(gBoard *temp, movement *list);



void showBoardfirst(gBoard *temp);
void showBoard(gBoard *temp);
void readGame(gBoard *temp);




float valueOfBoard(gBoard *temp,char side);



#endif