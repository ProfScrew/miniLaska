#include <stdio.h>
#include <stdlib.h>
void initBoard(int Board[7][7][3],int b){
  b = 1;
  int i,j;
  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(i%2 == 0){
        if(j%2 == 0){
          Board [i] [j] [0] = 1;
          Board [i] [j] [1] = 1;
          Board [i] [j] [2] = 1;
        }
        else
          Board [i] [j] [0]= 0;

      }
      else{
        if(j%2 == 0)
          Board [i] [j] [0]= 0;
        else{
          Board [i] [j] [0]= 1;
          Board [i] [j] [1] = 1;
          Board [i] [j] [2] = 1;
        }
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  int b = 0;

  int Board[7][7][3];

  initBoard(Board, b);

  int i,j;
  printf("   a b c d e f g\n");
  printf("  ===============\n");
  for(i=0; i<7; i++){
    printf("%d |", i+1);
    for(j=0; j<7; j++){
      printf("%d|",Board [i] [j] [0]);
    }
    printf("\n");
  }
  printf("  ===============\n");

  printf("%d \n",  b);
  return 0;
}

















void checkWhiteMove(char Board[7][7][3]){
  int i, j;
  int move;

  int countEatMove = 1;
  int* eatMove = (int*) malloc (6 * countEatMove * sizeof(int));

  int countNormMoves = 1;
  int*  normalMove = (int*) malloc(4  * countNormMoves * sizeof(int));

  newshowBoard(Board);

  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(Board[i][j][0] == 'w'){
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){
          /*can move bot left*/
          normalMove =  registerMoves(i, j, (i+1), (j-1), normalMove, &countNormMoves);
        }
        if(Board[i+1][j+1][0]== ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){
          /*can move bot right*/
          normalMove = registerMoves(i, j, (i+1), (j+1), normalMove, &countNormMoves);
        }
        /*remember to put else */
        /**/

        if(((Board[i+1][j-1][0] == 'b')|| (Board[i+1][j-1][0] == 'B')) &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i+2][j-2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j-2) > 0 && (j-2) < 7 ))){
            /*can eat bottom left */
            registerEatMove(i,j,i+1,j-1,i+2,j-2, eatMove, &countEatMove);
            eatMove = (int*) realloc(eatMove, 6 * (countEatMove) * sizeof(int));
          }
        }
        if(((Board[i+1][j+1][0] == 'b')|| (Board[i+1][j+1][0] == 'B')) &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i+2][j+2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j+2) > 0 && (j+2) < 7 ))){
            /*can eat bottom right*/
            registerEatMove(i,j,i+1,j+1,i+2,j+2, eatMove, &countEatMove);
            eatMove = (int*) realloc(eatMove, 6 * (countEatMove) * sizeof(int));
          }
        }



      }
      if(Board[i][j][0] == 'W'){
        /*first part normal moves to blank spot */
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){        /*check bottom left*/
          registerMoves(i, j, (i+1), (j-1), normalMove, &countNormMoves);
        }
        if(Board[i+1][j+1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right*/
          registerMoves(i, j, (i+1), (j+1), normalMove, &countNormMoves);
        }
        if(Board[i-1][j-1][0] == ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check top left*/
          registerMoves(i, j, (i-1), (j-1), normalMove, &countNormMoves);
        }
        if(Board[i-1][j+1][0] == ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check top right*/
          registerMoves(i, j, (i-1), (j+1), normalMove, &countNormMoves);
        }



        if(((Board[i+1][j-1][0] == 'b')|| (Board[i+1][j-1][0] == 'B')) &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check bottom left move */
          if(Board[i+2][j-2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j-2) > 0 && (j-2) < 7 ))){
            registerEatMove(i,j,i+1,j-1,i+2,j-2, eatMove, &countEatMove);
            eatMove = (int*) realloc(eatMove, 6 * (countEatMove) * sizeof(int));
          }
        }
        if(((Board[i+1][j+1][0] == 'b')|| (Board[i+1][j+1][0] == 'B')) &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right move*/
          if(Board[i+2][j+2][0]== ' ' &&  (((i+2) > 0 && (i+2) < 7) && ((j+2) > 0 && (j+2) < 7 ))){
            registerEatMove(i,j,i+1,j+1,i+2,j+2, eatMove, &countEatMove);
            eatMove = (int*) realloc(eatMove, 6 * (countEatMove) * sizeof(int));
          }
        }
        if(((Board[i-1][j-1][0] == 'b')|| (Board[i-1][j-1][0] == 'B')) &&  (((i-1) > 0 && (i-1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check top left move */
          if(Board[i-2][j-2][0]== ' ' &&  (((i-2) > 0 && (i-2) < 7) && ((j-2) > 0 && (j-2) < 7 ))){
            registerEatMove(i,j,i-1,j-1,i-2,j-2, eatMove, &countEatMove);
            eatMove = (int*) realloc(eatMove, 6 * (countEatMove) * sizeof(int));
          }
        }
        if(((Board[i-1][j+1][0] == 'b')|| (Board[i-1][j+1][0] == 'B')) &&  (((i-1) > 0 && (i-1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check top left move */
          if(Board[i-2][j+2][0]== ' ' &&  (((i-2) > 0 && (i-2) < 7) && ((j+2) > 0 && (j+2) < 7 ))){
            registerEatMove(i,j,i-1,j+1,i-2,j+2, eatMove, &countEatMove);
            eatMove = (int*) realloc(eatMove, 6 * (countEatMove) * sizeof(int));
          }
        }

      }


    }
  }

  if(((countNormMoves - 1) == 0 )&& ((countEatMove - 1) == 0) ){  /*white player can't do any moves*/
    winner = 'b';
    return;
  }
  j=1;
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
    scanf("%d", &move );
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
    scanf("%d", &move );
    normalMovement(normalMove, move ,Board);

  }

  free(eatMove);
  free(normalMove);

}
