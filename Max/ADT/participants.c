#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include"participants.h"
#include"board.h"
#include"move.h"

void playerMove(gBoard *temp){
    int i, move;
    movement list;
    movement *plist;
    plist = &list;
    createMove(plist);

    if(temp->turn == 'w'){
        list = checkWhite(temp);
        if(plist->countEatMove==0 && plist->countNormalMove==0){
            temp->winner = 'b';
            destroyMove(plist);
            return;
        }
        printf("\nWhite ");
    }else if (temp->turn == 'b'){
        list = checkBlack(temp);
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
        eatMovement(temp,plist->eatMove[move-1][0],plist->eatMove[move-1][1],plist->eatMove[move-1][2],plist->eatMove[move-1][3],plist->eatMove[move-1][4],plist->eatMove[move-1][5]);


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
        normalMovement(temp,plist->normalMove[move-1][0],plist->normalMove[move-1][1],plist->normalMove[move-1][2],plist->normalMove[move-1][3]);
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
        list = checkWhite(temp);
        if(plist->countEatMove==0 && plist->countNormalMove==0){
            temp->winner = 'b';
            destroyMove(plist);
            return;
        }
        printf("\nWhite ");
    }else if (temp->turn == 'b'){
       list = checkBlack(temp);
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
        
        eatMovement(temp,plist->eatMove[move][0],plist->eatMove[move][1],plist->eatMove[move][2],plist->eatMove[move][3],plist->eatMove[move][4],plist->eatMove[move][5]);

    }else{
        printf("cpu moves:\n");
        move = rand() % plist->countNormalMove;
        printf("From: %d%c ", plist->normalMove[move][0]+1, plist->normalMove[move][1]+65);
        printf("To: %d%c\n", plist->normalMove[move][2]+1, plist->normalMove[move][3]+65);
        normalMovement(temp,plist->normalMove[move][0],plist->normalMove[move][1],plist->normalMove[move][2],plist->normalMove[move][3]);
    }

    if(temp->turn == 'w')
        temp->turn = 'b';
    else
        temp->turn = 'w';
    destroyMove(plist);
    
    

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
    if(original->turn == 'w')
        list = checkWhite(original);
    else if(original->turn == 'b')
        list = checkBlack(original, plist);

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
        destroyMove(plist);
        destroyBoard(original);
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
        destroyMove(plist);
        destroyBoard(original);
        return temp;

    }
    if(plist->countEatMove == 1){
        eatMovement(original,plist,0);
        destroyMove(plist);
        if(pdummy->turn = 'w')
            pdummy->turn = 'b';
        else
            pdummy->turn = 'w';
        return cpuRecFunc(depth-1, original, numberOfOutcomes, side);
    }
    
    if(plist->countNormalMove == 1){
        normalMovement(original,plist,0);
        destroyMove(plist);
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
    float outcomes = 0;
    float *pOut;
    pOut = &outcomes;
    pdummy = &dummy;
    plist = &list;

    createMove(plist);
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
        destroyMove(plist);
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
    destroyMove(plist);
    
    if(temp->turn == 'w')
        temp->turn = 'b';
    else 
        temp->turn = 'w';


}

