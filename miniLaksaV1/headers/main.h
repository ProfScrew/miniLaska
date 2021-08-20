
/**
 * 
 * \file main.h
 * \author Maksym Novytskyy
 * \version 1.0
 * \brief Contains main menu and submenus.
 * \date 17/08/2021
 * \mainpage miniLaska
 * \section intro_sec Introduction
 * 
 * The miniLaska is a small version of the original game http://www.laska.org
 * 
 * Limitation of the game:
 * 
 * - can conquer/eat only once per turn
 * 
 * - the max height of the stack is 3 max, if limit exceded the pawn is removed
 * 
 * - if none of the players wins in 100 moves the game is a draw
 * 
 * \section compile_sec Compile
 * 
 * In this section will stated how to make the game run and the requiments for it.
 * 
 * \subsection require_sec Required gcc
 * 
 * 
 * 
 * Make sure that you have gcc installed.
 *  If its not installed, here is a small guide on how to do it using a terminal:
 * 
 * 1. Start by updating the packages list:
 * 
 *          sudo apt update
 * 
 * 2. Install the <b>build-essential</b>:
 * 
 *          sudo apt install build-essential
 * 
 * 3. Validate if installed using the following comand
 * 
 *          gcc --version
 * 
 * \subsection compilatio_sec Compilation
 * 
 * To compile the program make use of the <b>Makefile</b> by using only the simple comand
 * in the same folder:
 * 
 *          make
 * 
 * This comand will execute the following command to compile the game:
 * 
 *          gcc -ansi -pedantic -Wno-unused-result -O2 src/main.c src/board.c src/move.c src/participants.c -o miniLaska
 * 
 * It has the following parameters:
 * 
 * -ansi: tells the compiler to implement the ANSI language option. This turns off certain "features" of GCC which are incompatible with the ANSI standard.
 * 
 * -pedantic used in conjunction with -ansi, this tells the compiler to be adhere strictly to the ANSI standard, rejecting any code which is not compliant.
 * 
 * -Wno-unused-result means that it will ignore the unused result warning, which occurs during the usage of the <ins>scanf()</ins> comand
 * 
 * \subsection exe_sec Execution 
 * 
 * To execute the program use the file <b>miniLaska</b> created by the previous command. 
 * 
 *          ./miniLaska
 * 
 * \section menu_sec Main Menu
 * 
 * When the program is started the menu will appear with the following options:
 * 
 * \subsection game_sec  Play Game
 * 
 * Allows the user to play the game. The user has then the following choice:
 * 
 * - Player vs Player
 * 
 * - Player vs Random
 * 
 * - Player vs CPU Scan
 * 
 * - Player vs CPU Eat
 * 
 * And after choosing the following game will start.
 * 
 * \note Also the user has the choice of which side he wants to play.
 * 
 * \warning If the user during the game makes 5 mistakes consecutively(inserts invalid number) the program will terminate
 * 
 * \subsection test_sec Test CPU vs CPU
 * 
 * This option allows user to test the cpus and see the resault.
 * 
 * To use this the user need to insert the number of tests he wants to perform 
 * 
 * and what type of test.
 * 
 * There are two types of test:
 * 
 *  - single: Here the user will have to choose the cpus that will fight each other
 * 
 *  - full: This option will test all the combination of the cpus so the number of test will be multiplied by 9
 * 
 * The three cpus are:
 * 
 *  1. #cpuMoveRandom: it randomly chooses the option.
 * 
 *  2. #cpuScan: analizes in depth all possibility and gives each posibility towards the end a value (#valueOfBoard),
 * these values are then added and devided by the number of outcomes and the end the cpu chooses the best outcome.
 * 
 *  3. #cpuScan: analizes in depth all posibility and if there is an capture a certain value is added after that che cpu
 * will determine the option with the highest value of captures and choose it.
 * 
 * \note The draw function was implemente because on some positions the cpus entered a loop 
 * 
 * \subsection setting_sec Setting depth CPU
 * 
 * Here the user can setup the depth of each cpu. If the depth is invalid it will go to the default settings.
 * 
 * \subsection exit_sec Exit
 * 
 * Terminates the program.
 */


#include "../headers/board.h"
#include "../headers/move.h"
#include "../headers/participants.h"

/*function used to play game between first participants vs second participants*/
/*using this you can make al the combination without writing the individualty*/
/**
 * \brief Function used to operate games between two entities
 * 
 * Function controlls game and chooses the respective participant to play.
 * 
 * \param pgame pointer to the board on which the game is played
 * \param depthS depth used by the #cpuScan function 
 * \param depthE depth used by the #cpuEat function
 * \param first value used to decide first parcipiant(White)
 * \param second value used to decide second participant("Black")
 * 
 * \note Playes the two parcipant function in a loop and checks if there is a winner or draw
*/
void gameControl(gBoard *pgame, int depthS, int depthE, int first, int second);
/*manages a game between a player vs another entity(player,cpurand,cpuscan,cpueat)*/
/**
 * \brief Function that lets user decide who to play against
 * 
 * After choosing the function calls #gameControl to play the game
 * 
 * \param depthS depth used by the #cpuScan function 
 * \param depthE depth used by the #cpuEat function
*/
void gameManager(int depthS, int depthE);

/*function used to assist function below and make N(tests) of games and save the resault*/
/**
 * \brief Applies the setting of the test and simulates games
 * 
 * \param tests number of tests to perform
 * \param first first participant(White)
 * \param second second participant(Black)
 * \param depthS depth used by the #cpuScan function 
 * \param depthE depth used by the #cpuEat function
 * \param countFirst counter of White wins
 * \param countSecond counter of Black wins
 * \param countDraw counter of Draws 
 * 
 * 
*/
void testManager(int tests, int first, int second, int depthS, int depthE, int *countFirst, int *countSecond, int *countDraw);
/*function used to manage test games for statistics*/
/**
 * \brief Let user decide setting of the test 
 * 
 * \param depthS depth used by the #cpuScan function 
 * \param depthE depth used by the #cpuEat function
 * 
 * 
*/
void testCpu(int depthS, int depthE);

