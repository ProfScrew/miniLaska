#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[]) {
  int i;
  int* normalMove =(int*) malloc(4 * 1 * sizeof(int));

  for(i=0; i<4; i ++){
    normalMove[i] = i;
    printf("%d\n", normalMove[i] );
  }

  normalMove = (int*) realloc(normalMove, 5 * sizeof(int));

  normalMove[4] = 6;

  for(i=0; i<5; i ++){
    printf("%d\n", normalMove[i] );
  }
}
