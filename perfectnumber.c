#include <stdio.h>

int main(void)
{
    int x, i;

    for(x = 1; x < 10000; x++){
        int count = 0;
        for(i = 1; i < x; i++){
            if(x % i == 0){
                count += i;
            }
        }
        if(count == x){
            printf("%d는 완전수\n", x);
        }
    }

}