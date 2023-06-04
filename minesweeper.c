#include <stdio.h>
#define X_SIZE 10
#define Y_SIZE 10



int main(void)
{
    int map[X_SIZE][Y_SIZE] = {{0}}; //0으로 초기화
    int x, y;
    int i, j, k, l;//i, k는 x축 j, l은 y축

    map[0][0] = map[4][1] = map[5][2] = map[9][2] //지뢰 설치되어 있는 위치
    = map[5][3] = map[3][4] = map[4][4]
    = map[1][5] = map[0][7] = map[2][7]
    = map[7][7] = map[0][8] = map[1][8]
    = map[7][8] = map[2][9] = -1;

    for(i = 1; i < 9; i++){ // x = 1 ~ x = 8, y = 1 ~ y = 8
        for(j = 1; j < 9; j++){
            if(map[i][j] == -1){
                continue;
            }
            for(k = -1; k <= 1; k++){
                for(l = -1; l <= 1; l++){
                    if(map[i+k][j+l] == -1){
                        map[i][j]++;
                    }
                }
            }
        }
    }

    for(i = 0; i < 10; i++){ // x = 0 ~ x = 9, y = 0
        if(map[i][0] == -1){
            continue;
        }
        for(k = -1; k <= 1; k++){
            for(l = 0; l <= 1; l++){
                if(map[i+k][l] == -1){
                    map[i][0]++;
                }
            }
        }
    }

    for(i = 1; i < 10; i++){ // x = 1 ~ x = 8, y = 9
        if(map[i][9] == -1){
            continue;
        }
        for(k = -1; k <= 1; k++){
            for(l = -1; l <= 0; l++){
                if(map[i+k][9+l] == -1){
                    map[i][9]++;
                }
            }
        }
    }

    for(j = 0; j < 10; j++){ // x = 0, y = 0 ~ y = 9
        if(map[0][j] == -1){
            continue;
        }
        for(k = 0; k <= 1; k++){
            for(l = -1; l <= 1; l++){
                if(map[k][j+l] == -1){
                    map[0][j]++;
                }
            }
        }
    }

    for(j = 1; j < 9; j++){ // x = 9, y = 1 ~ y = 8
        if(map[9][j] == -1){
            continue;
        }
        for(k = -1; k <= 0; k++){
            for(l = -1; l <= 1; l++){
                if(map[9+k][j+l] == -1){
                    map[9][j]++;
                }
            }
        }
    }

    printf("  0 1 2 3 4 5 6 7 8 9\n"); // x = 0 ~ x = 9, y = 9
    for(y = 0; y < Y_SIZE; y++){
        printf("%d", y);
        for(x = 0; x < X_SIZE; x++){
            if(map[x][y] == -1){
                printf(" B"); //지뢰 표시
            }else if(map[x][y] == 0){
                printf(" 0");
            }else{
                printf(" %d", map[x][y]);
            }
            

        }
        printf("\n");
    }

}