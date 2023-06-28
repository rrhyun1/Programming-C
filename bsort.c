#include <stdio.h>

//프로토타입 선언
//bsort() 함수를 main()함수의 밑에 쓰는 경우에 필요
//다른 적합함수를 써도 상관 X

void bsort(int[], int);

int main()
{
    int i, num = 0;
    //정수형의 배열변수 ary[]를 선언해서 적합치를 대입한다
    int ary[256] ;
    //= {9, 3, 0, 8, 5, 1, 6, 4, 7, 2};

    printf("Input:");

    for(i = 0; i < 10; i++){
        scanf("%d", &ary[i]);
        num++;  // n = 10
    }

    //여기서 ary[]는 아직 배열이 바뀌지 않았다.
    //1의 표시

    /*for(i = 0; i < 10; i++){
        printf("%d ", ary[i]);
    }*/
    printf("\n\n");


    bsort(ary, num); // num은 ary의 요소수

    //bsort() 함수의 뒤에는 ary[]는 작은 순으로 되어있다.
    //2의 표시
    printf("\n\nResult:");

    for(i = 0; i < 10; i++){
        printf("%d ", ary[i]);
    }
    printf("\n");

    return 0;
}

void bsort(int ary[], int n)//배열은 포인터를 쓰지 않아도 main함수에 영향을 줄 수 있다.
{
    int tmp;
    int i = 0;
    int j = 0;
    n--;
    //n = 9;

    while(1){

        for(i = n; i > 0; i--){
            if(ary[i] < ary[i - 1]){
                tmp = ary[i];
                ary[i] = ary[i-1];
                ary[i-1] = tmp;
            }
        }

        for(i = 0; i <= n; i++){
            printf("%d ", ary[i]);
        }
        printf("\n");

        /*for(n = 0; n < 10; n++) {
            if(ary[n] > ary[n+1]){
                i++;
            }
        }*/
        
        j++;
        if(j == n){
            break;
        }
    }
}