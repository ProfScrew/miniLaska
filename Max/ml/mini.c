#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "board.h"
#include "move.h"


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
long cpuRecFunc(int depth, gBoard *original, long *numberOfOutcomes, char side){
    gBoard dummy;
    gBoard *pdummy;

    movement list;
    movement *plist;
    int i;
    pdummy = &dummy;
    plist = &list;
    initMovement(plist);
    if(original->turn == 'w')
        checkWhite(original, plist);
    else if(original->turn == 'b')
        checkBlack(original, plist);

    if(plist->countEatMove == 0 && plist->countNormalMove == 0){
        *numberOfOutcomes += 1;
        freeMove(plist);
        cleanBoard(original);
        if(side == original->turn)
            return -100;
        else
            return +100;
    }
    if(depth == 0){
        
        float temp = valueOfBoard(original,side);
        *numberOfOutcomes +=1;
        cleanBoard(original);
        freeMove(plist);
        return temp;
    }
    if(plist->countNormalMove>1){
        float temp=0;
        for(i = 0; i< plist->countNormalMove; i++){
            createBoard(pdummy);
            copyBoard(pdummy,original);
            normalMovement(pdummy, plist,i);
            if(pdummy->turn = 'w')
                pdummy->turn = 'b';
            else
                pdummy->turn = 'w';
            temp += cpuRecFunc(depth-1,pdummy, numberOfOutcomes, side);
            
        }
        freeMove(plist);
        cleanBoard(original);
        return temp;
    }
    if(plist->countEatMove>1){
        float temp = 0;
        for(i = 0; i< plist->countEatMove; i++){
            createBoard(pdummy);
            copyBoard(pdummy,original);
            eatMovement(pdummy,plist,i);
            if(pdummy->turn = 'w')
                pdummy->turn = 'b';
            else
                pdummy->turn = 'w';
            temp += cpuRecFunc(depth-1,pdummy,numberOfOutcomes,side);
            
        }
        freeMove(plist);
        cleanBoard(original);
        return temp;

    }
    if(plist->countEatMove == 1){
        eatMovement(original,plist,0);
        freeMove(plist);
        if(pdummy->turn = 'w')
            pdummy->turn = 'b';
        else
            pdummy->turn = 'w';
        return cpuRecFunc(depth-1, original, numberOfOutcomes, side);
    }
    
    if(plist->countNormalMove == 1){
        normalMovement(original,plist,0);
        freeMove(plist);
        if(pdummy->turn = 'w')
            pdummy->turn = 'b';
        else
            pdummy->turn = 'w';
        return cpuRecFunc(depth-1, original, numberOfOutcomes, side);
    }
    
    return 0;
}
void cpuSmart(gBoard *temp, int depth){
    float *move;
    bool check = false;
    int i, choice = 0;
    movement list;
    movement *plist;
    gBoard dummy;
    gBoard *pdummy;
    char arr[2] = {'w', 'b'};
    long outcomes = 0;
    long *pOut;
    pOut = &outcomes;
    pdummy = &dummy;
    plist = &list;

    initMovement(plist);
    if(temp->turn== 'w'){
        checkWhite(temp,plist);
        i=1;
        printf("\nWhite ");
    }
    else if(temp->turn == 'b'){
        checkBlack(temp,plist);
        i=0;
        printf("\nBlack ");
    }

    if(plist->countEatMove == 0 && plist->countNormalMove == 0){
        temp->winner = arr[i];
        check = true;
        printf("no moves Available.\n");
    }
    if(plist->countEatMove == 1){
        eatMovement(temp,plist,0);
        temp->turn = arr[i];
        check = true;
        printf("cpu eat move:\n");
        printf("From: %d%c ", plist->eatMove[0][0]+1, plist->eatMove[0][1]+65);
        printf("Eat: %d%c ", plist->eatMove[0][2]+1, plist->eatMove[0][3]+65);
        printf("To: %d%c\n", plist->eatMove[0][4]+1, plist->eatMove[0][5]+65);
        

    }
    if(plist->countEatMove == 0 && plist->countNormalMove == 1){
        normalMovement(temp,plist,0);
        temp->turn = arr[i];
        check = true;

        printf("cpu move:\n");
        printf("From: %d%c ", plist->normalMove[0][0]+1, plist->normalMove[0][1]+65);
        printf("To: %d%c\n", plist->normalMove[0][2]+1, plist->normalMove[0][3]+65);
    }
    if(check){
        freeMove(plist);
        return;
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
        printf("cpu eat moves:\n");
        for(i = 0; i<plist->countEatMove;i++){
            if(move[choice]<move[i])
                choice = i;
            
            
            printf("From: %d%c ", plist->eatMove[i][0]+1, plist->eatMove[i][1]+65);
            printf("Eat: %d%c ", plist->eatMove[i][2]+1, plist->eatMove[i][3]+65);
            printf("To: %d%c ", plist->eatMove[i][4]+1, plist->eatMove[i][5]+65);
            printf("Value: %f \n", move[i]);
        }
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
        printf("cpu moves:\n");
        for(i = 0; i< plist->countNormalMove;i++){
            if(move[choice]<move[i])
                choice = i;
                

                printf("%d From: %d%c ", i+1, plist->normalMove[i][0]+1, plist->normalMove[i][1]+65);
                printf("To: %d%c ", plist->normalMove[i][2]+1, plist->normalMove[i][3]+65);
                
                printf("Value: %f \n", move[i]);
        }
        printf("\nFinal choice: %d\n", choice+1);
        normalMovement(temp, plist, choice);
    }
    free(move);
    freeMove(plist);
    
    if(temp->turn == 'w')
        temp->turn = 'b';
    else 
        temp->turn = 'w';


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
    
    cleanBoard(pgame);
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

    cleanBoard(pTest);
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
                cpuSmart(pTest, depth);
                showBoard(pTest);
                if(pTest->winner == 'n'){
                    cpuMoveRandom(pTest);
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
                cpuMoveRandom(pTest);
                showBoard(pTest);
                
                if(pTest->winner == 'n'){
                    
                    cpuSmart(pTest, depth);
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
    cleanBoard(pTest);
    printf("Result of test:\nCpu Smart:%d\nCpu Random:%d\n", countSmart,countRand);
    
}

int main(int argc, char const *argv[]) {
    int depth = 5;
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



    /*
    
    */





    return 0;
}
