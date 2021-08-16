
#include "board.h"
#include "move.h"
#include "participants.h"

/*function used to play game between first participants vs second participants*/
/*using this you can make al the combination without writing the individualty*/
void gameControl(gBoard *pgame, int depthS, int depthE, int first, int second);
/*manages a game between a player vs another entity(player,cpurand,cpuscan,cpueat)*/
void gameManager(int depthS, int depthE);

/*function used to assist function below and make N(tests) of games and save the resault*/
void testManager(int tests, int first, int second, int depthS, int depthE, int *countFirst, int *countSecond, int *countDraw);
/*function used to manage test games for statistics*/
void testCpu(int depthS, int depthE);

