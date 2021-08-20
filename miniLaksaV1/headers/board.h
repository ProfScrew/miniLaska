/**
 * \file board.h
 * \brief Contains Board and all the function to manage it.
 * 
 */
#ifndef BOARD_H
#define BOARD_H
#include "../headers/move.h"

/*contains board structure and all functions to manage it*/

/**
 * \brief Structure that keeps of information related to the game
 * 
 * 
 * 
*/
typedef struct gameBoard{
   /**
    * \brief Pointer of the 3d array that contains the board.
    */
   char*** Board;    
   /**
    * \brief Keeps track of the winner: 'n' none, 'w' white, 'b' black, 'd' draw.
    */
   char winner;      
   /**
    * \brief Keeps track of whos turn it is.
    */
   char turn;        
}gBoard;

/**
 *\brief Allocates space in memory for board.
 */
void createBoard(gBoard *temp);     
/**
 * \brief Frees memory of the board.
 */
void destroyBoard(gBoard *temp);    
/**
 * \brief Fills board with empty chars " " and "#".
 */
void initBoard(gBoard *temp);       
/**
 * \brief Fills board with players.
 */
void initPlayers(gBoard *temp);    
/**
 * \brief Copies board.
 * 
 * \param original origin of copy
 * \param copy destination of copy
 * 
 * \note If one of boards is NULL then the program goes into error.
 */
void copyBoard(gBoard *copy, gBoard *original); /*copies board if one of board null then error*/


/*utility below*/


/**
 * \defgroup utility_group Utility functions
 * \brief Utility functions
 * 
 * 
 * 
 * \{
 */

char getTurn(gBoard *temp);      
char getWinner(gBoard *temp); 
/**
 * \brief Changes turn.
 */   
void changeTurn(gBoard *temp);   
/**
 * \brief Based on whos turn it is, it determines the winner if asked.
 */
void selectWinner(gBoard *temp); 
/**
 * \brief Changes winner to 'd' draw.
 */
void drawGame(gBoard *temp);     
/**\}*/
/*----------------------------*/

/*below function that manage movement of the pieces*/

/**
 * \defgroup movement_group Movement
 * \brief Functions that move the peaces on the board
 * \{
 */

/**
 * \brief Manages a normal movement
 * 
 * Moves the peaces, and also takes care of promotion
 * 
 * \param temp board on which the function is workin on 
 * \param list pointer to the list that contains information on all possible movement
 * \param move which of the movement is choosen
 * 
 */
void normalMovement(gBoard *temp, movement *list, int move);
/**
 * \brief Manages a capture movement
 * 
 * Captures, and also takes care of promotion
 * 
 * \param temp board on which the function is workin on 
 * \param list pointer to the list that contains information on all possible capture/eat
 * \param move which of the movement is choosen
 * 
 */
void eatMovement(gBoard *temp, movement *list, int move);

/**\}*/


/*functions used to scan board and determine available movement*/
/**
 * \defgroup check_group Check
 * \brief Check available movement for both sides.
 * \{
 */
/**
 * \brief Checks available movement for White
 * 
 * Checks and saves them using functions in move.h
 * 
*/
void checkWhite(gBoard *temp, movement *list);
/**
 * \brief Checks available movement for Black
 * 
 * Checks and saves them using functions in move.h
 * 
*/
void checkBlack(gBoard *temp, movement *list);
/**\}*/

/*function used by CPU scan to scan board at the end of depth and assign it a value*/
/*wich goes from -100 lost to 100 win, and various values in between that are assigned based on the peaces on the board*/
/**
 * \defgroup cpuScan_group Function used by cpuScan
 * \{
 */
/**
 * \brief Check board and gives it a value.
 * Scans through the board and depending on the position of each peace it add a certain value to the board
 * \param temp Board to scan
 * \param side Used for the sign in the adding
 */
float valueOfBoard(gBoard *temp,char side);
/**\}*/
/*outputs board*/
/**
 * \brief Output to terminal the board
 */
void showBoard(gBoard *temp);
/*reads game from txt file, used for debug*/
/**
 * \brief Read game from .txt file
 * Used to debug some cases when are bugs
 */
void readGame(gBoard *temp);




#endif
