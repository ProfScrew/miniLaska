#ifndef PRATICIPANTS_H
#define PARTICIPANTS_H

#include"board.h"
#include"move.h"

void playerMove(gBoard *temp);
void cpuMoveRandom(gBoard *temp);
float valueOfBoard(gBoard *temp,char side);
float cpuScanRec(int depth, gBoard *original, float *numberOfOutcomes, char side);
void cpuScan(gBoard *temp, int depth);
float cpuEatRec(gBoard *original, int depth, int depthCount, float value, int *numberOfOutcomes, char side);
void cpuEat(gBoard *temp, int depth);

#endif