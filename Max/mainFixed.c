#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char winner = 'n';

void initBoard(char Board[7][7][3]){

  int i,j;
  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(i%2 == 0){
        if(j%2 == 0){
          Board [i] [j] [0] = ' ';
          Board [i] [j] [1] = ' ';
          Board [i] [j] [2] = ' ';
        }
        else
          Board [i] [j] [0]= '#';

      }
      else{
        if(j%2 == 0)
          Board [i] [j] [0]= '#';
        else{
          Board [i] [j] [0]= ' ';
          Board [i] [j] [1] = ' ';
          Board [i] [j] [2] = ' ';
        }
      }
    }
  }
}

void startPlayerOne(char Board[7][7][3]){
  int i, j;

  for(i=0; i<3; i++){
    for(j=0; j<7; j++){
      if(i%2 == 0){
        if(j%2 == 0)
          Board[i] [j] [0] = 'w';
      }else{
        if(j%2 != 0)
          Board[i] [j] [0] = 'w';
      }
    }
  }
}

void startPlayerTwo(char Board[7][7][3]){
  int i, j;

  for(i=4; i<7; i++){
    for(j=0; j<7; j++){
      if(i%2 == 0){
        if(j%2 == 0)
          Board[i] [j] [0] = 'b';
      }else{
        if(j%2 != 0)
          Board[i] [j] [0] = 'b';
      }
    }
  }
}


void normalMovement(int* normalMove, int choice, char Board [7][7][3]){
  int i;
  for(i=0; i<3;i++){
    Board[normalMove[2+ (4 * choice) - 4]][normalMove [3 + (4 * choice) -4]][i] = Board[normalMove[0+ (4 * choice) - 4]][normalMove [1 + (4 * choice) -4]][i];
    Board[normalMove[0+ (4 * choice) - 4]][normalMove [1 + (4 * choice) -4]][i] = ' ';
  }
  if(normalMove[2 + (4 * choice) - 4] == 6 && Board[normalMove[2+ (4 * choice) - 4]][normalMove [3 + (4 * choice) -4]][0] == 'w')
    Board[normalMove[2+ (4 * choice) - 4]][normalMove [3 + (4 * choice) -4]][0] = 'W';
  if(normalMove[2 + (4 * choice) - 4] == 0 && Board[normalMove[2+ (4 * choice) - 4]][normalMove [3 + (4 * choice) -4]][0] == 'b')
    Board[normalMove[2+ (4 * choice) - 4]][normalMove [3 + (4 * choice) -4]][0] = 'B';

}

void registerMoves( int i, int j, int a, int b, int** normalMove , int* countPunt){
    /*printf("a %d\n", *normalMove[0] );
  *normalMove[0 + (4 * (*countPunt)) -4] = i;
  printf("\nok \n");
  printf("%d\n", *normalMove[0] );
  /*printf("%d ", normalMove[0 + (4 * *countPunt) -4]  +1);
  *normalMove[1 + (4 * (*countPunt)) -4] = j;

  /*printf("%d ", normalMove[1 + (4 * *countPunt) -4] +1);
  *normalMove[2 + (4 * (*countPunt)) -4] = a;
  /*printf("%d ", normalMove[2 + (4 * *countPunt) -4] +1);
  *normalMove[3 + (4 * (*countPunt)) -4] = b;
  /*printf("%d ", normalMove[3 + (4 * *countPunt) -4] +1);

  *countPunt = (*countPunt) + 1;
  /*normalMove = (int*) realloc(normalMove, 4 *  (*countPunt) * sizeof(int));
  */

  *(*normalMove + 0 + (4 *(*countPunt)) - 4) = i;
  *(*normalMove + 1 + (4 *(*countPunt)) - 4) = j;
  *(*normalMove + 2 + (4 *(*countPunt)) - 4) = a;
  *(*normalMove + 3 + (4 *(*countPunt)) - 4) = b;

  *countPunt = (*countPunt) + 1;
}




