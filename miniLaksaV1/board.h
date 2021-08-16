#ifndef BOARD_H
#define BOARD_H
#include "move.h"

/*contains board structure and all functions to manage it*/
typedef struct gameBoard{
   char*** Board;
   char winner;
   char turn;
}gBoard;

void createBoard(gBoard *temp);     /*allocates space in memory for board*/
void destroyBoard(gBoard *temp);    /*frees memory for board*/
void initBoard(gBoard *temp);       /*fills board with empty chars " " and "#"*/
void initPlayers(gBoard *temp);     /*fills board with players*/
void copyBoard(gBoard *copy, gBoard *original); /*copies board if one of board null then error*/

/*utility below*/
void changeTurn(gBoard *temp);
char getTurn(gBoard *temp);
char getWinner(gBoard *temp);
void selectWinner(gBoard *temp);
void drawGame(gBoard *temp);
/*----------------------------*/

/*below function that manage movement of the pieces*/

void normalMovement(gBoard *temp, movement *list, int move);
void eatMovement(gBoard *temp, movement *list, int move);

/*functions used to scan board and determine available movement*/
void checkWhite(gBoard *temp, movement *list);
void checkBlack(gBoard *temp, movement *list);

/*function used by CPU scan to scan board at the end of depth and assign it a value*/
/*wich goes from -100 lost to 100 win, and various values in between that are assigned based on the peaces on the board*/
float valueOfBoard(gBoard *temp,char side);

/*outputs board*/
void showBoard(gBoard *temp);
/*reads game from txt file, used for debug*/
void readGame(gBoard *temp);




#endif
