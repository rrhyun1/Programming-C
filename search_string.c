#include <stdio.h>

int length(char a[]) //문자열의 길이를 반환하는 함수
{
	int i = 0;
	int len = 0;
	for(i = 0; a[i] != '\0'; i++){
		len++;
	}
	return len;
}

void search(char a[], char b[]) //문자열 a에서 문자열 b를 찾는 함수
{
	int i, j;
	int count = 0;
	int nocount = 0;
	
	for(i = 0; i < length(a); i++){ //배열 a의 길이에서
		
		if(a[i] == b[0]){//배열 b의 첫 글자가 배열 a 중에 있으면 그 자리를 i 라고 함
			count++;
			
			for(j = 1; j < length(b); j++){ // i+1 ~ i+b-1 까지 (배열 b의 길이 - 1)만큼 비교. 같으면 +1 
				if(a[i+j] == b[j]){
					count++;
				}else{
					count = 0;
					break;
				}
			}
			
			if(count == length(b)){
				printf("%d글자째 ~ %d글자째\n", i, i+j-1);
				nocount++;
				i += (length(b) - 1);
			}
			
		}
		count = 0;
		
	}

	
	if(nocount == 0){
		printf("문자열 %s는 존재하지 않습니다. \n", b);
	}
	
}


int main(void)
{
	char p1[32];
	char p2[32];
	
	printf("검색대상의 문자열을 입력해 주세요\n");
	scanf("%s", p1);
	
	printf("검색하고 싶은 문자열을 입력해 주세요\n");
	scanf("%s", p2);
	
	//p2로 p1을 검색하는 함수
	
	printf("p1의 문자열의 길이는 %d\n", length(p1));
	printf("p2의 문자열의 길이는 %d\n\n", length(p2));
	

	printf("문자열 %s는 이하의 장소에 존재합니다. \n", p2);

	search(p1, p2);
	
}