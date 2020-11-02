#include <stdio.h>
#include <stdlib.h>

void secondfunction(int a) {
  a = a + 1;
}

void firstfunction (){
  int a = 0;
  printf("%d\n", a);
  secondfunction(a);
  printf("%d\n", a );
}

void thirdfunction(int b) {
  b = b + 1 ;
}



int main(int argc, char const *argv[]) {




  int i,n;
  int* normalMove =(int*) malloc(4 * 1 * sizeof(int));

  for(i=0; i<4; i ++){
    normalMove[i] = i;
    printf("%d", normalMove[i] );
  }
  printf("\n");
  n = 2;
  normalMove = (int*) realloc(normalMove, 4 * n * sizeof(int));

  normalMove[4] = 6;
  normalMove[5] = 7;
  normalMove[6] = 8;
  normalMove[7] = 9;

  for(i=0; i<8; i ++){
    printf("%d", normalMove[i] );
  }
  printf("\n" );

  /*
  int i, j, p;

  for(i=0; i<7; i++){
    for (p=0; p<3; p++) {
      for(j=0; j<7;i++){
        if ('#' == '#') {
          printf("###");
        }else{
          printf("   ");
        }
      }
      printf("\n");
    }

  }
  printf("\n");
*/
}
