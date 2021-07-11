#ifndef PARTICIPANTS_H
#define PARTICIAPNTS_H

#include"board.h"
#include"move.h"

void playerMove(gBoard *temp);
void cpuMoveRandom(gBoard *temp);
float cpuRecFunc(int depth, gBoard *original, float *numberOfOutcomes, char side);
void cpuSmart(gBoard *temp, int depth);

#endif