void eatMovement(int* eatMove, int choice, char Board[7][7][3]){
  int i;
  for(i=0; i<3;i++){
    Board[eatMove[4 +(6* choice)-6]][eatMove[5 + (6 * choice)-6]][i] =  Board[eatMove[0 +(6* choice)-6]][eatMove[1 + (6 * choice)-6]][i];
    Board[eatMove[0 +(6* choice)-6]][eatMove[1 + (6 * choice)-6]][i] = ' ';
  }
  if(Board[eatMove[4 +(6* choice)-6]][eatMove[5 + (6 * choice)-6]][1] == ' '){
    Board[eatMove[4 +(6* choice)-6]][eatMove[5 + (6 * choice)-6]][1] = Board[eatMove[2 +(6* choice)-6]][eatMove[3 + (6 * choice)-6]][0];
  }
  else{
    if(Board[eatMove[4 +(6* choice)-6]][eatMove[5 + (6 * choice)-6]][2] == ' '){
      Board[eatMove[4 +(6* choice)-6]][eatMove[5 + (6 * choice)-6]][2] = Board[eatMove[2 +(6* choice)-6]][eatMove[3 + (6 * choice)-6]][0];
    }
  }
  Board[eatMove[2 +(6* choice)-6]][eatMove[3 + (6 * choice)-6]][0] = Board[eatMove[2 +(6* choice)-6]][eatMove[3 + (6 * choice)-6]][1];
  Board[eatMove[2 +(6* choice)-6]][eatMove[3 + (6 * choice)-6]][1] = Board[eatMove[2 +(6* choice)-6]][eatMove[3 + (6 * choice)-6]][2];
  Board[eatMove[2 +(6* choice)-6]][eatMove[3 + (6 * choice)-6]][2] = ' ';

  if(eatMove[4 +(6* choice)-6] == 6 && Board[eatMove[4 +(6* choice)-6]][eatMove[5 + (6 * choice)-6]][0] == 'w')
    Board[eatMove[4 +(6* choice)-6]][eatMove[5 + (6 * choice)-6]][0] = 'W';
  if(eatMove[4 +(6* choice)-6] == 0 && Board[eatMove[4 +(6* choice)-6]][eatMove[5 + (6 * choice)-6]][0] == 'b')
    Board[eatMove[4 +(6* choice)-6]][eatMove[5 + (6 * choice)-6]][0] = 'B';
}

void registerEatMove(int i, int j, int a, int b,int l,int m, int** eatMove , int* countPunt) {
  /*
  *eatMove[0 + (6 * *countPunt) -6] = i;
  *eatMove[1 + (6 * *countPunt) -6] = j;
  *eatMove[2 + (6 * *countPunt) -6] = a;
  *eatMove[3 + (6 * *countPunt) -6] = b;
  *eatMove[4 + (6 * *countPunt) -6] = l;
  *eatMove[5 + (6 * *countPunt) -6] = m;
  printf("\n%d - %d - %d - %d - %d - %d -\n",i,j,a,b,l,m );
  printf("\n eat moves \n");
  for(int d = 0; d<6;d++ ){
    printf("%d\n", *eatMove[d + (6 * *countPunt) -6]);
  }

  *countPunt = *countPunt + 1;
  printf("\ncount punt eat%d\n", *countPunt);
*/
  *(*eatMove + 0 + (6 * (*countPunt)) -6) = i;
  *(*eatMove + 1 + (6 * (*countPunt)) -6) = j;
  *(*eatMove + 2 + (6 * (*countPunt)) -6) = a;
  *(*eatMove + 3 + (6 * (*countPunt)) -6) = b;
  *(*eatMove + 4 + (6 * (*countPunt)) -6) = l;
  *(*eatMove + 5 + (6 * (*countPunt)) -6) = m;

  *countPunt = (*countPunt) + 1;

}




