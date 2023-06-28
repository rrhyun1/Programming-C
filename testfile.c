#include <stdio.h>
#define L 2
#define M 3
#define N 2

int main(void){
    int ma[L][M] = { {1, 2, 3}, {4, 5, 6} };
    int mb[M][N] = { {1,5}, {5, 3}, {8, 1} };
    int mc[L][N] = { {0, 0}, {0, 0} };
    int i, j, k;

    for(i = 0; i < L; i++){
        for(k = 0; k < N; k++){
            for(j = 0; j < M; j++){
                
                
                

            }
        }
    }



    for(i = 0; i < L;  i++){
        for(k = 0; k < N; k++){
            printf("%3d", mc[i][k]);
        }
        printf("\n");
    }

    return 0;
}