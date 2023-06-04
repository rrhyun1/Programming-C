#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int uru(int year, int month)
/* year年month月がうるう月なら1を返し、それ以外は0を返す関数 */
/* うるう年の規則
400で割り切れる年はうるう年である
100で割り切れる年はうるう年ではない
4で割り切れる年はうるう年である
それ以外の年はうるう年ではない
*/

{
    /**** 2月以外は0を返す */
    /**** 2月なら、規則に従い、1か0を返す */
    int uru = 0; //uru를 0으로 초기화하지않으면 int의 최대값이 나와버림
	
	if(month != 2){
		uru = 0;
	}else{
		if(year % 4 == 0){
			uru =1;
		}if(year % 100 == 0){
			uru = 0;
		}if(year % 400 == 0){
			uru =1;
		}
	}

    return uru;
}

int main(int argc, char *argv[])
{
	int yearnum = 0;
    int count=0;
    int year, month, day;
    int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31}; //각 달의 일수
    /* 今日の日付を得る */
    int t_year, t_month, t_day;
    struct tm *today; //년,월,일의 구조의 포인터 값
    time_t tp;
    time(&tp); //tp값의 주소
    today = localtime(&tp);
    t_year = today->tm_year+1900;
    t_month = today->tm_mon+1;
    t_day = today->tm_mday;
    
    /* 引数の数のチェック */
    if (argc != 4) {
        /* 引数の数が仕様(年、月、日)と合わない場合は
        使用方法を出力して強制終了 */
        
        fprintf(stderr, "Usage: %s year month day\n", argv[0]);
        exit(1);
    }
    /**** year に 第1引数の値を代入(atoiを利用) */
    year = atoi(argv[1]);


    /**** month に 第2引数の値を代入(atoiを利用) */
    month = atoi(argv[2]);


    /* monthが妥当な数字か確認 */
    if (month < 1 || month > 12) {
        fprintf(stderr, "monthは1から12の整数を入力して下さい。\n");
        exit(2);
    }

    /**** day に 第3引数の値を代入(atoiを利用) */
    day = atoi(argv[3]);

    /* ☆dayが妥当な数字か確認 */
    if ( day < 1 || day > days[month]+uru(year,month)) {
        fprintf(stderr, "day has to be from 1 to %d\n", days[month]+uru(year,month));
        exit(3); /* 強制終了 */
    }


    /* 未来の場合は日付を逆にする */
    if ((t_year<year) ||
        ((t_year==year) && (t_month<month)) ||
        ((t_year==year) && (t_month==month) && (t_day<day))) {
        int tmp;
        printf("%d年%d月%d日まで\n", year, month, day);
        tmp=year; year=t_year; t_year=tmp; //year와 t_year를 바꿈
        tmp=month; month=t_month; t_month=tmp; //서로 swap
        tmp=day; day=t_day; t_day=tmp; //swap
    } else {
        printf("%d年%d月%d日から\n", year, month, day);
    }

    /**** 日付が一致するまで count で数え上げる */
    while (t_year!=year || t_month!=month || t_day!=day) {
        count++;
        day++;
		yearnum++;
        /* day,month,yearの繰り上げ処理をする */
        if(day > days[month] + uru(year, month) ){
            day = 1;
            month++;
			printf("year = %d month = %2d uru = %d day = %d yearnum = %d\n", year, month, uru(year, month), days[month]+uru(year, month), yearnum);
			
            if( (month > 12) ){
                day = 1;
                month = 1;
                year++;
				yearnum = 0;
            }
        }
            /**** day がその月の上限(上の☆を参考)を越えたら
            day を 1 にリセット、month を 1 増やす */
                /**** month が 12 を越えたら
                month を 1 にリセット、year を 1 増やす */
    }
    printf(" %d 日です。\n", count);
    return 0;
}