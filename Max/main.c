#include <stdio.h>
#include <stdlib.h>
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

int* registerMoves( int i, int j, int a, int b, int* normalMove , int countNormMoves){

  normalMove[0 + (4 * countNormMoves) -4] = i;
  printf("%d ", normalMove[0 + (4 * countNormMoves) -4]  +1);
  normalMove[1 + (4 * countNormMoves) -4] = j;
  printf("%d ", normalMove[1 + (4 * countNormMoves) -4] +1);
  normalMove[2 + (4 * countNormMoves) -4] = a;
  printf("%d ", normalMove[2 + (4 * countNormMoves) -4] +1);
  normalMove[3 + (4 * countNormMoves) -4] = b;
  printf("%d ", normalMove[3 + (4 * countNormMoves) -4] +1);
  printf("\ncount: %d \n\n", countNormMoves);

  return normalMove;

}

void registerEatMove(int i, int j, int a, int b,int l,int m, int* eatMove, int countEatMove) {

  eatMove[0 + (6 * countEatMove)  ] = i;

  eatMove[1 + (6 * countEatMove) -6] = j;
  eatMove[2 + (6 * countEatMove) -6] = a;
  eatMove[3 + (6 * countEatMove) -6] = b;
  eatMove[4 + (6 * countEatMove) -6] = l;
  eatMove[5 + (6 * countEatMove) -6] = m;


  eatMove = (int*) realloc(eatMove, 6 * countEatMove * sizeof(int));
}

