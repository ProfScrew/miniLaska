#ifndef BOARD_H
#define BOARD_H


typedef struct gameBoard{
   char*** Board;
   char winner;
   char turn;
}gBoard;


void createBoard(gBoard *temp);
void cleanBoard(gBoard *temp);
void initBoard(gBoard *temp);
void initPlayers(gBoard *temp);

void copyBoard(gBoard *copy, gBoard *original);


void showBoardfirst(gBoard *temp);
void showBoard(gBoard *temp);

void readGame(gBoard *temp);


#endif