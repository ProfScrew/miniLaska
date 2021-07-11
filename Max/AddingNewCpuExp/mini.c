#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct availableMovement{
    int countEatMove;
    int countNormalMove;
    int **eatMove;
    int **normalMove;
}movement;
typedef struct gameBoard{
   char*** Board;
   char winner;
   char turn;
}gBoard;


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
void destroyBoard(gBoard *temp) {
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

void changeTurn(gBoard *temp){
    if(temp->turn == 'w')
        temp->turn = 'b';
    else
        temp->turn = 'w';
}
char getTurn(gBoard *temp){
    return temp->turn;
}
char getWinner(gBoard *temp){
    return temp->winner;
}
void selectWinner(gBoard *temp){
    if(temp->turn == 'w')
        temp->winner = 'b';
    else
        temp->winner = 'w';
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

void printNormMoves(movement *temp, float *move){
    int i;
    printf("cpu moves: \n");
    for(i=0;i<temp->countNormalMove;i++){
        printf("%d From: %d%c ", i+1, temp->normalMove[i][0]+1, temp->normalMove[i][1]+65);
        printf("To: %d%c ", temp->normalMove[i][2]+1, temp->normalMove[i][3]+65);
        if(move != NULL) 
            printf("Value: %f \n", move[i]);
    }
}
void printEatMoves(movement *temp, float *move){
    int i;
    
    printf("cpu eat moves:\n");
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

void randomchoise(movement *temp, float *move, bool type, int *choice){
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

void playerMove(gBoard *temp){
    int i, move;
    movement list;
    movement *plist;
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
        printf("eat moves:\n");
        for(i=0;i<plist->countEatMove; i++){
            printf("%d. From: %d%c ", i+1, plist->eatMove[i][0]+1, plist->eatMove[i][1]+65);
            printf("Eat: %d%c ", plist->eatMove[i][2]+1, plist->eatMove[i][3]+65);
            printf("To: %d%c\n", plist->eatMove[i][4]+1, plist->eatMove[i][5]+65);
        }
        printf("Enter Move: ");
        if(scanf("%d", &move ) < 0){
            printf("\n Error move");
            return;
        }else if(move > list.countEatMove){
            printf("\n Error move");
            return;
        }
        eatMovement(temp, plist, move-1);


    }else{
        printf("moves:\n");
        for(i=0;i<plist->countNormalMove; i++){
            printf("%d. From: %d%c ",i+1, plist->normalMove[i][0]+1, plist->normalMove[i][1]+65);
            printf("To: %d%c\n", plist->normalMove[i][2]+1, plist->normalMove[i][3]+65);

        }
        printf("Enter Move: ");
        if(scanf("%d", &move ) < 0){
            printf("\n Error move");
            return;
        }else if(move > list.countNormalMove){
            printf("\n Error move");
            return;
        }
        normalMovement(temp,plist,move-1);
    }

    if(temp->turn == 'w')
        temp->turn = 'b';
    else
        temp->turn = 'w';
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
        printf("cpu moves:\n");
        move = rand() % plist->countNormalMove;
        printf("From: %d%c ", plist->normalMove[move][0]+1, plist->normalMove[move][1]+65);
        printf("To: %d%c\n", plist->normalMove[move][2]+1, plist->normalMove[move][3]+65);
        normalMovement(temp,plist,move);
    }

    if(temp->turn == 'w')
        temp->turn = 'b';
    else
        temp->turn = 'w';
    destroyMove(plist);
    
    

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
float cpuRecFunc(int depth, gBoard *original, float *numberOfOutcomes, char side){
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
            temp += cpuRecFunc(depth-1,pdummy,numberOfOutcomes,side);
            
        }
        destroyMove(plist);
        destroyBoard(original);
        return temp;

    }
    if(plist->countEatMove == 1){
        eatMovement(original,plist,0);
        destroyMove(plist);
        changeTurn(original);
        return cpuRecFunc(depth-1, original, numberOfOutcomes, side);
    }
    if(plist->countNormalMove>1){
        float temp=0;
        for(i = 0; i< plist->countNormalMove; i++){
            createBoard(pdummy);
            copyBoard(pdummy,original);
            normalMovement(pdummy, plist,i);
            changeTurn(pdummy);
            temp += cpuRecFunc(depth-1,pdummy, numberOfOutcomes, side);
            
        }
        destroyMove(plist);
        destroyBoard(original);
        return temp;
    }
    if(plist->countNormalMove == 1){
        normalMovement(original,plist,0);
        destroyMove(plist);
        changeTurn(original);
        return cpuRecFunc(depth-1, original, numberOfOutcomes, side);
    }
    
    return 0;
}
void cpuSmart(gBoard *temp, int depth){
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
    if(plist->countEatMove == 1){
        eatMovement(temp,plist,0);
        printEatMoves(plist,NULL);

    }
    if(plist->countEatMove == 0 && plist->countNormalMove == 1){
        normalMovement(temp,plist,0);
        printNormMoves(plist,NULL);
    }
    if(plist->countEatMove > 1){
        move = malloc(plist->countEatMove * sizeof(float));
        for(i=0; i<plist->countEatMove; i++){
            createBoard(pdummy);
            copyBoard(pdummy, temp);
            eatMovement(pdummy,plist,i);
            move[i] = cpuRecFunc(depth,pdummy, pOut,temp->turn);
            move[i] =  (move[i] /outcomes);
            outcomes = 0;
        }
        for(i = 0; i<plist->countEatMove;i++){
            if(move[choice]<move[i])
                choice = i;
        }
        printEatMoves(plist,move);

        randomchoise(plist,move,true,&choice);

        printf("\nFinal choice: %d\n", choice+1);
        eatMovement(temp, plist, choice);
    }
    else if(plist->countNormalMove > 1){
        move = malloc(plist->countNormalMove * sizeof(float));
        for(i=0; i<plist->countNormalMove; i++){
            createBoard(pdummy);
            copyBoard(pdummy, temp);
            normalMovement(pdummy,plist,i);
            move[i] = cpuRecFunc(depth,pdummy, pOut,temp->turn);
            
            move[i] =  (move[i] /outcomes);
            outcomes = 0;
            
        }
        for(i = 0; i< plist->countNormalMove;i++){
            if(move[choice]<move[i])
                choice = i;
        }

        printNormMoves(plist,move);
        randomchoise(plist,move,false,&choice);

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
    int i, j;
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
    if(plist->countEatMove == 1){
        eatMovement(temp,plist,0);
        printf("cpu eat move:\n");
        printf("From: %d%c ", plist->eatMove[0][0]+1, plist->eatMove[0][1]+65);
        printf("Eat: %d%c ", plist->eatMove[0][2]+1, plist->eatMove[0][3]+65);
        printf("To: %d%c\n", plist->eatMove[0][4]+1, plist->eatMove[0][5]+65);
        

    }
    if(plist->countEatMove == 0 && plist->countNormalMove == 1){
        normalMovement(temp,plist,0);

        printf("cpu move:\n");
        printf("From: %d%c ", plist->normalMove[0][0]+1, plist->normalMove[0][1]+65);
        printf("To: %d%c\n", plist->normalMove[0][2]+1, plist->normalMove[0][3]+65);
    }

    if(plist->countEatMove > 1){
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
        randomchoise(plist,move,true,&choice);
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
        randomchoise(plist,move,false,&choice);
        printf("\nFinal choice: %d \n", choice+1);
        normalMovement(temp,plist,choice);
    }
    if(move != NULL)
        free(move);
    destroyMove(plist);
    changeTurn(temp);

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

void gameManager(int depth){
    gBoard game;
    gBoard *pgame;
    int choice, side;

    pgame = &game;
    createBoard(pgame);
    initBoard(pgame);
    initPlayers(pgame);
    printf("Who you want to play against?\n");
    printf("1. Player vs Player\n2. Player vs CPU easy(random)\n3. Player vs CPU hard \n 5. Exit\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:     /*player vs player*/

        while (pgame->winner == 'n'){   
            showBoard(pgame);
            playerMove(pgame);
        }

    break;

    case 2:     /*player vs cpu rand*/

        printf("Which side you want to play?(1.White 2.Black)");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:     /*player is white*/
            while (pgame->winner == 'n'){
                showBoard(pgame);
                playerMove(pgame);
                if(pgame->winner == 'n'){
                    showBoard(pgame);
                    cpuMoveRandom(pgame);
                }
            }

            break;
        
        case 2:     /*player is black*/
            while (pgame->winner == 'n'){
                showBoard(pgame);
                cpuMoveRandom(pgame);
                if(pgame->winner == 'n'){
                    showBoard(pgame);
                    playerMove(pgame);
                    
                }
            }

            break;
        default:
            printf("Unkown side.");
            break;
        }

    break;

    case 3:
        printf("Which side you want to play?(1.White 2.Black)"); /* player vs cpu smart*/
        scanf("%d",&choice);
        switch (choice){
            case 1: /*player is white*/
                while (pgame->winner == 'n'){
                    showBoard(pgame);
                    playerMove(pgame);
                    if(pgame->winner == 'n'){
                        showBoard(pgame);
                        cpuSmart(pgame,depth);
                    }
                }
                

                break;

            case 2: /*player is black*/
                while (pgame->winner == 'n'){
                    showBoard(pgame);
                    cpuSmart(pgame,depth);
                    if(pgame->winner == 'n'){
                        showBoard(pgame);
                        playerMove(pgame);
                    }
                }

                break;

            default:
                printf("Unkown side.");
                break;

        }



    break;
    default:
        printf("Invalid input");
    break;
    }

    if(pgame->winner == 'w')
        printf("Winner is White");
    else if(pgame->winner == 'b')
        printf("Winner is Black");
    
    destroyBoard(pgame);
    /*free*/
}
void testTemp(){
    gBoard test;
    gBoard *pTest;
    pTest = &test;
    createBoard(pTest);

    initBoard(pTest);
    initPlayers(pTest);
    showBoard(pTest);

    destroyBoard(pTest);
}
void testCpu(int tests,int side,int depth){
    gBoard test;
    gBoard *pTest;
    int i, countSmart = 0, countRand = 0;

    pTest = &test;
    createBoard(pTest);

    initBoard(pTest);
    initPlayers(pTest);
    showBoard(pTest);
    if(side == 0){
        for ( i = 0; i < tests; i++){
            initBoard(pTest);
            initPlayers(pTest);
            while (pTest->winner == 'n')
            {   
                cpuEat(pTest, depth);
                showBoard(pTest);
                if(pTest->winner == 'n'){
                    cpuSmart(pTest,depth);
                    showBoard(pTest);
                }
            }
            if(pTest->winner == 'w')
                countSmart ++;
            else
                countRand ++;
            pTest->winner = 'n';
        }
    }
    else{
        for(i = 0; i< tests; i++){
            initBoard(pTest);
            initPlayers(pTest);
            while (pTest->winner == 'n')
            {
                cpuSmart(pTest,depth);
                showBoard(pTest);
                
                if(pTest->winner == 'n'){
                    
                    cpuEat(pTest, depth);
                    showBoard(pTest);
                }
                
            }
            if(pTest->winner == 'b')
                countSmart ++;
            else
                countRand ++;
            pTest->winner = 'n';
        }
    }
    destroyBoard(pTest);
    printf("Result of test:\nCpu Smart:%d\nCpu Random:%d\n", countSmart,countRand);
    
}

int main(int argc, char const *argv[]) {
    
    
    int depth = 6;
    int choice;
    int tests, side;
    bool exit = false;
    
    
    while(exit == false){
        printf("\nWelcome to miniLaska \n");
        printf("Menu:\n1.Play Game\n2.Test CPU(Random vs Smart)\n3.Setting depth CPU(default 6)\n4.Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            gameManager(depth);
            break;
        case 2:
            printf("\nHow many tests do you want? (ex. 10 test in 20 sec, 100 test in 2 min, 1000 test in 5 min)");
            scanf("%d", &tests);
            printf("\nWhich side SmartCpu(0 = white, 1 = black)");
            scanf("%d", &side);
            testCpu(tests, side, depth);
            break;
        case 3:
            printf("What depth you want(3 fast, 6 normal, 8 slow or costume):");
            scanf("%d", &depth);
            break;
        case 4:
            exit = true;
            break;

        default:
            printf("\nThis option does not exist, try entering again.\n");
            break;
        }
    }



    return 0;
}
