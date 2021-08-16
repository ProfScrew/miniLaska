
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void createBoard(gBoard *temp){
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
void cleanBoard(gBoard *temp) {
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

void initBoard(gBoard *temp){

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
void initPlayers(gBoard *temp){
    int i=0, j=0;
    temp->winner = 'n';
    temp->turn = 'w';
    /*init white player */
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

