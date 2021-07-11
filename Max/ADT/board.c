
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "move.h"

void createBoard(gBoard *temp){ /*allocates memory for the board on heap*/
    int i=0, j=0, k;

    temp->winner = 'n';
    temp->turn = 'w';
    temp->Board = (char ***)malloc(7 * sizeof(char **));

    for(i=0; i < 7; i++){
        temp->Board[i] = (char **)malloc(7* sizeof(char*));
        for(j=0; j < 7; j++){
            temp->Board[i][j] = (char *)malloc(3 * sizeof(char));
        }
    }
}
void destroyBoard(gBoard *temp) {   /*frees board from memory*/
    int i=0, j=0, k=0;
    if(temp->Board != NULL){
        for(i=0; i<7;i++){
            for(j=0; j<7;j++){

                free(temp->Board[i][j]);
            }
            free(temp->Board[i]);
        }
        free(temp->Board);
    }
}
void initBoard(gBoard *temp){   /*fills empty spaces and '#' on unused squares*/

    int i,j,k;
    for(i=0; i<7; i++){
        for(j=0; j<7; j++){
            for(k=0; k<3; k++){
                if(i%2 == 0){
                    if(j%2 == 0){
                        temp->Board[i][j][k] = ' ';
                    }
                    else
                        temp->Board[i][j][k] = '#';

                }
                else{
                    if(j%2 == 0)
                        temp->Board[i][j][k] = '#';
                    else{
                        temp->Board[i][j][k] = ' ';
                    }
                }
            }
        }
    }
}
void initPlayers(gBoard *temp){ /*fill players*/
    int i=0, j=0;
    temp->winner = 'n';
    temp->turn = 'w';
    /*fill white player */
    for(i=0; i<3; i++){
        for(j=0; j<7; j++){
            if(i%2 == 0){
                if(j%2 == 0)
                    temp->Board[i][j][0] = 'w';
            }else{
                if(j%2 != 0)
                    temp->Board[i][j][0] = 'w';
            }
        }
    }
    /*fill black player*/
    for(i=4; i<7; i++){
        for(j=0; j<7; j++){
            if(i%2 == 0){
                if(j%2 == 0)
                    temp->Board[i][j][0] = 'b';
            }else{
                if(j%2 != 0)
                    temp->Board[i][j][0] = 'b';
            }
        }
    }
}
void copyBoard(gBoard *copy, gBoard *original){
    int i=0,j=0,k=0;
    if(copy->Board !=NULL || original->Board != NULL){
        copy->turn = original->turn;
        copy->winner = copy->winner;
        for(i=0;i<7;i++){
            for(j=0;j<7;j++){
                for(k=0;k<3;k++){
                    copy->Board[i][j][k] = original->Board[i][j][k];
                }
            }
        }
    }else{
    printf("Error Copy");
    }
}


void showBoardfirst(gBoard *temp){
    int i=0,j=0,k=0;
    if(temp->Board != NULL){
        for(i=0; i<7; i++){
            for(j=0; j<7; j++){
                    printf("%c", temp->Board[i][j][k]);
                }
                printf("\n");
            }
    }
}
void showBoard(gBoard *temp){
    int i, j, p;

    printf("   |");
    for(i=0; i<7; i++){
        printf(" %c ", (65 + i) );
    }
    printf("\n   |_____________________\n");

    for(i=0; i<7; i++){

        for (p=0; p<3; p++) {
            for(j=0; j<7;j++){
                if(j==0 && p ==1)
                    printf(" %d |", i+1);
                else if (j==0)
                printf("   |");

                if (temp->Board[i][j][0] == '#') {
                    printf("###");
                }else{
                    printf(" %c ", temp->Board[i][j][p]);
                }
            }
        printf("\n");
        }

    }
    printf("\n");

}


void readGame(gBoard *temp){ /* used for debug and testing board*/
    char buffer[1];
    int tempa = 0,tempb = 0,tempc = 0;
    char info = ' ';
    FILE *fp = fopen("testInfo.txt","r");
    if(fp == NULL){
        perror("Unable to open file!");
        exit(1);
    }
    
    while (tempa!= 9 && tempb!= 9 && tempc!= 9 && info != 'f'){   
        temp->Board[tempa][tempb][tempc] = info;
        
        fscanf(fp, "%d", &tempa);
        fscanf(fp, "%d", &tempb);
        fscanf(fp, "%d", &tempc);
        fscanf(fp, "%c", &info);
        
    }
    fclose(fp);
}


void normalMovement(gBoard *temp, int fromI, int fromJ, int toI, int toJ){
    int i;
    /*board[dest] = board[origin]*/
    for(i=0; i<3;i++){
        temp->Board[toI][toJ][i] = temp->Board[fromI][fromJ][i];
        
        temp->Board[fromI][fromJ][i] = ' ';
    }
    /*if board[dest] = bordo then make promo*/
    if(toI == 6 && temp->Board[toI][toJ][0] == 'w')
        temp->Board[toI][toJ] [0] = 'W';
    else if(toI == 0 && temp->Board[toI][toJ][0] == 'b')
        temp->Board[toI][toJ][0] = 'B';



}
void eatMovement(gBoard *temp, int fromI, int fromJ, int eatI, int eatJ, int toI, int toJ){

    int i;
    /*board[dest] = board[origin]*/
    for(i=0; i<3;i++){
        temp->Board[toI]      [toJ]    [i] =  temp->Board[fromI][fromJ][i];
        temp->Board[fromI][fromJ][i] = ' ';
    }
    /*adding the eaten part to the buttom*/
    if(temp->Board[toI][toJ][1] == ' '){
        temp->Board[toI][toJ][1] = temp->Board[eatI][eatJ][0];
    }
    else{
        if(temp->Board[toI][toJ][2] == ' '){
            temp->Board[toI][toJ][2] = temp->Board[eatI][eatJ][0];
        }
    }

    /*the eaten piece goes up and add a ' ' at bottom*/
    temp->Board[eatI][eatJ][0] = temp->Board[eatI][eatJ][1];
    temp->Board[eatI][eatJ][1] = temp->Board[eatI][eatJ][2];
    temp->Board[eatI][eatJ][2] = ' ';

    /*promotion if at border*/
    if(toI == 6 && temp->Board[toI][toJ][0] == 'w')
        temp->Board[toI][toJ][0] = 'W';
    if(toI == 0 && temp->Board[toI][toJ][0] == 'b')
        temp->Board[toI][toJ][0] = 'B';

}

movement checkWhite(gBoard *temp){
    int i, j;
    movement tlist;
    movement *list;

    list = &tlist;
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

    return tlist;
}

movement checkWhite(gBoard *temp){
    int i, j;
    movement tlist;
    movement *list;
    list = &tlist;
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
    return tlist;
}

float valueOfBoard(gBoard *temp,char side){
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

char getTurn(gBoard *temp){
    return temp->turn;
}
char getWinner(gBoard *temp){
    return temp->winner;
}