void checkWhiteMove(char Board[7][7][3]){
  int i, j, a, b, l, m;

  int countEatMove = 1;
  int* eatMove = (int*) malloc (6 * countEatMove * sizeof(int));

  int countNormMoves = 1;
  int*  normalMove = (int*) malloc(4  * countNormMoves * sizeof(int));


  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(Board[i][j][0] == 'w'){
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){
          /*can move bot left*/
          normalMove =  registerMoves(i, j, (i+1), (j-1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 *  countNormMoves * sizeof(int));
        }
        if(Board[i+1][j+1][0]== ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){
          /*can move bot right*/
          normalMove = registerMoves(i, j, (i+1), (j+1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }
        /*remember to put else */
        /**/

        if(((Board[i+1][j-1][0] == 'b')|| (Board[i+1][j-1][0] == 'B')) &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i+2][j-2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j-2) > 0 && (j-2) < 7 ))){
            /*can eat bottom left */
            registerEatMove(i,j,i+2,j-2,i+1,j-1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }
        if(((Board[i+1][j+1][0] == 'b')|| (Board[i+1][j+1][0] == 'B')) &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i+2][j+2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j+2) > 0 && (j+2) < 7 ))){
            /*can eat bottom right*/
            registerEatMove(i,j,i+2,j+2,i+1,j+1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }



      }
      if(Board[i][j][0] == 'W'){
        /*first part normal moves to blank spot */
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){        /*check bottom left*/
          registerMoves(i, j, (i+1), (j-1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }
        if(Board[i+1][j+1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right*/
          registerMoves(i, j, (i+1), (j+1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }
        if(Board[i-1][j-1][0] == ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check top left*/
          registerMoves(i, j, (i-1), (j-1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }
        if(Board[i-1][j+1][0] == ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check top right*/
          registerMoves(i, j, (i-1), (j+1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }



        if(((Board[i+1][j-1][0] == 'b')|| (Board[i+1][j-1][0] == 'B')) &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i+2][j-2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j-2) > 0 && (j-2) < 7 ))){
            registerEatMove(i,j,i+2,j-2,i+1,j-1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }
        if(((Board[i+1][j+1][0] == 'b')|| (Board[i+1][j+1][0] == 'B')) &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i+2][j+2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j+2) > 0 && (j+2) < 7 ))){
            registerEatMove(i,j,i+2,j+2,i+1,j+1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }
        if(((Board[i-1][j-1][0] == 'b')|| (Board[i-1][j-1][0] == 'B')) &&  (((i-1) > 0 && (i-1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check top left move */
          if(Board[i-2][j-2][0]== ' ' &&  (((i-2) > 0 && (i-2) < 7) && ((j-2) > 0 && (j-2) < 7 ))){
            registerEatMove(i,j,i-2,j-2,i-1,j-1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }
        if(((Board[i-1][j+1][0] == 'b')|| (Board[i-1][j+1][0] == 'B')) &&  (((i-1) > 0 && (i-1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check top left move */
          if(Board[i-2][j+2][0]== ' ' &&  (((i-2) > 0 && (i-2) < 7) && ((j+2) > 0 && (j+2) < 7 ))){
            registerEatMove(i,j,i-2,j+2,i-1,j+1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }

      }


    }
  }
  if(((countNormMoves - 1) == 0 )&& ((countEatMove - 1) == 0) ){  /*white player can't do any moves*/
    winner = 'b';
    return;
  }

/*
  printf("normal moves %d\n", countNormMoves );
  for (i = 0; i < ((countNormMoves ) * 4); i++) {
    if(i%4 == 0){
      printf("\n");
    }
    printf("inside ?\n");
    printf("value : %d ", normalMove[i] );

  }
  printf("\nends here.\n");
  free(normalMove);
  free(eatMove);
*/

}

void checkBlackMove(char Board[7][7][3]){
  int i, j, a, b, l, m;

  int countEatMove = 1;
  int* eatMove = (int*) malloc (6 * countEatMove * sizeof(int));

  int countNormMoves = 1;
  int*  normalMove = (int*) malloc(4  * countNormMoves * sizeof(int));


  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(Board[i][j][0] == 'b'){
        if(Board[i-1][j-1][0] == ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){
          /*can top bot left*/
          normalMove =  registerMoves(i, j, (i-1), (j-1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 *  countNormMoves * sizeof(int));
        }
        if(Board[i-1][j+1][0]== ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){
          /*can top bot right*/
          normalMove = registerMoves(i, j, (i-1), (j+1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }
        /*remember to put else */
        /**/

        if(((Board[i-1][j-1][0] == 'w')|| (Board[i-1][j-1][0] == 'W')) &&  (((i-1) > 0 && (i-1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i-2][j-2][0]== ' ' &&  (((i-2) > 0 && (i-2) < 7) && ((j-2) > 0 && (j-2) < 7 ))){
            /*can eat bottom left */
            registerEatMove(i,j,i-2,j-2,i-1,j-1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }
        if(((Board[i-1][j+1][0] == 'w')|| (Board[i-1][j+1][0] == 'W')) &&  (((i-1) > 0 && (i-1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i-2][j+2][0]== ' ' &&  (((i-2) > 0 && (i-2) < 7) && ((j+2) > 0 && (j+2) < 7 ))){
            /*can eat bottom right*/
            registerEatMove(i,j,i-2,j+2,i-1,j+1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }



      }
      if(Board[i][j][0] == 'B'){
        /*first part normal moves to blank spot */
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){        /*check bottom left*/
          registerMoves(i, j, (i+1), (j-1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }
        if(Board[i+1][j+1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right*/
          registerMoves(i, j, (i+1), (j+1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }
        if(Board[i-1][j-1][0] == ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check top left*/
          registerMoves(i, j, (i-1), (j-1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }
        if(Board[i-1][j+1][0] == ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check top right*/
          registerMoves(i, j, (i-1), (j+1), normalMove, countNormMoves);
          countNormMoves++;
          normalMove = (int*) realloc(normalMove, 4 * countNormMoves * sizeof(int));
        }



        if(((Board[i+1][j-1][0] == 'w')|| (Board[i+1][j-1][0] == 'W')) &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i+2][j-2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j-2) > 0 && (j-2) < 7 ))){
            registerEatMove(i,j,i+2,j-2,i+1,j-1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }
        if(((Board[i+1][j+1][0] == 'w')|| (Board[i+1][j+1][0] == 'W')) &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i+2][j+2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j+2) > 0 && (j+2) < 7 ))){
            registerEatMove(i,j,i+2,j+2,i+1,j+1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }
        if(((Board[i-1][j-1][0] == 'w')|| (Board[i-1][j-1][0] == 'W')) &&  (((i-1) > 0 && (i-1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check top left move */
          if(Board[i-2][j-2][0]== ' ' &&  (((i-2) > 0 && (i-2) < 7) && ((j-2) > 0 && (j-2) < 7 ))){
            registerEatMove(i,j,i-2,j-2,i-1,j-1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }
        if(((Board[i-1][j+1][0] == 'w')|| (Board[i-1][j+1][0] == 'W')) &&  (((i-1) > 0 && (i-1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check top left move */
          if(Board[i-2][j+2][0]== ' ' &&  (((i-2) > 0 && (i-2) < 7) && ((j+2) > 0 && (j+2) < 7 ))){
            registerEatMove(i,j,i-2,j+2,i-1,j+1, eatMove, countEatMove);
            countEatMove++;
            eatMove = (int*) realloc(eatMove, 4 * countEatMove * sizeof(int));
          }
        }

      }


    }
  }
  if(((countNormMoves - 1) == 0 )&& ((countEatMove - 1) == 0) ){  /*white player can't do any moves*/
    winner = 'w';
    return;
  }

/*
  printf("normal moves %d\n", countNormMoves );
  for (i = 0; i < ((countNormMoves ) * 4); i++) {
    if(i%4 == 0){
      printf("\n");
    }
    printf("inside ?\n");
    printf("value : %d ", normalMove[i] );

  }
  printf("\nends here.\n");
  free(normalMove);
  free(eatMove);
*/

}





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
  newshowBoard(Board);
  checkWhiteMove(Board);


  /*system("clear");*/

  /* while loop where each player has a to do a move */
  while(winner == 'n'){
    /*so we have two funcition that move  but before we need to make a funcition
      at the ending where the system checks if someone has won*/
      if(turn == 'w'){
        /*white turn functions*/
        printf("White move\n");
        /*check moves tha white can do and write them*/

        /*decide what moves he does*/
        turn = 'b';
      }
      else{
        /*black turn*/
        printf("Black turn\n");
        /*check moves tha white can do and write them*/

        /*decide what moves he does*/

        turn = 'b';
      }

      /*check if anyone has won the game*/

      winner = 'b';
  }

  if(winner =='w')
    printf("White winner\n");
  else
    printf("Black winner\n");

  printf("\nEnd.\n");

  return 0;
}
