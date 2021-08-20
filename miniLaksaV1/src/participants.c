#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#include "../headers/participants.h"
#include "../headers/board.h"
#include "../headers/move.h"


void playerMove(gBoard *temp){
    movement list;
    movement *plist;
    int i, move=0;
    plist = &list;
    createMove(plist);

    if(getTurn(temp) == 'w'){          /*checking moves*/
        checkWhite(temp,plist);
        printf("\nWhite ");
    }else if (getTurn(temp) == 'b'){
        checkBlack(temp, plist);
        printf("\nBlack ");
    }
    if(getCountEat(plist)==0 && getCountNormal(plist)==0){    /*no moves (lost)*/
        printf("no moves.\n");
        selectWinner(temp);
        destroyMove(plist);
    }
    else if(getCountEat(plist) != 0){          /*eat moves available*/
        int count=0;
        printEatMoves(plist,NULL);
        while(move<1 || move > getCountEat(plist)){
            printf("Enter Move: ");
            scanf("%d", &move );
            if(move < 1 || move > getCountEat(plist)){
                count++;
                printf("\n Error move! Try again.(%d available mistakes)\n",(5-count));
                if(count == 5){
                    printf("\nExceded limit mistakes\n");
                    exit(4);
                }
            }
        }
        eatMovement(temp, plist, move-1);
    }
    else{                                      /*normal moves available*/
        int count=0;
        printNormMoves(plist, NULL);
        while (move<1 || move>getCountNormal(plist))
        {
            printf("Enter Move: ");
            scanf("%d", &move );
            if(move < 1 || move > getCountNormal(plist)){
                count++;
                printf("\n Error move! Try again.(%d available mistakes)\n",(5-count));
                if(count == 5){
                    printf("\nExceded limit mistakes\n");
                    exit(4);
                }
            }
        }
        normalMovement(temp,plist,move-1);
    }
    changeTurn(temp);
    destroyMove(plist);
}
void cpuMoveRandom(gBoard *temp){
    int i, move;
    movement list;
    movement *plist;
    time_t t;
    srand((unsigned) time(&t));
    plist = &list;
    createMove(plist);

    if(getTurn(temp) == 'w'){
        checkWhite(temp,plist);
        if(getCountEat(plist)==0 && getCountNormal(plist)==0){
            selectWinner(temp);
            destroyMove(plist);
            return;
        }
        printf("\nWhite ");
    }else if (getTurn(temp) == 'b'){
        checkBlack(temp, plist);
        if(getCountEat(plist)==0 && getCountNormal(plist)==0){
            selectWinner(temp);
            destroyMove(plist);
            return;
        }
        printf("\nBlack ");
    }
    if(getCountEat(plist) != 0){
        printEatMoves(plist,NULL);
        move = rand() % getCountEat(plist);
        printf("Final Choice Rand: %d \n", move);
        eatMovement(temp, plist, move);

    }else{
        printNormMoves(plist,NULL);
        move = rand() % getCountNormal(plist);
        printf("Final choice rand: %d \n", move);
        normalMovement(temp,plist,move);
    }

    changeTurn(temp);
    destroyMove(plist);
}

