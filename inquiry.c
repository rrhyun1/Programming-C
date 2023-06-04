#include <stdio.h>
#include <stdlib.h>

typedef struct { //좌표평면의 한 점을 나타내는 구조체
	double x;
	double y;
} Point;


typedef struct { //삼각형을 나타내는 구조체
	Point p[3]; //삼각형의 3개의 각 점을
} Triangle;     //Point 구조체의 배열로 나타낸다


//1개의 Triangle 구조체의 변수와, double 형의 2차원 배열을 인수로 해서, 
//인수로 준 삼각형을 행렬 A에 의해 선형변환한 후의 삼각형(Triangle 구조체)을 반환하는 함수

void linear_transform(Triangle* tri, double A[][2]) //(중요) 구조체 안의 구조체를 함수로 바꿔주기 위해서는 포인터를 이용해야 함!
{
	int i, j;
	//Triangle* faketri;//Triangle에 대한 포인터이지만, 유효한 메모리를 가리키도록 초기화되지는 않았음
	//즉 참조 faketri(-> 연산자 활용)이 정의되지 않은 동작임을 의미
	//new를 사용하여 faketri에 메모리를 할당하거나 스택에 할당된 변수로 만들어야 함
	
	
	for(i = 0; i < 3; i++){
		tri->p[i].x = (tri->p[i].x * A[0][0]) + (tri->p[i].y * A[1][0]); //이러한 객체는 +=연산자를 사용하여 수정할 수 없는 더블 형식
		tri->p[i].y = (tri->p[i].x * A[0][1]) + (tri->p[i].y * A[1][1]); //대신 할당 연산자 = 를 사용해야 함.
	}
	
}
//함수에서 tri에 할당하여 함수에 전달된 원래 Triangle 개체를 업데이트하려고 함.
//그러나 이 할당은 로컬 변수 tri만 업데이트 하고 원래 개체에는 영향을 미치지 않음.
//원래 개체를 업데이트 하려면 해당 구성원을 직접 수정해야 함.


int main(void)
{
	int i, j;
	
	Triangle tri1;
	Triangle tri2;
	double A[2][2];
	
	for(i = 0; i < 3; i++){ //삼각형1에 좌표 입력
		scanf("%lf", &tri1.p[i].x);
		scanf("%lf", &tri1.p[i].y);
	}
	
	for(i = 0; i < 3; i++){ //삼각형2에 좌표 입력
		scanf("%lf", &tri2.p[i].x);
		scanf("%lf", &tri2.p[i].y);
	}
	
	for(i = 0; i < 2; i++){ //Matrix A에 입력
		for(j = 0; j < 2; j++){
			scanf("%lf", &A[i][j]);
		}
	}
	
	printf("T1: (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f)\n", tri1.p[0].x, tri1.p[0].y, tri1.p[1].x, tri1.p[1].y, tri1.p[2].x, tri1.p[2].y);
	printf("T2: (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f)\n\n", tri2.p[0].x, tri2.p[0].y, tri2.p[1].x, tri2.p[1].y, tri2.p[2].x, tri2.p[2].y);
	
	printf("Matrix A:\n%.3f %.3f\n%.3f %.3f\n\n", A[0][0], A[0][1], A[1][0], A[1][1]);
	
	linear_transform(&tri1, A); 
	linear_transform(&tri2, A);
	
	printf("AT1: (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f)\n", tri1.p[0].x, tri1.p[0].y, tri1.p[1].x, tri1.p[1].y, tri1.p[2].x, tri1.p[2].y);
	printf("AT2: (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f)\n\n", tri2.p[0].x, tri2.p[0].y, tri2.p[1].x, tri2.p[1].y, tri2.p[2].x, tri2.p[2].y);
}