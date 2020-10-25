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

void checkWhiteMove(char Board[7][7][3]){
  int i, j;


  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(Board[i][j][0] == 'w'){
        if(j==0){ /*white pieces on left side*/
          if(i)
          if(Board[i+1][j+1][0]== 'w' || Board[i+1][j+1][0] == 'W'){
            /*cant move*/
          }else if(Board[i+1][j+1][0] == ' '){
            /*blank space can move here */
          }else if(Board[i+1][j+1][0] == 'b' || Board[i+1][j+1][0] == 'B' ){
            if(Board[][][])
            if(Board[i+2][i+2][0] ==  ' '){
              if(Board[][][] == )
              /*can eat enemy piece */

            }
          }
        }else if(j==6){
          if (/* condition */) {
            /* code */
          }
        }else{

        }
      }
      if(Board[i][j][0] == 'W'){

      }
    }
  }

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