void checkWhite(char Board[7][7][3], int* countEatMove, int* countNormMoves, int **eatMove , int **normalMove ){


  int i, j;
  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(Board[i][j][0] == 'w'){
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){
          /*can move bot left*/
          registerMoves(i, j, (i+1), (j-1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }
        if(Board[i+1][j+1][0]== ' ' &&  (((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){
          /*can move bot right*/
          registerMoves(i, j, (i+1), (j+1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }
        /*remember to put else */
        /**/

        if(((Board[i+1][j-1][0] == 'b')|| (Board[i+1][j-1][0] == 'B')) &&  (((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i+2][j-2][0]== ' ' &&  (((i+2) >= 0 && (i+2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))){
            /*can eat bottom left */
            registerEatMove(i,j,i+1,j-1,i+2,j-2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));
          }
        }
        if(((Board[i+1][j+1][0] == 'b')|| (Board[i+1][j+1][0] == 'B')) &&  (((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i+2][j+2][0]== ' ' &&  (((i+2) >= 0 && (i+2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))){
            /*can eat bottom right*/
            registerEatMove(i,j,i+1,j+1,i+2,j+2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));
          }
        }



      }
      if(Board[i][j][0] == 'W'){
        /*first part normal moves to blank spot */
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){        /*check bottom left*/

          registerMoves(i, j, (i+1), (j-1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }
        if(Board[i+1][j+1][0] == ' ' &&  (((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check bottom right*/
          ;
          registerMoves(i, j, (i+1), (j+1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }
        if(Board[i-1][j-1][0] == ' ' &&  (((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){  /*check top left*/

          registerMoves(i, j, (i-1), (j-1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }
        if(Board[i-1][j+1][0] == ' ' &&  (((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check top right*/

          registerMoves(i, j, (i-1), (j+1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }



        if(((Board[i+1][j-1][0] == 'b')|| (Board[i+1][j-1][0] == 'B')) &&  (((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i+2][j-2][0]== ' ' &&  (((i+2) >= 0 && (i+2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))){

            registerEatMove(i,j,i+1,j-1,i+2,j-2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));
          }
        }
        if(((Board[i+1][j+1][0] == 'b')|| (Board[i+1][j+1][0] == 'B')) &&  (((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i+2][j+2][0]== ' ' &&  (((i+2) >= 0 && (i+2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))){

            registerEatMove(i,j,i+1,j+1,i+2,j+2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));
          }
        }
        if(((Board[i-1][j-1][0] == 'b')|| (Board[i-1][j-1][0] == 'B')) &&  (((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){  /*check top left move */
          if(Board[i-2][j-2][0]== ' ' &&  (((i-2) >= 0 && (i-2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))){

            registerEatMove(i,j,i-1,j-1,i-2,j-2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));
          }
        }
        if(((Board[i-1][j+1][0] == 'b')|| (Board[i-1][j+1][0] == 'B')) &&  (((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check top left move */
          if(Board[i-2][j+2][0]== ' ' &&  (((i-2) >= 0 && (i-2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))){

            registerEatMove(i,j,i-1,j+1,i-2,j+2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));
          }
        }

      }


    }
  }

}
void WhiteMove(char Board[7][7][3]){
  int i, j;
  int move;

  int countEatMove = 1;
  int* eatMove = (int*) malloc (6 * countEatMove * sizeof(int));

  int countNormMoves = 1;
  int*  normalMove = (int*) malloc(4  * countNormMoves * sizeof(int));

  checkWhite(Board, &countEatMove, &countNormMoves, &eatMove, &normalMove);


  if(((countNormMoves - 1) == 0 )&& ((countEatMove - 1) == 0) ){  /*white player can't do any moves*/
    winner = 'b';
    return;
  }
  j=1;

  time_t t;
  srand((unsigned) time(&t));

  if(countEatMove != 1){
    /*you have to eat so choose what move*/
    printf("White eat moves: %d", countEatMove -1 );
    for(i=0; i<((countEatMove -1) * 6 ); i++){
      if(i%6==0){
        printf("\n");
        printf("%d Move from: ", i/6 +1);
      }
      if(i%2 == 0)
        printf("%d", eatMove[i] +1 );
      else
        printf("%c", 65 + eatMove[i]);
      if(i==1 || j == i){
        printf(" to: ");
        j=j+6;
      }

    }
    printf("\n\n");
    printf("Enter move number " );
    /*
    scanf("%d", &move );
    */
    move =  (rand() % (countEatMove-1))+1;
    printf("%d\n", move);

    eatMovement(eatMove, move ,Board);
  }else{
    /* you have to do normal move*/
    printf("White moves %d", countNormMoves -1 );
    for (i = 0; i < ((countNormMoves -1 ) * 4); i++) {
      if(i%4 == 0){
        printf("\n");
        printf("%d Move from: ", i/4 + 1);
      }

      if(i%2 == 0)
        printf("%d", normalMove[i] +1 );
      else
        printf("%c", 65 + normalMove[i]);
      if(i%2 != 0 && (i+1)%4 != 0)
        printf(" to: ");
    }
    printf("\n\n");
    printf("Enter move number " );

    move =  (rand() % (countNormMoves - 1))+1;
    printf("%d\n", move);
    /*
    scanf("%d", &move );
    */


    normalMovement(normalMove, move ,Board);

  }

  free(eatMove);
  free(normalMove);

}



void checkBlack(char Board[7][7][3], int* countEatMove, int* countNormMoves, int **eatMove, int **normalMove){
  int i, j;

  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(Board[i][j][0] == 'b'){
        if(Board[i-1][j-1][0] == ' ' &&  (((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){
          /*can top bot left*/
          registerMoves(i, j, (i-1), (j-1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  (*countNormMoves) * sizeof(int));
        }
        if(Board[i-1][j+1][0]== ' ' &&  (((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){
          /*can top bot right*/
          registerMoves(i, j, (i-1), (j+1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }
        /*remember to put else */
        /**/

        if(((Board[i-1][j-1][0] == 'w')|| (Board[i-1][j-1][0] == 'W')) &&  (((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i-2][j-2][0]== ' ' &&  (((i-2) >= 0 && (i-2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))){
            /*can eat bottom left */
            registerEatMove(i,j,i-1,j-1,i-2,j-2, eatMove, countEatMove);

            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));



          }
        }
        if(((Board[i-1][j+1][0] == 'w')|| (Board[i-1][j+1][0] == 'W')) &&  (((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i-2][j+2][0]== ' ' &&  (((i-2) >= 0 && (i-2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))){
            /*can eat bottom right*/
            registerEatMove(i,j,i-1,j+1,i-2,j+2, eatMove, countEatMove);
            
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));


          }
        }



      }
      if(Board[i][j][0] == 'B'){
        /*first part normal moves to blank spot */
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){        /*check bottom left*/

          registerMoves(i, j, (i+1), (j-1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }
        if(Board[i+1][j+1][0] == ' ' &&  (((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check bottom right*/

          registerMoves(i, j, (i+1), (j+1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }
        if(Board[i-1][j-1][0] == ' ' &&  (((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){  /*check top left*/

          registerMoves(i, j, (i-1), (j-1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }
        if(Board[i-1][j+1][0] == ' ' &&  (((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check top right*/

          registerMoves(i, j, (i-1), (j+1), normalMove, countNormMoves);
          *normalMove = (int*) realloc(*normalMove, 4 *  *countNormMoves * sizeof(int));
        }



        if(((Board[i+1][j-1][0] == 'w')|| (Board[i+1][j-1][0] == 'W')) &&  (((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i+2][j-2][0]== ' ' &&  (((i+2) >= 0 && (i+2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))){

            registerEatMove(i,j,i+1,j-1,i+2,j-2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));

            if(!eatMove)
              printf("error\n");

          }
        }
        if(((Board[i+1][j+1][0] == 'w')|| (Board[i+1][j+1][0] == 'W')) &&  (((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i+2][j+2][0]== ' ' &&  (((i+2) >= 0 && (i+2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))){

            registerEatMove(i,j,i+1,j+1,i+2,j+2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));

            if(!eatMove)
              printf("error\n");

          }
        }
        if(((Board[i-1][j-1][0] == 'w')|| (Board[i-1][j-1][0] == 'W')) &&  (((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))){  /*check top left move */
          if(Board[i-2][j-2][0]== ' ' &&  (((i-2) >= 0 && (i-2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))){

            registerEatMove(i,j,i-1,j-1,i-2,j-2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));

            if(!eatMove)
              printf("error\n");

          }
        }
        if(((Board[i-1][j+1][0] == 'w')|| (Board[i-1][j+1][0] == 'W')) &&  (((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))){  /*check top left move */
          if(Board[i-2][j+2][0]== ' ' &&  (((i-2) >= 0 && (i-2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))){

            registerEatMove(i,j,i-1,j+1,i-2,j+2, eatMove, countEatMove);
            *eatMove = (int*) realloc(*eatMove, 6 * *countEatMove * sizeof(int));

            if(!eatMove)
              printf("error\n");

          }
        }

      }


    }
  }


}

void BlackMove(char Board[7][7][3]){
  int i, j;
  int move;
  int countEatMove = 1;
  int* eatMove = (int*) malloc (6 * countEatMove * sizeof(int));

  int countNormMoves = 1;
  int*  normalMove = (int*) malloc(4  * countNormMoves * sizeof(int));

  checkBlack(Board, &countEatMove, &countNormMoves, &eatMove, &normalMove);


  if(((countNormMoves - 1) == 0 )&& ((countEatMove - 1) == 0) ){  /*white player can't do any moves*/
    winner = 'w';
    free(eatMove);
    free(normalMove);
    return;
  }
  printf("%d\n", countEatMove );

  j=1;
  if(countEatMove != 1){
    /*you have to eat so choose what move*/
    printf("Black eat moves: %d", countEatMove -1 );
    for(i=0; i<((countEatMove -1) * 6 ); i++){
      if(i%6==0){
        printf("\n");
        printf("%d Move from: ", i/6 +1);
      }
      if(i%2 == 0)
        printf("%d", eatMove[i] +1 );
      else
        printf("%c", 65 + eatMove[i]);
      if(i==1 || j == i){
        printf(" to: ");
        j=j+6;
      }

    }
    printf("\n\n");
    printf("Enter move number " );
    scanf("%d", &move );
    eatMovement(eatMove, move ,Board);
  }else{
    /* you have to do normal move*/
    printf("Black moves %d", countNormMoves -1 );
    for (i = 0; i < ((countNormMoves -1 ) * 4); i++) {
      if(i%4 == 0){
        printf("\n");
        printf("%d Move from: ", i/4 + 1);
      }

      if(i%2 == 0)
        printf("%d", normalMove[i] +1 );
      else
        printf("%c", 65 + normalMove[i]);
      if(i%2 != 0 && (i+1)%4 != 0)
        printf(" to: ");
    }
    printf("\n\n");
    printf("Enter move number " );
    scanf("%d", &move );
    normalMovement(normalMove, move ,Board);

  }

  free(eatMove);
  free(normalMove);


}


/* CPU*/
/*
void CPU(char Board[7][7][3]){
  int i, j, z;

  char BoardCPU[7][7][3];

  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      for(z=0; z<3; z++){
        BoardCPU [i][j][z] = Board [i][j][z];
      }
    }
  }

  0

}
*/


void showBoard(char Board[7][7][3]){
  int i,j;
  printf("   a b c d e f g\n");
  printf("  ===============\n");
  for(i=0; i<7; i++){
    printf("%d |", i+1);
    for(j=0; j<7; j++){
      printf("%c|",Board [i] [j] [0]);
    }
    printf("\n");
  }
  printf("  ===============\n");
}

void newshowBoard(char Board[7][7][3]){
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

        if (Board[i][j][0] == '#') {
          printf("###");
        }else{
          printf(" %c ", Board[i][j][p]);
        }
      }
      printf("\n");
    }

  }
  printf("\n");

}




int main(int argc, char const *argv[]) {
  char Board [7] [7] [3];

  char turn = 'w';
  initBoard(Board);
  /*showBoard(Board);*/
  startPlayerOne(Board);
  startPlayerTwo(Board);
  /*showBoard(Board);*/
  /*newshowBoard(Board);
  checkWhiteMove(Board);
  newshowBoard(Board);
  printf("\n________________\n");
  */
  /*checkBlackMove(Board);*/

  /*system("clear");*/

  /* while loop where each player has a to do a move */
  printf("Welcome to miniLaska\n");
  printf("Menu:\n1. Player vs Player\n2. Player vs CPU easy(random)\n3. Player vs CPU hard\n");
  /*input and then if to decide the chose */
  while(winner == 'n'){
    /*so we have two funcition that move  but before we need to make a funcition
      at the ending where the system checks if someone has won*/
      if(turn == 'w'){
        /*white turn functions*/
        printf("White move\n");
        /*check moves tha white can do and write them*/
        newshowBoard(Board);
        WhiteMove(Board);
        /*decide what moves he does*/
        turn = 'b';
      }
      else{
        /*black turn*/
        printf("Black turn\n");
        /*check moves tha white can do and write them*/
        newshowBoard(Board);
        BlackMove(Board);
        /*decide what moves he does*/

        turn = 'w';
      }

      /*check if anyone has won the game*/
      /*system("clear");*/
  }

  if(winner =='w')
    printf("White winner\n");
  else
    printf("Black winner\n");

  printf("\nEnd.\n");

  return 0;
}
