#ifndef BOARD_H
#define BOARD_H

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


void showBoardfirst(gBoard *temp);
void showBoard(gBoard *temp);
void readGame(gBoard *temp);


void normalMovement(gBoard *temp, int fromI, int fromJ, int toI, int toJ);
void eatMovement(gBoard *temp, int fromI, int fromJ, int eatI, int eatJ, int toI, int toJ);

movement checkWhite(gBoard *temp);
movement checkBlack(gBoard *temp);

float valueOfBoard(gBoard *temp,char side);

char getTurn(gBoard *temp);
char getWinner(gBoard *temp);


#endif