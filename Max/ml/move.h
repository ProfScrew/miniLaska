#ifndef move_h
#define move_h
#include "board.h"

typedef struct availableMovement{
    int countEatMove;
    int countNormalMove;
    int **eatMove;
    int **normalMove;
}movement;



void initMovement(movement *temp);
void regNormalMove(movement *temp, int fromI, int fromJ, int toI, int toJ);
void regEatMove(movement *temp, int fromI, int fromJ,int eatI, int eatJ, int toI, int toJ);
void freeMove(movement *temp);
void seeMove(movement *temp);

void checkWhite(gBoard *temp, movement *list);
void checkBlack(gBoard *temp, movement *list);


void normalMovement(gBoard *temp, movement *list, int move);
void eatMovement(gBoard *temp, movement *list, int move);


#endif