#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct availableMovement{
    int countEatMove;
    int countNormalMove;
    int **eatMove;
    int **normalMove;
}availableMovement;

typedef struct availableMovement* movement; 

typedef struct gameBoard{
   char*** Board;
   char winner;
   char turn;
}gameBoard;

typedef struct gameBoard* gBoard;

void initMovement(movement temp){

    temp->countEatMove = 0;
    temp->countNormalMove = 0;
    temp->eatMove = NULL;
    temp->normalMove = NULL;
}
void regNormalMove(movement temp, int fromI, int fromJ, int toI, int toJ){

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
void regEatMove(movement temp, int fromI, int fromJ,int eatI, int eatJ, int toI, int toJ){

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
void freeMove(movement temp){
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

void seeMove(movement temp){
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

void createBoard(gBoard temp){
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
void cleanBoard(gBoard temp) {
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
void initBoard(gBoard temp){

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
void initPlayers(gBoard temp){
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

void normalMovement(gBoard temp, movement list, int move){
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
void eatMovement(gBoard temp, movement list, int move){

    int i;
    /*board[dest] = board[origin]*/
    for(i=0; i<3;i++){
        temp->Board[list->eatMove[move][4]][list->eatMove[move][5]][i] =  temp->Board[list->eatMove[move][0]][list->eatMove[move][0]][i];
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

void checkWhite(gBoard temp, movement list){
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
void checkBlack(gBoard temp, movement list){
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
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ));/*check bottom right move*/
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

void playerMove(gBoard temp){
    int i, move;
    availableMovement list;
    movement plist;
    plist = &list;

    if(temp->turn = 'w'){
        checkWhite(temp,plist);
        if(plist->countEatMove==0 && plist->countNormalMove==0){
            temp->winner = 'b';
            freeMove(plist);
            return;
        }
        printf("\nWhite ");
    }else if (temp->turn = 'b'){
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
            printf("%d. From: %d%c ", i+1, plist->eatMove[i][0], plist->eatMove[i][1]+65);
            printf("Eat: %d%c ", plist->eatMove[i][2], plist->eatMove[i][3]+65);
            printf("To: %d%c\n", plist->eatMove[i][4], plist->eatMove[i][5]+65);
        }
        printf("Enter Move: ");
        scanf("%d", &move );
        eatMovement(temp, plist, move-1);


    }else{
        printf("moves:\n");
        for(i=0;i<plist->countNormalMove; i++){
            printf("%d. From: %d%c ",i+1, plist->normalMove[i][0], plist->normalMove[i][1]+65);
            printf("To: %d%c\n", plist->normalMove[i][2], plist->normalMove[i][3]+65);

        }
        printf("Enter Move: ");
        scanf("%d", &move );
        normalMovement(temp,plist,move-1);
    }

    if(temp->turn == 'w')
        temp->turn = 'b';
    else
        temp->turn = 'w';
    freeMove(plist);
}


void showBoardfirst(gBoard temp){
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
void showBoard(gBoard temp){
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

void copyBoard(gBoard copy, gBoard original){
    int i=0,j=0,k=0;
    if(copy->Board !=NULL || original->Board != NULL){
        for(i=0;i<7;i++){
            for(j=0;j<7;j++){
                for(k=0;k<3;k++){
                    copy->Board[i][j][k] = original->Board[i][j][k];
                }
            }
        }
    }
    printf("Error Copy");
}

void playerTest(gBoard temp){
    availableMovement list;
    movement plist;
    plist = &list;

    checkWhite(temp, plist);
}


void whiteMove(gBoard temp){
    int i=0, j=0;
    int countEatMove = 0;
    int countNormalMove = 0;

    int* eatMove = (int*) malloc (6 * (countEatMove + 1) * sizeof(int));
    int* normalMove = (int*) malloc(4  * (countNormalMove + 1) * sizeof(int));



    free(eatMove);
    free(normalMove);

}


int main(int argc, char const *argv[]) {
    int choice = 0, side = 0;

    gameBoard original;
    gBoard t;

    availableMovement list;
    movement plist;
    plist = &list;



    t = &original;
    createBoard(t);
    initBoard(t);
    initPlayers(t);
    showBoard(t);
    regEatMove(plist, 1,1,1,1,1,1);
    /*checkWhite(t, plist);*/
    seeMove(plist);
    /*playerMove(t);*/
    /*playerTest(t);*/
    showBoard(t);
    freeMove(plist);

    cleanBoard(t);

    /*
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
    */





    return 0;
}
