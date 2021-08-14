
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "board.h" 
#include "move.h"



void createMove(movement *temp){
    temp->countEatMove = 0;
    temp->countNormalMove = 0;
    temp->eatMove = NULL;
    temp->normalMove = NULL;
}
void regNormalMove(movement *temp, int fromI, int fromJ, int toI, int toJ){
    temp->countNormalMove = temp->countNormalMove + 1;
    if(temp->normalMove == NULL)
        temp->normalMove = (int **)malloc(temp->countNormalMove * sizeof(int*));
    else
        temp->normalMove = (int **)realloc(temp->normalMove,temp->countNormalMove * sizeof(int*));
    temp->normalMove[temp->countNormalMove-1] = (int *)malloc(4 * sizeof(int));

    temp->normalMove[temp->countNormalMove-1][0] = fromI;
    temp->normalMove[temp->countNormalMove-1][1] = fromJ;
    temp->normalMove[temp->countNormalMove-1][2] = toI;
    temp->normalMove[temp->countNormalMove-1][3] = toJ;
}
void regEatMove(movement *temp, int fromI, int fromJ,int eatI, int eatJ, int toI, int toJ){
    temp->countEatMove = temp->countEatMove + 1;
    if(temp->eatMove == NULL){
        temp->eatMove = (int **)malloc(temp->countEatMove * sizeof(int*));
    }else{
        temp->eatMove = (int **)realloc(temp->eatMove,temp->countEatMove * sizeof(int*));
    }
    temp->eatMove[temp->countEatMove-1] = (int *)malloc(6 * sizeof(int));

    temp->eatMove[temp->countEatMove-1][0] = fromI;
    temp->eatMove[temp->countEatMove-1][1] = fromJ;
    temp->eatMove[temp->countEatMove-1][2] = eatI;
    temp->eatMove[temp->countEatMove-1][3] = eatJ;
    temp->eatMove[temp->countEatMove-1][4] = toI;
    temp->eatMove[temp->countEatMove-1][5] = toJ;
}
void destroyMove(movement *temp){
    int i;
    if(temp->normalMove != NULL){
        for(i=0;i<temp->countNormalMove; i++){
            free(temp->normalMove[i]);
        }
        free(temp->normalMove);
    }
    if(temp->eatMove!= NULL){
        for(i=0;i<temp->countEatMove; i++){
            free(temp->eatMove[i]);
        }
        free(temp->eatMove);
    }
}


void seeMove(movement *temp){
    int i, j;
    printf("\nNormalMoves\n");
    for(i=0; i<temp->countNormalMove;i++){
        for(j=0; j<4;j++){
            printf("%d", temp->normalMove[i][j]);
        }
        printf("\n");
    }
    printf("\nEatMoves");
    for(i=0; i<temp->countEatMove;i++){
        for(j=0; j<6;j++){
            printf("%d", temp->eatMove[i][j]);
        }
        printf("\n");
    }
}


void printNormMoves(movement *temp, float *move){
    int i;
    printf(" moves: \n");
    for(i=0;i<temp->countNormalMove;i++){
        printf("%d From: %d%c ", i+1, temp->normalMove[i][0]+1, temp->normalMove[i][1]+65);
        printf("To: %d%c ", temp->normalMove[i][2]+1, temp->normalMove[i][3]+65);
        if(move != NULL)
            printf("Value: %f \n", move[i]);
        else
            printf("\n");
    }
}
void printEatMoves(movement *temp, float *move){
    int i;
    printf(" eat moves:\n");
    for(i=0;i<temp->countEatMove; i++){
        printf("%d.From: %d%c ", i+1, temp->eatMove[i][0]+1, temp->eatMove[i][1]+65);
        printf("Eat: %d%c ", temp->eatMove[i][2]+1, temp->eatMove[i][3]+65);
        printf("To: %d%c ", temp->eatMove[i][4]+1, temp->eatMove[i][5]+65);
        if(move != NULL)
            printf("Value: %f \n", move[i]);
        else
            printf("\n");
    }
}

void randomChoice(movement *temp, float *move, bool type, int *choice){
    time_t t;
    int i, ti, count =0;
    srand((unsigned) time(&t));
    if(type)
        ti = temp->countEatMove;
    else
        ti= temp->countNormalMove;

    for(i=0; i<ti;i++){
            if(move[*choice] == move[i])
                count++;
    }
    if(count>1){
        int tem = 0;
        count = (rand() % count) +1;
        for(i=0; tem < count;i++){
            if(move[i] == move[*choice])
                tem++;
        }
        *choice = i-1;
    }
}

