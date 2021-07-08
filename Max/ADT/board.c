
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


char getTurn(gBoard *temp){
    return temp->turn;
}
char getWinner(gBoard *temp){
    return temp->winner;
}