/**
 * \file move.h
 * \brief Contains list of movements and functions
 * 
 */

#ifndef MOVE_H
#define MOVE_H
/*structure wich contains list of available movement of a player after scan*/

/**
 *\brief Contains list of available movement of a player 
 * 
 * It uses two 2d arrays(pointer to pointer).
 * Where one dimention is fixed on either 6 when capture/eat or 4 when normal move,
 * the other dimention value is stored in the corresponding count value.
*/
typedef struct availableMovement{
    int countEatMove;       
    int countNormalMove;
    /**
     * \brief 2d array composed of 6 variables(x y start, x y eat, x y end) for countEatMove
     */
    int **eatMove;          
    /**
     * \brief 2d array composed of 4 variables(x y start, x y end) for count NormalMove
     */
    int **normalMove;       
}movement;

/**
 *\brief Assignes pointers at null and values at zero
 */
void createMove(movement *temp);

/*if movement is possible its going to be registered with those two functions with all the necessary coordinates*/
/**
 * \brief Registeres movement in the array
 * 
 * Take as parameters position from origin, destination and saves them in the corresponding array
 */
void regNormalMove(movement *temp, int fromI, int fromJ, int toI, int toJ); 
/**
 * \brief Register capture in the array
 * 
 * Takes as paramenters position from origin, destination, capture and saves them in the corresponding array 
 */   
void regEatMove(movement *temp, int fromI, int fromJ,int eatI, int eatJ, int toI, int toJ);
/**
 * \brief Frees moves when not necessary
 */
void destroyMove(movement *temp);

/**
 * \brief Display moves (used for debug)
 * 
 */
void seeMove(movement *temp);

/*functions used to display movement to the user*/
/*used by player functions and cpus with options of displaying value of the move*/

/**
 * \brief Print normal move for the user
 * \param temp contains list of moves
 * \param move contains value of move(used by cpus)
 * 
 * \note If move is NULL it doesn't specify the value.
 */
void printNormMoves(movement *temp, float *move);
/**
 * \brief Print capture move for the user
 * \param temp contains list of moves
 * \param move contains value of move(used by cpus)
 * 
 * \note If move is NULL it doesn't specify the value.
*/
void printEatMoves(movement *temp, float *move);

/*used by cpus when it has situations with equals values*/
/*it choses random between the N choices with same value*/
/*in this way the games are not all the same */
/**
 * \brief Checks moves if there are multiple top values, it randomly chooses between them.
 * 
 * Checks if the top value have doubles. 
 * If it has then it randomly chooses one of moves with the top value.
 * If not then returns the top value
 * 
 * \param temp Used to extract number of moves.
 * \param move Contains values of moves 
 * \param type Specifies if normal move or capture move
 * \param choice Contains the high value 
 * 
 * 
 */
int randomChoice(movement *temp, float *move, bool type, int choice);

/*utility function*/
/**
 * \defgroup utilitymove_group Utility Functions
 * \brief Get basic information
 * \{
 */
int getCountEat(movement *temp);
int getCountNormal(movement *temp);

int getMoveEat(movement *temp, int move, int pos);
int getMoveNormal(movement *temp, int move, int pos);
/**\}*/
#endif