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

void playerMove(gBoard *temp){
    int i, move;
    movement list;
    movement *plist;
    plist = &list;
    initMovement(plist);

    if(temp->turn == 'w'){
        checkWhite(temp,plist);
        if(plist->countEatMove==0 && plist->countNormalMove==0){
            temp->winner = 'b';
            freeMove(plist);
            return;
        }
        printf("\nWhite ");
    }else if (temp->turn == 'b'){
        checkBlack(temp, plist);
        if(plist->countEatMove==0 && plist->countNormalMove==0){
            temp->winner = 'w';
            freeMove(plist);
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
    freeMove(plist);
}
void cpuMoveRandom(gBoard *temp){
    int i, move;
    movement list;
    movement *plist;
    time_t t;
    srand((unsigned) time(&t));
    plist = &list;
    initMovement(plist);

    if(temp->turn == 'w'){
        checkWhite(temp,plist);
        if(plist->countEatMove==0 && plist->countNormalMove==0){
            temp->winner = 'b';
            freeMove(plist);
            return;
        }
        printf("\nWhite ");
    }else if (temp->turn == 'b'){
        checkBlack(temp, plist);
        if(plist->countEatMove==0 && plist->countNormalMove==0){
            temp->winner = 'w';
            freeMove(plist);
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
    freeMove(plist);
    
    

}
int valueOfBoard(gBoard *temp){
    
}
int cpuRecFunc(int depth, gBoard *original, long *numberOfOutcomes, char side){
    gBoard dummy;
    gBoard *pdummy = NULL;

    movement list;
    movement *plist;
    int i;

    plist = &list;
    initMovement(plist);
    if(original->turn == 'w')
        checkWhite(original, plist);
    else if(original->turn == 'b')
        checkBlack(original, plist);

    if(plist->countEatMove == 0 && plist->countNormalMove == 0){
        numberOfOutcomes += 1;
        freeMove(plist);
        if(side == original->turn)
            return -1000;
        else
            return +1000;
    }
    if(plist->countEatMove == 1){
        if(depth == 0){
            int temp;
            eatMovement(original, plist, 0);
            temp = valueOfBoard(original);
            cleanBoard(original);
            numberOfOutcomes += 1;
            freeMove(plist);
            return temp;
        }else{
            eatMovement(original,plist,0);
            freeMove(plist);
            return cpuRecFunc(depth-1, original, numberOfOutcomes, side);
        }
    }
    if(plist->countEatMove > 1){
        int temp;
        for(i = 0; i<plist->countEatMove; i++){
            initBoard(pdummy);
            copyBoard(pdummy, original);
            temp = cpuRecFunc(depth)
        }
    }
    if(plist->countNormalMove == 1){
        if(depth == 0){
            int temp;
            eatMovement(original,plist,0);
            temp = valueOfBoard(original);
            cleanBoard(original);
            numberOfOutcomes += 1;
            freeMove(plist);
            return temp;
        }else{
            normalMovement(original,plist,0);
            freeMove(plist);
            return cpuRecFunc(depth-1, original, numberOfOutcomes, side);
        }
    }
    
    

    


    return 0;
}
void cpuSmart(gBoard *temp, int depth){
    int *move;
    bool check = false;
    int i, move;
    movement list;
    movement *plist;
    gBoard dummy;
    gBoard *pdummy;
    char arr[2] = {'w', 'b'};

    pdummy = &dummy;
    plist = &list;

    initMovement(plist);
    if(temp->turn== 'w'){
        checkWhite(temp,plist);
        i=1;
    }
    else if(temp->turn == 'b'){
        checkBlack(temp,plist);
        i=0;
    }

    if(plist->countEatMove == 0 && plist->countNormalMove == 0){
        temp->winner = arr[i];
        check = true;
    }
    if(plist->countEatMove == 1){
        eatMovement(temp,plist,0);
        temp->turn = arr[i];
        check = true;
    }
    if(plist->countEatMove == 0 && plist->countNormalMove == 1){
        normalMovement(temp,plist,0);
        temp->turn = arr[i];
        check = true;
    }
    if(check){
        freeMove(plist);
        return;
    }
    initBoard(pdummy);
    if(plist->countEatMove > 1){
        move = malloc(plist->countEatMove * sizeof(int));
        for(i=0; i<plist->countEatMove; i++){
            copyBoard(pdummy, temp);
            eatMovement(pdummy,plist,i);
            move[i] = cpuRecFunc();
        }
    }
    else if(plist->countNormalMove > 1){
        move = malloc(plist->countNormalMove * sizeof(int));
        for(i=0; i<plist->countNormalMove; i++){
            copyBoard(pdummy, temp);
            normalMovement(pdummy,plist,i);
            move[i] = cpuRecFunc();
        }
    }
    cleanBoard(pdummy);




    
    

    


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

void gameManager(){
    int choice, side;

    printf("Welcome to miniLaska\n");
    printf("Menu:\n1. Player vs Player\n2. Player vs CPU easy(random)\n3. Player vs CPU hard \n4. CPU vs CPU\n 5. Exit\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        printf("Which side you like to play? \n1.White \n2.Black \n");
        scanf("%d", &side);
            switch (side){
            case 1:
                printf("White");
            break;
            case 2:
                printf("Black");
            default:
                break;
            }

        break;

    default:
        printf("Invalid input");
        break;
    }
}

int main(int argc, char const *argv[]) {
    int choice = 0, side = 0;

    gBoard original;
    gBoard *t;

    movement list;
    movement *plist;
    plist = &list;



    t = &original;
    createBoard(t);
    initBoard(t);
    initPlayers(t);
    showBoard(t);
    
    

    
    while (t->winner == 'n')
    {   
        showBoard(t);
        cpuMoveRandom(t);
        
        
    }
    
    printf("\n WINNER %c\n", t->winner);
    cleanBoard(t);

    /*
    
    */





    return 0;
}