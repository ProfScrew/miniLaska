/*#include <stdio.h>
#include <stdlib.h>

int myfunction(float **input) {
    int i,n=10;
    *input = realloc( *input, n*sizeof(float) );
    if(*input!=NULL) {
        for(i=0;i<n;i++) (*input)[i] = (float)i;
        return(n);
    }
    else return(-1);
}

int main(int argc, char *argv[]) {
    float *data = NULL;
    int n = myfunction(&data);
    int i;
    for(i=0;i<n;i++) printf("%f\n",data[i]);
    free(data);
    return 0;
}

*/
#include <stdio.h>
#include <stdlib.h>



void functionB(int **b){

  *b = (int*) realloc(*b, 3 * sizeof(int));
  **b = 255;
  *(*b + 1) = 130;
  printf("first val %d\n", *b[0] );
  printf("inside funct %d\n", **b);
  printf("one * %d\n", *b);
  printf("no * %d\n", b);
}

int main(int argc, char *argv[]) {
  int i;
    int* a = (int*) malloc(6 * sizeof(int));
    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    a[4] = 4;
    a[5] = 5;
    printf("mem first arr %d\n", a );

    for(i=0;i<6;i++) printf("%d\n",a[i]);

    functionB(&a);

    for(i=0;i<6;i++) printf("%d\n",a[i]);

    return 0;
}
