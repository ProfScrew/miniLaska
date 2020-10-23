#include "stdio.h"

void initBoard(char Board[7][7]){

  int i,j;
  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      if(i%2 == 0){
        if(j%2 == 0)
          Board [i] [j] = ' ';
        else
          Board [i] [j] = '#';

      }
      else{
        if(j%2 == 0)
          Board [i] [j] = '#';
        else
          Board [i] [j] = ' ';
      }
    }
  }
}





void showBoard(char Board[7][7]){
  int i,j;
  for(i=0; i<7; i++){
    for(j=0; j<7; j++){
      printf("%c",Board [i] [j]);
    }
    printf("\n");
  }

}

int main(int argc, char const *argv[]) {
  char Board [7] [7];
  initBoard(Board);
  showBoard(Board);
  printf("\nHello world");

  return 0;
}
