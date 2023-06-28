#include <stdio.h>
#include <string.h>


void replace(char str1[], char str2[],char pat[],char rep[]){
	int i;
	for(i = 0; i < 20; i++){ //(중요)replace 내용을 문자열의 길이만큼 반복시켜 준다
		if( strncmp( str1, pat, strlen(pat) ) == 0 ){ //지금 현재 커서에 있는 str1과 pat의 배열을 pat의 길이만큼 비교를 한다
			strcat(str2, rep); //둘이 같으면 str2에 rep문자열을 붙인다
			str1 = str1 + strlen(pat); //str1 문자열에서 pet문자열의 길이만큼 뒤로 이동한다.
		} else { //만약 같지 않다면
			strncat(str2, str1, 1); //str2문자열에 str1문자열을 길이 1만큼 붙인다 
			str1++; //그리고 str1의 문자열에서 1만큼 이동한다.
			//printf("str1[%d] = %s 붙임\n", i, str2);
		}
		
		//if(str1[i] == '\0') break;
	}
}



int main(int argc, char *argv[]) //이에 관한 내용은 20200629 자료에 있음
{
	char str1[1000];
	char str2[2000];
	char pat[100];
	char rep[100];
	
	strcpy(str1, argv[1]);
	//strcpy(str2, str1);
	strcpy(pat, argv[2]);
	strcpy(rep, argv[3]);
	
	printf("대상문자열 str1 : %s\n조합문자열  pat : %s\n치환문자열  rep : %s\n\n", str1, pat, rep);
	
	//str1문자열에서 pat 문자열을 찾아낸다
	
	replace(str1, str2, pat, rep);
	/*if( strncmp( str1, pat, strlen(pat) ) == 0 ){ //지금 현재 커서에 있는 str1과 pat의 배열을 pat의 길이만큼 비교를 한다
		strcat(str2, rep); //둘이 같으면 str2에 rep문자열을 붙인다
		str1 = str1 + strlen(pat); //str1 문자열에서 pet문자열의 길이만큼 뒤로 이동한다.
	} else { //만약 같지 않다면
		strncat(str2, str1, 1); //str2문자열에 str1문자열을 길이 1만큼 붙인다
		str1++; //그리고 str1의 문자열에서 1만큼 이동한다.
	}*/
	
	printf("치환 후의 문자열은 \n%s\n입니다. \n", str2);
}