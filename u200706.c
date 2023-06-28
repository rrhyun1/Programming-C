#include <stdio.h>
#include <stdlib.h>
#define NUM 20 //define은 대문자로 하는게 관례
#define MAX_LEN 30 //define 에는 콜론(;)을 붙이지 않음

struct data {
    int car_num;
    char name[MAX_LEN];
    char cons[MAX_LEN];
    char nationality[MAX_LEN];
    int birth;
    double point;
}; //구조체에 {}부분의 끝에는 콜론을 붙일 것

void sort2(struct data **a, struct data **b) //포인터를 쓰는 이유 : main 함수에서의 메모리 위치를 "실제로" 바꾸기 위해
// *a라는 data와 *b라는 data를 받아옮
{
    struct data *tmp; //임시(temporary) 데이터를 만듦
    //struct data 타입과 struct data * 타입이랑은 서로 작용이 불가능하기 때문에
    //strucdt data * tmp라고 선언해줘야 한다.

    if( (**a).point < (**b).point ) {//(*a).point의 ()괄호는 필수.
    //()가 없으면 *(a.point)의 의미가 되서 컴파일 에러 남. 에러 연산자를 이용해서 a->point처럼 기술해도 좋다.
    //**a는 &f1_pt에서 왔으므로 struct data 형의 변수로, f1을 의미함. f1의 point 의 차가 발생할 경우,

    tmp = *a; //*a는 struct data * 형의 변수로, f1_pt를 의미. f1_pt를 정렬한다.
    *a = *b;
    *b = tmp; //swap
    }

    return; //void이기 때문에 return 값은 없고 그냥 return
}

int main(void)
{
    struct data f1[NUM]={ // NUM = 20이므로 20개의 구조체 배열을 만듦
        {44,"Lewis Hamilton","Mercedes","United Kingdom",1985,413}, //f1[0] // car number, name, cons, nationality, birth, point
        {77,"Valtteri Bottas","Mercedes","Finland",1989,326},
        {5,"Sebastian Vettel","Ferrari","Germany",1987,240},
        {16,"Charles Leclerc","Ferrari","Monaco",1997,264},
        {33,"Max Verstappen","Red Bull Racing","Netherlands",1997,278},
        {23,"Alexander Albon","Red Bull Racing","Thailand",1996,92},
        {27,"Nico Hulkenberg","Renault","Germany",1987,37},
        {3,"Daniel Ricciardo","Renault","Australia",1989,54},
        {8,"Romain Grosjean","Haas","France",1986,8},
        {20,"Kevin Magnussen","Haas","Denmark",1992,20},
        {55,"Carlos Sainz","McLaren","Spain",1994,96},
        {4,"Lando Norris","McLaren","United Kingdom",1999,49},
        {11,"Sergio Perez","Racing Point","Mexico",1990,52},
        {18,"Lance Stroll","Racing Point","Canada",1998,21},
        {7,"Kimi Raikkonen","Alfa Romeo","Finland",1979,43},
        {99,"Antonio Giovinazzi","Alfa Romeo","Italy",1993,14},
        {26,"Daniil Kvyat","Toro Rosso","Russian Federation",1994,37},
        {10,"Pierre Gasly","Red Bull Racing","France",1996,95},
        {63,"George Russell","Williams","United Kingdom",1998,0},
        {88,"Robert Kubica","Williams","Poland",1984,1} //f1[19]
    };

    struct data *f1_pt[NUM]; //*f1_pt 구조체 배열을 만듦
    int i,j;

    for (i = 0; i < NUM; i++){
        f1_pt[i] = &f1[i]; //f1의 주소값을 f1_pt의 배열에다가 넘김 그러면 *f1_pt[] = f1[]이 됌
    }

    //sort2함수를 이용하는 부분
    for (i=NUM-1; i>0; i--) { //f1_pt의 배열을 정렬함
        for (j=0; j<i; j++) {
            sort2(&f1_pt[j], &f1_pt[j+1]); //f1_pt 2개의 배열요소의 구조체의 주소를 sort함수로 보낸다.
            /* 二つの配列要素(構造体)のアドレスを関数にわたす */
        }
    }

    printf("Original Data\n");//오리지널 배열이 바뀌지 않은 것을 확인
    for (i=0; i<NUM; i++) {
        printf("%2d %-20s %-15s %-20s %4d %4.0f\n",
        f1[i].car_num, f1[i].name, f1[i].cons, f1[i].nationality,
        f1[i].birth, f1[i].point);
    }

    printf("\nSorted Data\n");//f1_pt 배열이 바뀐 것을 확인
    for (i=0; i<NUM; i++) {
        printf("%2d %-20s %-15s %-20s %4d %4.0f\n",
        (*f1_pt[i]).car_num,(*f1_pt[i]).name,(*f1_pt[i]).cons,
        (*f1_pt[i]).nationality,(*f1_pt[i]).birth,(*f1_pt[i]).point);
    }         

    return 0;
}