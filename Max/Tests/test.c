#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[]) {
  int countEatMove = 1;
  int* eatMove = (int*) malloc(6 * countEatMove * sizeof(int));

  int countNormMoves = 1;
  int*  normalMove = (int*) malloc(4  * countNormMoves * sizeof(int));

  printf("ok\n");
  free(eatMove);
  free(normalMove);


  return 0;
}
