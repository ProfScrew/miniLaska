#ifndef MOVE_H
#define MOVE_H
/*structure wich contains list of available movement of a player after scan*/
typedef struct availableMovement{
    int countEatMove;
    int countNormalMove;
    int **eatMove;
    int **normalMove;
}movement;

/**/
void createMove(movement *temp);   /*assignes pointers at nulles and values at zero*/

/*if movement is possible its going to be registered with those two functions with all the necessary coordinates*/
void regNormalMove(movement *temp, int fromI, int fromJ, int toI, int toJ);    
void regEatMove(movement *temp, int fromI, int fromJ,int eatI, int eatJ, int toI, int toJ);
/*frees moves when not necessary*/
void destroyMove(movement *temp);
/*display moves used for debug*/
void seeMove(movement *temp);

/*functions used to display movement to the user*/
/*used by player functions and cpus with options of displaying value of the move*/
void printNormMoves(movement *temp, float *move);
void printEatMoves(movement *temp, float *move);

/*used by cpus when it has situations with equals values*/
/*it choses random between the N choices with same value*/
/*in this way the games are not all the same */
void randomChoice(movement *temp, float *move, bool type, int *choice);

/*utility function*/
int getCountEat(movement *temp);
int getCountNormal(movement *temp);

int getMoveEat(movement *temp, int move, int pos);
int getMoveNormal(movement *temp, int move, int pos);

#endif