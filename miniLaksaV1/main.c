#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"
#include "board.h"
#include "move.h"
#include "participants.h"



int main(int argc, char const *argv[])
{
    int depthS =4, depthE=4;
    int choice;
    int tests, side;
    bool exit = false;


    while(exit == false){   /*main menu*/
        printf("\nWelcome to miniLaska \n");
        printf("Menu:\n1.Play Game\n2.Test CPU vs CPU\n3.Setting depth CPU\n4.Exit\nYour choice:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            gameManager(depthS,depthE);
            break;
        case 2:
            testCpu(depthS, depthE);
            break;
        case 3:
            
            printf("\nCurrent depth of the cpus are: CpuScan:%d CpuEat: %d\n", depthS, depthE);
            
            printf("CpuScan new value: ");
            scanf("%d",&depthS);
            printf("\nCpuEat new value ");
            scanf("%d", &depthE);

            if(depthE <1 || depthS<1){
                printf("\n Value not valid, all the depth have been changed to default.");
                depthS = 4;
                depthE = 4;
            }

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


void gameControl(gBoard *pgame, int depthS, int depthE, int first, int second){

    int count = 0;
    while (getWinner(pgame) == 'n' && count < 100)
    {
        showBoard(pgame);
        switch (first)  /*white side*/
        {
        case 1:
            playerMove(pgame);
            break;
        case 2:
            cpuMoveRandom(pgame);
            break;
        case 3:
            cpuScan(pgame,depthS);
            break;
        case 4:
            cpuEat(pgame,depthE);
            break;
        default:
            printf("Error GameManagerSwitch");
            exit(4);
            break;
        }
        count++;
        if(getWinner(pgame) == 'n' && count<100){       /*black side*/
            showBoard(pgame);
            switch (second)
            {
            case 1:
                playerMove(pgame);
                break;
            case 2:
                cpuMoveRandom(pgame);
                break;
            case 3:
                cpuScan(pgame,depthS);
                break;
            case 4:
                cpuEat(pgame,depthE);
                break;
            default:
                printf("Error GameManagerSwitch");
                exit(4);
                break;
            }
            count++;
        }
    }
    if(count == 100 && getWinner(pgame) == 'n')
        drawGame(pgame);
}

void gameManager(int depthS, int depthE){
    gBoard game;
    gBoard *pgame;
    int choice, side, count;
    count = 0;
    pgame = &game;
    createBoard(pgame);
    initBoard(pgame);
    initPlayers(pgame);
    printf("Who you want to play against?\n");
    printf("1. Player vs Player\n2. Player vs Random\n3. Player vs CPU Scan \n4. Player vs CPU Eat \n5. Exit\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:     /*player vs player*/
        gameControl(pgame,depthS,depthE,1,1);
    break;

    case 2:     /*player vs cpu rand*/
        printf("Which side you want to play?(1.White 2.Black)");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:     /*player is white*/
            gameControl(pgame,depthS,depthE,1,2);
            break;

        case 2:     /*player is black*/
            gameControl(pgame,depthS,depthE,2,1);
            break;
        default:
            printf("Unkown side.");
            break;
        }
    break;

    case 3:
        printf("Which side you want to play?(1.White 2.Black)"); /* player vs cpu scan*/
        scanf("%d",&choice);
        switch (choice){
            case 1: /*player is white*/
                gameControl(pgame,depthS,depthE,1,3);
                break;

            case 2: /*player is black*/
                gameControl(pgame,depthS,depthE,3,1);
                break;

            default:
                printf("Unkown side.");
                break;
        }
    break;

    case 4:
        printf("Which side you want to play?(1.White 2.Black)"); /* player vs cpu eat*/
        scanf("%d",&choice);
        switch (choice){
            case 1: /*player is white*/
                gameControl(pgame,depthS,depthE,1,4);
                break;

            case 2: /*player is black*/
                gameControl(pgame,depthS,depthE,4,1);
                break;

            default:
                printf("Unkown side.");
                break;
        }
    break;

    case 5:
        destroyBoard(pgame);
        return;
    break;
    default:
        printf("Invalid input");
    break;
    }
    if(getWinner(pgame) == 'd')
        printf("\nDraw Game");
    else if(getWinner(pgame) == 'w')
        printf("\nWinner is White");
    else if(getWinner(pgame) == 'b')
        printf("\nWinner is Black");

    destroyBoard(pgame);
    /*free*/
}

void testManager(int tests, int first, int second, int depthS, int depthE, int *countFirst, int *countSecond, int *countDraw){
    gBoard test;
    gBoard *pTest;
    int i;

    pTest = &test;
    createBoard(pTest);
    initBoard(pTest);
    initPlayers(pTest);

    for(i = 0; i < tests; i++){     /*executes num of test*/
        initBoard(pTest);
        initPlayers(pTest);
        gameControl(pTest,depthS,depthE,first,second);

        if(getWinner(pTest) == 'd')     /*saves resault*/
            *countDraw = *countDraw + 1;
        else if(getWinner(pTest) == 'w')
            *countFirst = *countFirst +1;
        else if (getWinner(pTest) == 'b')
            *countSecond = *countSecond +1;
    }

    destroyBoard(pTest);
}

void testCpu(int depthS, int depthE){
    int countFirst =0, countSecond=0, countDraw=0;
    int i,j,tests, choice;
    int first,second;

    printf("\nHow many tests you want to perform: ");
    scanf("%d", &tests);
    
    printf("\nDo you want to perform single type of test or full test(1 or 2) ");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case 1:     /*single type test between one entity vs another*/
        printf("\nWho is gonna play White \n1.Random \n2.CpuScan \n3.CpuEat\n");
        scanf("%d", &first);
        first++;

        printf("\nWho is gonna play Black \n1.Random \n2.CpuScan \n3.CpuEat\n");
        scanf("%d", &second);
        second++;

        testManager(tests,first,second,depthS,depthE,&countFirst,&countSecond,&countDraw);

        printf("Result of test:\n White wins: %d \n Black wins: %d \n Draws: %d",countFirst,countSecond,countDraw);

        break;
    case 2: /*full type, test between all entitys*/
        {

            int arrCountFirst[9] = {0,0,0,0,0,0,0,0,0}, arrCountSecond[9] = {0,0,0,0,0,0,0,0,0}, arrCountDraw[9] = {0,0,0,0,0,0,0,0,0};
            


            for(i=0;i<9;i++){
                if(i<3)
                    first = 1;
                else if(i<6)
                    first = 2;
                else if(i<9)
                    first = 3;

                if(i==0 || i==3 || i==6)
                    second = 1;
                else if(i==1 || i==4 || i==7)
                    second = 2;
                else if(i == 2 || i==5 || i==8)
                    second = 3;

                

                testManager(tests,first+1,second+1,depthS,depthE,&arrCountFirst[i],&arrCountSecond[i],&arrCountDraw[i]);

            
            }

            for(i=0;i<9;i++){
                if(i<3)
                    printf("\nRandom ");
                else if(i<6)
                    printf("\nCpuScan");
                else if(i<9)
                    printf("\nCpuEat");
                
                printf(" white side: %d wins.", arrCountFirst[i]);


                if(i==0 || i==3 || i==6)
                    printf("  Random");
                else if(i==1 || i==4 || i==7)
                    printf("  CpuScan");
                else if(i == 2 || i==5 || i==8)
                    printf("  CpuEat");

                printf(" black side: %d wins.",arrCountSecond[i]);

                printf("  Draws: %d", arrCountDraw[i]);
            }

        }
        printf("\nFine\n");
        break;
    default:
        printf("Wrong input");
        break;
    }

    return;

}
