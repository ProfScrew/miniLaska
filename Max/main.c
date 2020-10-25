#include <stdio.h>
#include <stdlib.h>
void initBoard(char Board[7][7][3]){

  int i,j;
  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(i%2 == 0){
        if(j%2 == 0)
          Board [i] [j] [0] = ' ';
        else
          Board [i] [j] [0]= '#';

      }
      else{
        if(j%2 == 0)
          Board [i] [j] [0]= '#';
        else
          Board [i] [j] [0]= ' ';
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
void whiteSoldierMovement(){

}

void checkWhiteMove(char Board[7][7][3]){
  int i, j;
  int k, l;

  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(Board[i][j][0] == 'w'){
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){
          /*can move bot left*/
        }else if(Board[i+1][j+1][0]== ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){
          /*can move bot right*/
        }
        /*remember to put else */
        else{
          for(k=0;k<3;k++){
            l = 1; /* thi variable is used to check if there are any kill moves if no then leave loop*/
            if(((Board[i+1+k][j-1-k][0] == 'b')|| (Board[i+1+k][j-1-k][0] == 'B')) &&  (((i+1+k) > 0 && (i+1+k) < 7) && ((j-1-k) > 0 && (j-1-k) < 7 ))){  /*check left move */
              if(Board[i+2+k][j-2-k][0]== ' ' &&  (((i+2+k) > 0 && (i+2+k) < 7) && ((j-2-k) > 0 && (j-2-k) < 7 ))){
                l = 0;
                /*can eat left at least once
                  then we have to run the for loop if we can go further */

                if(k!=0){}/*register more kill moves */

                /*normal kill move */

              }

            }
              if(((Board[i+1+k][j+1+k][0] == 'b')|| (Board[i+1+k][j+1+k][0] == 'B')) &&  (((i+1+k) > 0 && (i+1+k) < 7) && ((j+1+k) > 0 && (j+1+k) < 7 ))){  /*check right move*/
                if(Board[i+2+k][j+2+k][0]== ' ' &&  (((i+2+k) > 0 && (i+2+k) < 7) && ((j+2+k) > 0 && (j+2+k) < 7 ))){
                  l = 0;
                  /*can eat right at least once
                    then we have to run the for loop to check if we can go further*/

                }
              }

            if(l == 1){
              k=3; /*if cant find moves in the loop then stop*/
              l=0;
              }


          }
        }
      }
      if(Board[i][j][0] == 'W'){
        /*first part normal moves to blank spot */
        if(Board[i+1][j-1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){        /*check bottom left*/

        }else if(Board[i+1][j+1][0] == ' ' &&  (((i+1) > 0 && (i+1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check bottom right*/

        }else if(Board[i-1][j-1][0] == ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j-1) > 0 && (j-1) < 7 ))){  /*check top left*/

        }else if(Board[i-1][j+1][0] == ' ' &&  (((i-1) > 0 && (i-1) < 7) && ((j+1) > 0 && (j+1) < 7 ))){  /*check top right*/

        }else{
          while(l==1){}
        }

      }
    }
  }



/*  too complex if the other doesnt work come back to this
  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(Board[i][j][0] == 'w'){
        if(j==0){ /*white pieces on left side
          if(i==5){
            if(Board[i][j][0] == ' '){
              /*can move for promotion
            }
          }else if(Board[i+1][j+1][0]== 'w' || Board[i+1][j+1][0] == 'W'){
            /*cant move
          }else if(Board[i+1][j+1][0] == ' '){
            /*blank space can move here
          }else if(Board[i+1][j+1][0] == 'b' || Board[i+1][j+1][0] == 'B' ){
            if(Board[i+2][j+2][0] ==  ' ' &&  (i+2) == 5){
              /*just one move can eat
            }else if(Board[i+2][i+2][0] == ' '){
              if(left){

              }else if(right){
                if (right){
                  ************
                }else{/*can eat two peaces }
              }
            }

              /*can eat enemy piece

            }
          }
        }else if(j==6){
          if (/* condition ) {
            /* code
          }
        }else{

        }
      }
      if(Board[i][j][0] == 'W'){

      }
    }
  }
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

int main(int argc, char const *argv[]) {
  char Board [7] [7] [3];
  char winner = 'n';
  char turn = 'w';
  initBoard(Board);
  showBoard(Board);
  startPlayerOne(Board);
  startPlayerTwo(Board);
  showBoard(Board);

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
