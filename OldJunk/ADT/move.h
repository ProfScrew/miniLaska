#ifndef MOVE_H
#define MOVE_H

typedef struct availableMovement{
    int countEatMove;
    int countNormalMove;
    int **eatMove;
    int **normalMove;
}movement;


void createMove(movement *temp);
void regNormalMove(movement *temp, int fromI, int fromJ, int toI, int toJ);
void regEatMove(movement *temp, int fromI, int fromJ,int eatI, int eatJ, int toI, int toJ);
void destroyMove(movement *temp);


#endif