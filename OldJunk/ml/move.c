#include <stdio.h>
#include <stdlib.h>
#include "move.h"
#include "board.h"

void initMovement(movement *temp){

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
void freeMove(movement *temp){
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


void checkWhite(gBoard *temp, movement *list){
    int i, j;
    for(i=0; i<7; i++){
        for(j=0; j<7; j++){
            if(temp->Board[i][j][0] == 'w'){
                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*can move bot left*/
                    if(temp->Board[i+1][j-1][0] == ' ')
                        regNormalMove(list, i, j, (i+1), (j-1));
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 )) /*can move bot right*/
                    if(temp->Board[i+1][j+1][0]== ' ')
                        regNormalMove(list, i, j , (i+1), (j+1));
                /*eat moves below */
                /**/
                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left move */
                    if((temp->Board[i+1][j-1][0] == 'b')|| (temp->Board[i+1][j-1][0] == 'B'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j-2) >= 0 && (j-2) < 7 )) /*can eat bottom left */
                            if(temp->Board[i+2][j-2][0]== ' ')
                                regEatMove(list, i, j, (i+1), (j-1), (i+2), (j-2));
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 )) /*check bottom right move*/
                    if((temp->Board[i+1][j+1][0] == 'b')|| (temp->Board[i+1][j+1][0] == 'B'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))/*can eat bottom right*/
                            if(temp->Board[i+2][j+2][0]== ' ')
                                regEatMove(list, i,j,i+1,j+1,i+2,j+2);
            }

            if(temp->Board[i][j][0] == 'W'){
                /*first part normal moves to blank spot */
                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 )) /*check bottom left*/
                    if(temp->Board[i+1][j-1][0] == ' ')
                        regNormalMove(list, i, j, (i+1), (j-1));
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check bottom right*/
                    if(temp->Board[i+1][j+1][0] == ' ')
                        regNormalMove(list,i, j, (i+1), (j+1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check top left*/
                    if(temp->Board[i-1][j-1][0] == ' ')
                        regNormalMove(list,i, j, (i-1), (j-1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check top right*/
                    if(temp->Board[i-1][j+1][0] == ' ')
                        regNormalMove(list, i, j, (i-1), (j+1));
                /* eat moves below*/

                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left move */
                    if((temp->Board[i+1][j-1][0] == 'b')|| (temp->Board[i+1][j-1][0] == 'B'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))
                            if(temp->Board[i+2][j-2][0]== ' ')
                                regEatMove(list, i,j,i+1,j-1,i+2,j-2);
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check bottom right move*/
                    if(((temp->Board[i+1][j+1][0] == 'b')|| (temp->Board[i+1][j+1][0] == 'B')))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))
                            if(temp->Board[i+2][j+2][0]== ' ')
                                regEatMove(list,i,j,i+1,j+1,i+2,j+2);
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check top left move */
                    if((temp->Board[i-1][j-1][0] == 'b')|| (temp->Board[i-1][j-1][0] == 'B'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))
                            if(temp->Board[i-2][j-2][0]== ' ')
                                regEatMove(list,i,j,i-1,j-1,i-2,j-2);

                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check top right move*/
                    if((temp->Board[i-1][j+1][0] == 'b')|| (temp->Board[i-1][j+1][0] == 'B'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))
                            if(temp->Board[i-2][j+2][0]== ' ')
                                regEatMove(list, i,j,i-1,j+1,i-2,j+2);
            }
        }
    }
}
void checkBlack(gBoard *temp, movement *list){
    int i, j;

    for(i=0; i<7; i++){
        for(j=0; j<7; j++){
            if(temp->Board[i][j][0] == 'b'){
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*can top bot left*/
                    if(temp->Board[i-1][j-1][0] == ' ')
                        regNormalMove(list,i, j, (i-1), (j-1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*can top bot right*/
                    if(temp->Board[i-1][j+1][0]== ' ')
                        regNormalMove(list,i, j, (i-1), (j+1));
                /*remember to put else */
                /**/
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left move */
                    if((temp->Board[i-1][j-1][0] == 'w')|| (temp->Board[i-1][j-1][0] == 'W'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))/*can eat bottom left */
                            if(temp->Board[i-2][j-2][0]== ' ')
                                regEatMove(list,i,j,i-1,j-1,i-2,j-2);
                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check bottom right move*/
                    if((temp->Board[i-1][j+1][0] == 'w')|| (temp->Board[i-1][j+1][0] == 'W'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j+2) >= 0 && (j+2) < 7 )) /*can eat bottom right*/
                            if(temp->Board[i-2][j+2][0]== ' ')
                                regEatMove(list, i,j,i-1,j+1,i-2,j+2);
            }
            if(temp->Board[i][j][0] == 'B'){
                /*first part normal moves to blank spot */
                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left*/
                    if(temp->Board[i+1][j-1][0] == ' ')
                        regNormalMove(list, i, j, (i+1), (j-1));
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check bottom right*/
                    if(temp->Board[i+1][j+1][0] == ' ')
                        regNormalMove(list, i, j, (i+1), (j+1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check top left*/
                    if(temp->Board[i-1][j-1][0] == ' ')
                        regNormalMove(list,i, j, (i-1), (j-1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 )) /*check top right*/
                    if(temp->Board[i-1][j+1][0] == ' ')
                        regNormalMove(list, i, j, (i-1), (j+1));

                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left move */
                    if((temp->Board[i+1][j-1][0] == 'w')|| (temp->Board[i+1][j-1][0] == 'W'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))
                            if(temp->Board[i+2][j-2][0]== ' ')
                                regEatMove(list, i,j,i+1,j-1,i+2,j-2);
                if((i+1) >= 0 && (i+1) < 7 && (j+1) >= 0 && (j+1) < 7 )/*check bottom right move*/
                    if((temp->Board[i+1][j+1][0] == 'w')|| (temp->Board[i+1][j+1][0] == 'W'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))
                            if(temp->Board[i+2][j+2][0]== ' ')
                                regEatMove(list, i,j,i+1,j+1,i+2,j+2);
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check top left move */
                    if((temp->Board[i-1][j-1][0] == 'w')|| (temp->Board[i-1][j-1][0] == 'W'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))
                            if(temp->Board[i-2][j-2][0]== ' ')
                                regEatMove(list, i,j,i-1,j-1,i-2,j-2);

                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check top right move*/
                    if((temp->Board[i-1][j+1][0] == 'w')|| (temp->Board[i-1][j+1][0] == 'W'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))
                            if(temp->Board[i-2][j+2][0]== ' ')
                                regEatMove(list,i,j,i-1,j+1,i-2,j+2);


            }


        }
    }



}


void normalMovement(gBoard *temp, movement *list, int move){
    int i;
    /*board[dest] = board[origin]*/
    for(i=0; i<3;i++){
        temp->Board[list->normalMove[move][2]][list->normalMove[move][3]][i] = temp->Board[list->normalMove[move][0]][list->normalMove[move][1]][i];
        
        temp->Board[list->normalMove[move][0]][list->normalMove[move][1]][i] = ' ';
    }
    /*if board[dest] = bordo then make promo*/
    if(list->normalMove[move][2] == 6 && temp->Board[list->normalMove[move][2]][list->normalMove[move][3]] [0] == 'w')
        temp->Board[list->normalMove[move][2]][list->normalMove[move][3]] [0] = 'W';
    if(list->normalMove[move][2] == 0 && temp->Board[list->normalMove[move][2]][list->normalMove[move][3]][0] == 'b')
        temp->Board[list->normalMove[move][2]][list->normalMove[move][3]][0] = 'B';



}
void eatMovement(gBoard *temp, movement *list, int move){

    int i;
    /*board[dest] = board[origin]*/
    for(i=0; i<3;i++){
        temp->Board[list->eatMove[move][4]]      [list->eatMove[move][5]]    [i] =  temp->Board[list->eatMove[move][0]][list->eatMove[move][1]][i];
        temp->Board[list->eatMove[move][0]][list->eatMove[move][1]][i] = ' ';
    }
    /*adding the eaten part to the buttom*/
    if(temp->Board[list->eatMove[move][4]][list->eatMove[move][5]][1] == ' '){
        temp->Board[list->eatMove[move][4]][list->eatMove[move][5]][1] = temp->Board[list->eatMove[move][2]][list->eatMove[move][3]][0];
    }
    else{
        if(temp->Board[list->eatMove[move][4]][list->eatMove[move][5]][2] == ' '){
            temp->Board[list->eatMove[move][4]][list->eatMove[move][5]][2] = temp->Board[list->eatMove[move][2]][list->eatMove[move][3]][0];
        }
    }

    /*the eaten piece goes up and add a ' ' at bottom*/
    temp->Board[list->eatMove[move][2]][list->eatMove[move][3]][0] = temp->Board[list->eatMove[move][2]][list->eatMove[move][3]][1];
    temp->Board[list->eatMove[move][2]][list->eatMove[move][3]][1] = temp->Board[list->eatMove[move][2]][list->eatMove[move][3]][2];
    temp->Board[list->eatMove[move][2]][list->eatMove[move][3]][2] = ' ';

    /*promotion if at border*/
    if(list->eatMove[move][4] == 6 && temp->Board[list->eatMove[move][4]][list->eatMove[move][5]][0] == 'w')
        temp->Board[list->eatMove[move][4]][list->eatMove[move][5]][0] = 'W';
    if(list->eatMove[move][4] == 0 && temp->Board[list->eatMove[move][4]][list->eatMove[move][5]][0] == 'b')
        temp->Board[list->eatMove[move][4]][list->eatMove[move][5]][0] = 'B';

}
