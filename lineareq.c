#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DIM 4

//문제에서 제시하는 것 : 4*4 행렬의 방정식을 풀어라 요컨대 x[1] ~ x[n] 을 구하라는 것

void swap(double array[][DIM], int p, int q, int n_col)//2중배열의 p행과 q행을 바꾸는 함수
{
    double tmp[DIM]; //swap할 때 필요한 array 임시 배열[4]
    int i;

    for(i = 0; i < n_col; i++){
        tmp[i] = array[p][i];
        array[p][i] = array[q][i];
        array[q][i] = tmp[i];
    }
}

void swap_b(double b[], int p, int q){
    double tmp;
    tmp = b[p];
    b[p] = b[q];
    b[q] = tmp;
}

void degree(double array[DIM][DIM], int p, int q, double c, int n_col) //2중배열의 제p행의 c배를 q행에 더하는 함수  |  n_col = 열
{   
    int i;
    for(i = 0; i < n_col; i++){ //n_col은 열의 개수
        array[q][i] += (array[p][i] *  c);
    }
}

void get_ans(double array[][DIM], double b[], double ans[], int n_row, int n_col) //n_row = 행  |  n_col = 열(column)
//행렬 방정식을 다 전개해서 얻은 함수
{ //get_ans는 vec_x의 n번째 항을 얻기 위한 함수
    int i, k;

    for(k = n_row-1; k >= 0; --k){ //k가 행의 숫자에서 0이 될때까지 줄어든다 밑의 행부터 시작
        ans[k] = 0.0; //ans는 vec_x의 배열을 갖고 온 것이므로 초기화 시켜준다
        for(i = k+1; i < n_col; ++i){
            ans[k] += (array[k][i] * ans[i]); //시그마 a[k][i] * x[i]
        }
        ans[k] = (b[k] - ans[k]) / array[k][k]; //x[k] = (b[k] - 시그마) / a[k][k]
    }

}

int main()
{   
    int i, k;
    double c;
    int n_col = DIM, n_row = DIM;
    double array_A[DIM][DIM] = { {2.0, 4.0, 1.0, -3.0}, {-1.0, -2.0, 2.0, 4.0}, {4.0, 2.0, -3.0, 5.0},
    {5.0, -4.0, -3.0, 1.0} };
    double vec_b[DIM] = {0.0, 10.0, 2.0, 6.0};
    double vec_x[DIM];

    printf("Original matrix\n\n");
    printf("                            x      b\n");

    for(i = 0; i < DIM; i++){
        for(k = 0; k < DIM; k++){
            printf("%5.1f ", array_A[i][k]);
        }
        printf(" %5.1f ", vec_x[i]);
        printf(" %5.1f ", vec_b[i]);
        printf("\n\n");
    }    

    for(i = 0; i < n_col; i++){

        for(k = i+1; k < n_col; k++){
            if( fabs(array_A[i][i]) <  fabs(array_A[i][k]) ){
                swap(array_A, i, k, n_col);
                swap_b(vec_b, i, k);
            }
        }



        for(k = i+1; k < n_row; k++){
            
            /*if(array_A[i][i] == 0){
                swap(array_A, i, i+1, n_col);
                swap_b(vec_b, i, i+1);
            }*/

            c = array_A[k][i] / array_A[i][i]; //각 행의 선두의 숫자를 0으로 만드는 현재의 선두 행렬항
            degree(array_A, i, k, -c, n_col); //i행의 -c배를 k행에 더하는 것
            vec_b[k] -= (c * vec_b[i]);  //vec_b의 i행의 c배를 k행에서 빼는 것
        }
    }
    get_ans(array_A, vec_b, vec_x, n_row, n_col);//array배열과 vec_b배열을 최적화 시켰으므로 get_ans로 vec_x배열의 값만 구하면 된다.
    

    printf("solved matrix\n\n");
        printf("                            x      b\n");

    for(i = 0; i < DIM; i++){
        for(k = 0; k < DIM; k++){
            printf("%5.1f ", array_A[i][k]);
        }
        printf(" %5.1f ", vec_x[i]);
        printf(" %5.1f ", vec_b[i]);
        printf("\n\n");
    }
}