float cpuScanRec(int depth, gBoard *original, float *numberOfOutcomes, char side){
    gBoard dummy;
    gBoard *pdummy;
    movement list;
    movement *plist;
    int i;
    pdummy = &dummy;
    plist = &list;
    createMove(plist);
    if(getTurn(original) == 'w')
        checkWhite(original, plist);
    else if(getTurn(original) == 'b')
        checkBlack(original, plist);

    if(getCountEat(plist) == 0 && getCountNormal(plist) == 0){  /*lost situation*/
        *numberOfOutcomes += 1;
        destroyMove(plist);
        destroyBoard(original);
        if(side == original->turn)
            return -100;
        else
            return +100;
    }
    if(depth == 0){     /*reaches the end of depth*/

        float temp = valueOfBoard(original,side);
        *numberOfOutcomes +=1;
        destroyBoard(original);
        destroyMove(plist);
        return temp;
    }

    if(getCountEat(plist)>1){       /*the option below are used to go down each move decreasing depth*/
        float temp = 0;
        for(i = 0; i< getCountEat(plist); i++){
            createBoard(pdummy);
            copyBoard(pdummy,original);
            eatMovement(pdummy,plist,i);
            changeTurn(pdummy);
            temp += cpuScanRec(depth-1,pdummy,numberOfOutcomes,side);

        }
        destroyMove(plist);
        destroyBoard(original);
        return temp;

    }
    if(getCountEat(plist) == 1){    
        eatMovement(original,plist,0);
        destroyMove(plist);
        changeTurn(original);
        return cpuScanRec(depth-1, original, numberOfOutcomes, side);
    }
    if(getCountNormal(plist)>1){
        float temp=0;
        for(i = 0; i< getCountNormal(plist); i++){
            createBoard(pdummy);
            copyBoard(pdummy,original);
            normalMovement(pdummy, plist,i);
            changeTurn(pdummy);
            temp += cpuScanRec(depth-1,pdummy, numberOfOutcomes, side);

        }
        destroyMove(plist);
        destroyBoard(original);
        return temp;
    }
    if(getCountNormal(plist) == 1){
        normalMovement(original,plist,0);
        destroyMove(plist);
        changeTurn(original);
        return cpuScanRec(depth-1, original, numberOfOutcomes, side);
    }

    return 0;
}
void cpuScan(gBoard *temp, int depth){

    movement list;
    movement *plist;
    gBoard dummy;
    gBoard *pdummy;

    float *move = NULL;
    int count = 0;
    int i, choice = 0;
    float outcomes = 0;
    float *pOut;

    pOut = &outcomes;
    pdummy = &dummy;
    plist = &list;
                            /*checks move*/
    createMove(plist);
    if(getTurn(temp)== 'w'){
        checkWhite(temp,plist);
        printf("\nWhite ");
    }
    else if(getTurn(temp) == 'b'){
        checkBlack(temp,plist);
        printf("\nBlack ");
    }

    if(getCountEat(plist) == 0 && getCountNormal(plist) == 0){  /*no moves lost*/
        selectWinner(temp);
        printf("no moves Available.\n");
    }
    else if(getCountEat(plist) == 1){   /*one move available so no need to calculate*/
        eatMovement(temp,plist,0);
        printEatMoves(plist,NULL);

    }
    else if(getCountEat(plist) == 0 && getCountNormal(plist) == 1){ /*one move available*/
        normalMovement(temp,plist,0);
        printNormMoves(plist,NULL);
    }
    else if(getCountEat(plist) > 1){        /*possible multiple eat moves start recursive function to calculate*/
        move = malloc(getCountEat(plist) * sizeof(float));
        for(i=0; i<getCountEat(plist); i++){
            createBoard(pdummy);
            copyBoard(pdummy, temp);
            eatMovement(pdummy,plist,i);
            move[i] = cpuScanRec(depth,pdummy, pOut,temp->turn);
            move[i] =  (move[i] /outcomes);
            outcomes = 0;
        }
        for(i = 0; i<getCountEat(plist);i++){   /*chooses wich move to make from evaluation if top has 2 or more value*/
            if(move[choice]<move[i])            /*random choise between those two are made*/
                choice = i;
        }
        printEatMoves(plist,move);
        choice = randomChoice(plist,move,true, choice);
        printf("\nFinal choice: %d\n", choice+1);
        eatMovement(temp, plist, choice);
    }
    else if(getCountNormal(plist) > 1){     /*possible multiple normal moves start recursive function to calculate*/
        move = malloc(getCountNormal(plist) * sizeof(float));
        for(i=0; i<getCountNormal(plist); i++){
            createBoard(pdummy);
            copyBoard(pdummy, temp);
            normalMovement(pdummy,plist,i);
            move[i] = cpuScanRec(depth,pdummy, pOut,temp->turn);
            move[i] =  (move[i] /outcomes);
            outcomes = 0;
        }
        for(i = 0; i< getCountNormal(plist);i++){   /*choice between moves and random if same value*/
            if(move[choice]<move[i])
                choice = i;
        }
        printNormMoves(plist,move);
        choice = randomChoice(plist,move,false, choice);
        printf("\nFinal choice: %d\n", choice+1);
        normalMovement(temp, plist, choice);
    }
    if(move != NULL)
        free(move);
    destroyMove(plist);
    changeTurn(temp);


}

