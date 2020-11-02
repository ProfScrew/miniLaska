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
