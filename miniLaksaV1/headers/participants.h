/**
 * \file participants.h
 * \brief Contrains the participants and function to make them work.
 * 
 */
#ifndef PRATICIPANTS_H
#define PARTICIPANTS_H

#include"../headers/board.h"
#include"../headers/move.h"


/*the use is playing*/

/**
 * \brief The user decides which move to play.
 * \param temp Board where game is played.
 * 
 * \warning If user inserts 5 times invalid input the program will terminate.
 */
void playerMove(gBoard *temp);

/*cpu randomly*/
/*randomly chooses a move*/
/**
 * \brief Cpu that randomly chooses a move.
 */
void cpuMoveRandom(gBoard *temp);

/*cpu scan */
/*cpu goes through brute forces al possibily to a certain depth*/
/*when it reaches the end it evaluates a board through the func "valueOfBoard" and it gets a value */
/*those values are then added with other posibility after that it devides by the number of outcomes and it gets the final value*/ 
/**
 * \defgroup cpuScan_group Function used by cpuScan
 * \{
 */
/**
 * \brief Recursive function for the Cpu Scan
 * 
 * Goes through every possible move to a certain depth and scans the end cases.
 * 
 * Cases:
 *  - If no possible movement it registeres that the game is lost/won and saves value.
 *  - If depth is zero it scans the board and gets a value.
 *  - If the depth is not zero it checks the moves and recals the #cpuScanRec and decreases depth.
 *  
 * At the end the function returns the value of the move.
 * 
 * \note The function also keeps track of the number of outcomes so after its done, the resault is devided by the outcomes
 * So the cpu doesn't prioritize the longest game but the more advantagious.
 * 
 * \param depth It checks how many depth moves it hase to performa, at each new call of function it decreases by one.
 * \param original Contains the Board on wich the function is working on, if it calls #cpuScanRec before that it creates a copy of the board so it doesnt change the original.
 * \param numberOfOutcomes Keeps track of outcomes.
 * \param side Keeps track of side, so it can decide if add or subtract certain values.
 * 
 * 
 */
float cpuScanRec(int depth, gBoard *original, float *numberOfOutcomes, char side);
/**
 * \brief Cpu that goes through all combinations and at the end scans boards.
 * 
 * This function checks available movement.
 * If there is none the its game lost, if one move available it plays it without calling the recursive function.
 * 
 * But if there is more then one available movement it calls the revursive function for each of available
 * movement that calculates the value of the movement.
 * 
 * After its done it picks the move with the highest value.
 * 
 * \param temp Board where game is played.
 * \param depth Depth used by recursive function.
 * 
 */
void cpuScan(gBoard *temp, int depth);
/**\}*/

/*cpu eat*/
/*cpu goes through brute forces al possibily to a certain depth*/
/*if throughout the game simulation an eat move is perform a value is incresed and when it reaches the end its devided by the depth it stoped*/
/*if it reaches the end before end of depth meaning its a win or a lost a value of 100 is added and its devided by the depthcount*/
/*this way it will prioritize the quickest way to reach the end of a game*/
/**
 * \defgroup cpuEat_group Function used by cpuEat
 * \{
 */
/**
 * \brief Recursive function for the Cpu Eat
 * 
 * Goes throught each of possible move to a certain depth and takes in consideration the captures
 * 
 * Cases:
 *  - If no available movement it registeres the value as a win/loss and then devides by the depth count
 *  - If depth is zero then the value is devided by the depth count and returned
 *  - If depth is not zero it checks move and for each move it calls the function #cpuEatMove:
 *      - If it's a normal move it does nothing
 *      - If capture move then it adds or subtracts a certain value 
 * 
 * \param original Board on which the function is working on.
 * \param depth Keeps track of how much still has to go into depth
 * \param depthCount Keeps track of current depth and used to divide the value at the end
 * so a win of a deeper depth has less value then the one higher
 * \param value Stores the value of the move, each time there is a capture it is increased
 * or decreased depending on the side
 * \param numberOfOutcomes Counts the possible outcomes it is used later in the #cpuEat to devide the returned value
 * \param side Tracks the side, used in the value manipulation
 * 
 * 
 * 
 * 
 */
float cpuEatRec(gBoard *original, int depth, int depthCount, float value, int *numberOfOutcomes, char side);
/**
 * \brief Cpu that goes through all combinations and takes count of the captures.
 * 
 * Cpu Eat function that focuses on capture to evaluete the best move.
 * 
 * Checks available movement.
 * If There is none then its game lost, if only move available it plays it without calling the recursive function.
 * 
 * But if there is more then one available movement it calls the recursive function(#cpuEatRec) for each of available
 * movement that calculates the value of the movement.
 * 
 * After its done it picks the move with the highest value.
 * 
 * \param temp Board where game is played.
 * \param depth Depth used by recursive function.
 * 
 */
void cpuEat(gBoard *temp, int depth);
/**\}*/
#endif