float cpuEatRec(gBoard *original, int depth, int depthCount, float value, int *numberOfOutcomes, char side){

    gBoard dummy;
    gBoard *pdummy;

    movement list;
    movement *plist;
    int sign;
    if(side == getTurn(original))
        sign = +1;
    else
        sign = -1;

    plist = &list;
    pdummy = &dummy;
    createMove(plist);

    if(getTurn(original) == 'w')    /*check*/
        checkWhite(original, plist);
    else if(getTurn(original) == 'b')
        checkBlack(original,plist);

    if(getCountEat(plist) == 0 && getCountNormal(plist) == 0){  /*no moves value +/- 100 then devided by depth*/
        if(side == original->turn)
            value -= 100;
        else
            value += 100;

        value /= depthCount;
        destroyMove(plist);
        destroyBoard(original);
        *numberOfOutcomes +=1;
        return value;
    }
    if(depth == 0){     /*end depth*/
        *numberOfOutcomes += 1;
        destroyBoard(original);
        destroyMove(plist);
        return value/depthCount;
    }
    if(getCountEat(plist)==1){      /*one eat choice has an increas or decreas of value*/
        eatMovement(original,plist,0);
        destroyMove(plist);
        changeTurn(original);
        return cpuEatRec(original,depth-1, depthCount+1,value+(sign * 40),numberOfOutcomes,side);
    }
    if(getCountEat(plist)>1){   /*multiple choice inc/decr*/
        float temp = 0;
        int i;

        for(i=0;i<getCountEat(plist);i++){
            createBoard(pdummy);
            copyBoard(pdummy,original);
            eatMovement(pdummy,plist,i);
            changeTurn(pdummy);
            temp+=cpuEatRec(pdummy,depth-1,depthCount+1,value+(sign * 40),numberOfOutcomes,side);
        }
        destroyBoard(original);
        destroyMove(plist);
        return temp;
    }
    if(getCountNormal(plist) == 1){     /*normal move value stays the same*/
        normalMovement(original,plist,0);
        destroyMove(plist);
        changeTurn(original);
        return cpuEatRec(original,depth-1,depthCount+1,value,numberOfOutcomes,side);
    }
    if(getCountNormal(plist) > 1){  /*normal move value same*/

        float temp = 0;
        int i;

        for(i=0;i<getCountNormal(plist);i++){
            createBoard(pdummy);
            copyBoard(pdummy,original);
            normalMovement(pdummy,plist,i);
            changeTurn(pdummy);
            temp+=cpuEatRec(pdummy,depth-1,depthCount+1,value,numberOfOutcomes,side);
        }
        destroyMove(plist);
        destroyBoard(original);
        return temp;

    }

    return 0;


}
void cpuEat(gBoard *temp, int depth){

    gBoard dummy;
    gBoard *pdummy;
    movement list;
    movement *plist;

    int choice = 0;
    float *move = NULL;
    int j;
    int outcomes = 0;
    int *pout;

    pdummy = &dummy;
    plist = &list;
    pout = &outcomes;

    createMove(plist);
    if(getTurn(temp)== 'w'){        /*check*/
        checkWhite(temp,plist);
        printf("\nWhite ");
    }
    else if(getTurn(temp) == 'b'){
        checkBlack(temp,plist);
        printf("\nBlack ");
    }

    if(getCountEat(plist) == 0 && getCountNormal(plist) == 0){  /*lost*/
        selectWinner(temp);
        printf("no moves Available.\n");
    }
    else if(getCountEat(plist) == 1){   /*one move so no calculation*/
        eatMovement(temp,plist,0);
        printEatMoves(plist,NULL);
    }
    else if(getCountEat(plist) == 0 && getCountNormal(plist) == 1){     /*one move so no calculation*/
        normalMovement(temp,plist,0);
        printNormMoves(plist,NULL);
    }
    else if(getCountEat(plist) > 1){    /*eat moves start recursive function*/
        move = malloc(getCountEat(plist) * sizeof(float));
        for(j=0;j<getCountEat(plist); j++){
            createBoard(pdummy);
            copyBoard(pdummy,temp);
            eatMovement(pdummy,plist,j);
            changeTurn(pdummy);
            move[j] = cpuEatRec(pdummy,depth,1,50,pout,temp->turn);
            move[j] /= outcomes;
            outcomes = 0;
        }

        for(j=0; j<getCountEat(plist); j++){        /*choice based on evaluation*/
            if(move[choice]<move[j])
                choice = j;

        }
        printEatMoves(plist,move);
        choice = randomChoice(plist,move,true,choice);
        printf("\nFinal choice: %d \n", choice+1);
        eatMovement(temp,plist,choice);

    }
    else if(getCountNormal(plist)>1){   /*normal moves start recursive function*/
        move = malloc(getCountNormal(plist) * sizeof(float));
        for(j=0;j<getCountNormal(plist); j++){
            createBoard(pdummy);
            copyBoard(pdummy,temp);
            normalMovement(pdummy,plist,j);
            changeTurn(pdummy);
            move[j] = cpuEatRec(pdummy,depth,1,0,pout,temp->turn);
            move[j] = move[j] / outcomes;
            outcomes = 0;
        }
        for(j=0; j<getCountNormal(plist); j++){     /*choice based on evaluation*/
            if(move[choice]<move[j])
                choice = j;
        }
        printNormMoves(plist,move);
        choice = randomChoice(plist,move,false,choice);
        printf("\nFinal choice: %d \n", choice+1);
        normalMovement(temp,plist,choice);
    }
    if(move != NULL)
        free(move);
    destroyMove(plist);
    changeTurn(temp);

}
