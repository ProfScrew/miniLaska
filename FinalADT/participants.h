#ifndef PRATICIPANTS_H
#define PARTICIPANTS_H

#include"board.h"
#include"move.h"
/*contains the four participants that are able to play the game*/

/*the use is playing*/
void playerMove(gBoard *temp);

/*cpu randomly*/
/*randomly chooses a move*/
void cpuMoveRandom(gBoard *temp);

/*cpu scan */
/*cpu goes through brute forces al possibily to a certain depth*/
/*when it reaches the end it evaluates a board through the func "valueOfBoard" and it gets a value */
/*those values are then added with other posibility after that it devides by the number of outcomes and it gets the final value*/ 
float cpuScanRec(int depth, gBoard *original, float *numberOfOutcomes, char side);
void cpuScan(gBoard *temp, int depth);

/*cpu eat*/
/*cpu goes through brute forces al possibily to a certain depth*/
/*if throughout the game simulation an eat move is perform a value is incresed and when it reaches the end its devided by the depth it stoped*/
/*if it reaches the end before end of depth meaning its a win or a lost a value of 100 is added and its devided by the depthcount*/
/*this way it will prioritize the quickest way to reach the end of a game*/
float cpuEatRec(gBoard *original, int depth, int depthCount, float value, int *numberOfOutcomes, char side);
void cpuEat(gBoard *temp, int depth);

#endif