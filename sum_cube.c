#include <stdio.h>
#include <math.h>

int main(void){
    int a, b, a1, b1, a2, b2;
    int x; //두 수의 세제곱의 합 x
    int sum;

    for(x = 1; x < 10000; x++){

        for(a = 1; a < 22; a++){
            for(b = a; b < 22; b++){

                sum = pow(a , 3) + pow(b, 3);

                if(sum == x){
                    a1 = a;
                    b1 = b;
                }

            }
        }

        for(a = 1; a < 22; a++){
            for(b = a; b < 22; b++){
                sum = pow(a , 3) + pow(b, 3);
                if(sum != x){
                    continue;
                }

                if(a == a1 || a == b1){
                    continue;
                }else{
                    a2 = a;
                    b2 = b;
                    printf("%d = (%d, %d) = (%d, %d)\n", sum, a1, b1, a2, b2);
                }

            }
        }        


    }

}