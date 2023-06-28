#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(void){
    double r;
    int i, j;
    double y, h;
    int n;

    srand((unsigned int)getpid());

    for(i = 1; i <= 28; i++){//내가 만든 거

        n = pow(2 , i);
        h = 0.0;
        for(j = 0; j < n; j++){
            r = (double)rand() / (RAND_MAX + 1.0); //난수 
            y = sqrt(1 - (2 * r - 1) * (2 * r - 1) );
            h += y;
        }

        printf("%d %f\n", n , 4 * h / n);
    }
    printf("내가 만든 거\n\n");



    for(n = 2; n <= pow(2, 28); n *= 2){//답안
        h = 0.0;
        for(i = 0; i < n; i++){
            r = (double)rand() / (RAND_MAX + 1.0);
            y = sqrt(1 - (2 * r -1) * (2 * r -1) );
            h += y;
        }

        printf("%d %f\n", n, 4 * h / n);
    }
    printf("답안\n");

    return 0;
}