#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#include "participants.h"
#include "board.h"
#include "move.h"


void playerMove(gBoard *temp){
    movement list;
    movement *plist;
    int i, move;
    plist = &list;
    createMove(plist);

    if(temp->turn == 'w'){          /*checking moves*/
        checkWhite(temp,plist);
        printf("\nWhite ");
    }else if (temp->turn == 'b'){
        checkBlack(temp, plist);
        printf("\nBlack ");
    }
    if(plist->countEatMove==0 && plist->countNormalMove==0){    /*no moves (lost)*/
        printf("no moves.\n");
        selectWinner(temp);
        destroyMove(plist);
    }
    else if(plist->countEatMove != 0){          /*eat moves available*/
        printEatMoves(plist,NULL);
        printf("Enter Move: ");
        scanf("%d", &move );
        if(move < 0 || move > list.countEatMove){
            printf("\n Error move\n");
            exit(4);
        }
        eatMovement(temp, plist, move-1);
    }
    else{                                      /*normal moves available*/
        printNormMoves(plist, NULL);
        printf("Enter Move: ");
        scanf("%d", &move );
        if(move < 0 || move > list.countNormalMove){
            printf("\n Error move\n");
            exit(4);
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

    if(temp->turn == 'w'){
        checkWhite(temp,plist);
        if(plist->countEatMove==0 && plist->countNormalMove==0){
            temp->winner = 'b';
            destroyMove(plist);
            return;
        }
        printf("\nWhite ");
    }else if (temp->turn == 'b'){
        checkBlack(temp, plist);
        if(plist->countEatMove==0 && plist->countNormalMove==0){
            temp->winner = 'w';
            destroyMove(plist);
            return;
        }
        printf("\nBlack ");
    }
    if(plist->countEatMove != 0){
        printf("cpu eat move:\n");
        move = rand() % plist->countEatMove;
        printf("From: %d%c ", plist->eatMove[move][0]+1, plist->eatMove[move][1]+65);
        printf("Eat: %d%c ", plist->eatMove[move][2]+1, plist->eatMove[move][3]+65);
        printf("To: %d%c\n", plist->eatMove[move][4]+1, plist->eatMove[move][5]+65);
        eatMovement(temp, plist, move);

    }else{
        printf("cpu move:\n");
        move = rand() % plist->countNormalMove;
        printf("From: %d%c ", plist->normalMove[move][0]+1, plist->normalMove[move][1]+65);
        printf("To: %d%c\n", plist->normalMove[move][2]+1, plist->normalMove[move][3]+65);
        normalMovement(temp,plist,move);
    }

    changeTurn(temp);
    destroyMove(plist);
}
float valueOfBoard(gBoard *temp,char side){         /*scans and assigns value to a board*/
    int i,j,k;
    float countBlack = 0, countWhite = 0;

    for(i=0; i<7; i++){
        for(j=0; j<7; j++){
            for(k=0; k<3; k++){
                if(temp->Board[i][j][k] == 'W'){
                    if(k == 0)
                        countWhite += 2;
                    else if(k == 1 || k == 2)
                        countWhite += 0.40;
                }
                if(temp->Board[i][j][k] == 'w'){
                    if(k == 0)
                        countWhite += 1;
                    else if(k==1 || k == 2)
                        countWhite += 0.20;
                }
                if(temp->Board[i][j][k] == 'B'){
                    if(k == 0)
                        countBlack += 2;
                    else if(k == 1 || k == 2)
                        countBlack += 0.40;
                }
                if(temp->Board[i][j][k] == 'b'){
                    if(k == 0)
                        countBlack += 1;
                    else if(k==1 || k == 2)
                        countBlack += 0.20;
                }
            }
        }
    }

    if(side == 'w'){
        if(countWhite>=countBlack)
            return (float) ((countWhite * 100.0)/(countWhite + countBlack));
        else
            return (float) (-1)* ((countBlack * 100.0)/(countWhite + countBlack));
    }else{
        if(countBlack >= countWhite)
            return (float) ((countBlack * 100.0)/(countWhite + countBlack));
        else
            return (float) (-1)*((countWhite * 100.0)/(countWhite + countBlack));
    }

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

    if(plist->countEatMove == 0 && plist->countNormalMove == 0){
        *numberOfOutcomes += 1;
        destroyMove(plist);
        destroyBoard(original);
        if(side == original->turn)
            return -100;
        else
            return +100;
    }
    if(depth == 0){

        float temp = valueOfBoard(original,side);
        *numberOfOutcomes +=1;
        destroyBoard(original);
        destroyMove(plist);
        return temp;
    }

    if(plist->countEatMove>1){
        float temp = 0;
        for(i = 0; i< plist->countEatMove; i++){
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
    if(plist->countEatMove == 1){
        eatMovement(original,plist,0);
        destroyMove(plist);
        changeTurn(original);
        return cpuScanRec(depth-1, original, numberOfOutcomes, side);
    }
    if(plist->countNormalMove>1){
        float temp=0;
        for(i = 0; i< plist->countNormalMove; i++){
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
    if(plist->countNormalMove == 1){
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

    createMove(plist);
    if(temp->turn== 'w'){
        checkWhite(temp,plist);
        printf("\nWhite ");
    }
    else if(temp->turn == 'b'){
        checkBlack(temp,plist);
        printf("\nBlack ");
    }

    if(plist->countEatMove == 0 && plist->countNormalMove == 0){
        selectWinner(temp);
        printf("no moves Available.\n");
    }
    else if(plist->countEatMove == 1){
        eatMovement(temp,plist,0);
        printEatMoves(plist,NULL);

    }
    else if(plist->countEatMove == 0 && plist->countNormalMove == 1){
        normalMovement(temp,plist,0);
        printNormMoves(plist,NULL);
    }
    else if(plist->countEatMove > 1){
        move = malloc(plist->countEatMove * sizeof(float));
        for(i=0; i<plist->countEatMove; i++){
            createBoard(pdummy);
            copyBoard(pdummy, temp);
            eatMovement(pdummy,plist,i);
            move[i] = cpuScanRec(depth,pdummy, pOut,temp->turn);
            move[i] =  (move[i] /outcomes);
            outcomes = 0;
        }
        for(i = 0; i<plist->countEatMove;i++){
            if(move[choice]<move[i])
                choice = i;
        }
        printEatMoves(plist,move);
        randomChoice(plist,move,true,&choice);
        printf("\nFinal choice: %d\n", choice+1);
        eatMovement(temp, plist, choice);
    }
    else if(plist->countNormalMove > 1){
        move = malloc(plist->countNormalMove * sizeof(float));
        for(i=0; i<plist->countNormalMove; i++){
            createBoard(pdummy);
            copyBoard(pdummy, temp);
            normalMovement(pdummy,plist,i);
            move[i] = cpuScanRec(depth,pdummy, pOut,temp->turn);
            move[i] =  (move[i] /outcomes);
            outcomes = 0;
        }
        for(i = 0; i< plist->countNormalMove;i++){
            if(move[choice]<move[i])
                choice = i;
        }
        printNormMoves(plist,move);
        randomChoice(plist,move,false,&choice);
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
    if(side == original->turn)
        sign = +1;
    else
        sign = -1;

    plist = &list;
    pdummy = &dummy;
    createMove(plist);

    if(original->turn == 'w')
        checkWhite(original, plist);
    else if(original->turn == 'b')
        checkBlack(original,plist);

    if(plist->countEatMove == 0 && plist->countNormalMove == 0){
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
    if(depth == 0){
        *numberOfOutcomes += 1;
        destroyBoard(original);
        destroyMove(plist);
        return value/depthCount;
    }
    if(plist->countEatMove==1){
        eatMovement(original,plist,0);
        destroyMove(plist);
        changeTurn(original);
        return cpuEatRec(original,depth-1, depthCount+1,value+(sign * 40),numberOfOutcomes,side);
    }
    if(plist->countEatMove>1){
        float temp = 0;
        int i;

        for(i=0;i<plist->countEatMove;i++){
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
    if(plist->countNormalMove == 1){
        normalMovement(original,plist,0);
        destroyMove(plist);
        changeTurn(original);
        return cpuEatRec(original,depth-1,depthCount+1,value,numberOfOutcomes,side);
    }
    if(plist->countNormalMove > 1){

        float temp = 0;
        int i;

        for(i=0;i<plist->countNormalMove;i++){
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
    if(temp->turn== 'w'){
        checkWhite(temp,plist);
        printf("\nWhite ");
    }
    else if(temp->turn == 'b'){
        checkBlack(temp,plist);
        printf("\nBlack ");
    }

    if(plist->countEatMove == 0 && plist->countNormalMove == 0){
        selectWinner(temp);
        printf("no moves Available.\n");
    }
    else if(plist->countEatMove == 1){
        eatMovement(temp,plist,0);
        printEatMoves(plist,NULL);
    }
    else if(plist->countEatMove == 0 && plist->countNormalMove == 1){
        normalMovement(temp,plist,0);
        printNormMoves(plist,NULL);
    }
    else if(plist->countEatMove > 1){
        move = malloc(plist->countEatMove * sizeof(float));
        for(j=0;j<plist->countEatMove; j++){
            createBoard(pdummy);
            copyBoard(pdummy,temp);
            eatMovement(pdummy,plist,j);
            changeTurn(pdummy);
            move[j] = cpuEatRec(pdummy,depth,1,50,pout,temp->turn);
            move[j] /= outcomes;
            outcomes = 0;
        }

        for(j=0; j<plist->countEatMove; j++){
            if(move[choice]<move[j])
                choice = j;

        }
        printEatMoves(plist,move);
        randomChoice(plist,move,true,&choice);
        printf("\nFinal choice: %d \n", choice+1);
        eatMovement(temp,plist,choice);

    }
    else if(plist->countNormalMove>1){
        move = malloc(plist->countNormalMove * sizeof(float));
        for(j=0;j<plist->countNormalMove; j++){
            createBoard(pdummy);
            copyBoard(pdummy,temp);
            normalMovement(pdummy,plist,j);
            changeTurn(pdummy);
            move[j] = cpuEatRec(pdummy,depth,1,0,pout,temp->turn);
            move[j] = move[j] / outcomes;
            outcomes = 0;
        }
        for(j=0; j<plist->countNormalMove; j++){
            if(move[choice]<move[j])
                choice = j;
        }
        printNormMoves(plist,move);
        randomChoice(plist,move,false,&choice);
        printf("\nFinal choice: %d \n", choice+1);
        normalMovement(temp,plist,choice);
    }
    if(move != NULL)
        free(move);
    destroyMove(plist);
    changeTurn(temp);

}

