#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM 20
#define MAX_LEN 30
#define MAX_LINE 100

struct data {
  int car_num;
  char name[MAX_LEN];
  char cons[MAX_LEN];
  char nationality[MAX_LEN];
  int birth;
  double point;
};

int main(int argc, char* argv[])
{
  /*** ここを記述 ***/
  FILE* fp_in;
  
  struct data f1[NUM];
  int i;
  char line[MAX_LINE]; //line이라는 영역을 설정한다.

  int count=0; /* カウント用の変数 */
  
  if (argc != 3) { /* 引数は使う前に数をチェック */
    fprintf(stderr, "%s input_csv_file nationality\n", argv[0]);
    exit(1);
  }
  
  /* ファイルを開く */
  /* ファイル名は argv[1] を指定すること */
  /*** ここを記述 ***/
  fp_in = fopen(argv[1], "r");
  
  /* ファイルを開くときは必ずエラーチェックをする */
  if (fp_in == NULL) {
    fprintf(stderr, "Can't open file\n");
    exit(1);
  }

  for (i=0; i<NUM; i++) {
    /* １行ずつデータを読み込む */
    /*** ここを記述 ***/
	fgets(line, MAX_LINE, fp_in); //fgets로 line영역에 격납한다 한 줄 분의 데이터를 읽는다.
	sscanf(line, "%d,%[^,],%[^,],%[^,],%d,%lf", &f1[i].car_num, f1[i].name, f1[i].cons, f1[i].nationality, &f1[i].birth, &f1[i].point);
	//읽은 문자열로부터 각 데이터를 변수로 읽는다.
  }

  for (i=0; i<NUM; i++) {
    /* 与えられた国籍のデータを数える */
	if(strcmp(f1[i].nationality, argv[2]) == 0){//strcmp를 이용할 것
		count++;
		printf("%s\n", f1[i].name);
	}
  }
  printf("Number of %s is %d \n", argv[2], count);

  fclose(fp_in);

  return 0;
}

//복기: 다른 파일로부터 데이터를 읽으려면 fgets와 sscanf를 이용해야 한다.
//fgets는 데이터를 프로그램 안의 영역에 격납하는 역할
//sscanf는 격납된 데이터를 변수로 읽는 역할