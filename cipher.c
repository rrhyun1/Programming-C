//수업자료에 있는대로 해도 좋을듯?

#include <stdio.h>
#include <string.h>

void sort(char[], int);

int main(void)
{
    int key = 1; //key

    char ciphertext[] = "f2/)+E='9E(+-/44/4-E:5E-+:E<+8?E:/8+*E5,E9/::/4-E(?E.+8E9/9:+8E54E:.+E('41QE'4*E5,E.'</4-E45:"
    "./4-E:5E*5_E54)+E58E:=/)+E9.+E.'*E6++6+*E/4:5E:.+E(551E.+8E9/9:+8E='9E8+'*/4-QE(;:E/:E.'*E45E6/):;8+9E58E)54<+89':"
    "/549E/4E/:QE&'4*E=.':E/9E:.+E;9+E5,E'E(551QLE:.5;-.:Ef2/)+E&=/:.5;:E6/):;8+9E58E)54<+89':/54dL";

    printf("%s\n\n", ciphertext);

    //int len = 0;

    printf("n번째 자리의 숫자는 %c\n\n", ciphertext[300]);

    //printf("len %d\n", len);    

    for(key = 58; key < 59; key++){// 문자열에서 각각의 문자를 key값만큼 더한 문자로 나타낸다
        sort(ciphertext, key);
    }

}

void sort(char text[], int key)
{
    int t;
    int len = 0;

    for(t = 0; 1; t++){
        if(text[t] != '\0'){
            len++;
        }else break;
    }

    printf("key는 %d이고 text의 길이는 %d이다\n", key, len);
    printf("맨 앞의 문자는 %c였으나\n", (int)text[0]);

    /*for(t = 0; t < len; t++){//문자열의 각 문자마다 key값을 더한 문자열로 바꿈
        if(text[t] - key < 32){
            text[t] += 95;
        }
        text[t] = text[t] - key;//뺄경우엔 key=37
    }*/

    for(t = 0; t < len; t++){//문자열의 각 문자마다 key값을 더한 문자열로 바꿈
        if(text[t] + key > 126){
            text[t] -= 95;
        }
        text[t] = text[t] + key;//더할경우엔 key=58
    }

    printf("맨 앞의 문자는 %c이다\n", text[0]);

    printf("%s\n\n", text);
    
    for(t = 0; t < len; t++){ //복구 프로세스
        text[t] += 33;
    }

}