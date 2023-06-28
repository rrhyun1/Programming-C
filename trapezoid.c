#include <stdio.h>
#include <math.h>
#define EPS 1.0e-10

double integrand(double x);
double trapezoid(double Tk, int k, double a, double b);

int main(void)
{
    int k;
    double Tk; //T0를 구하기 위해 변수선언
    double Tkold; //Tk+1 과 Tk를 구분하기 위해 이전 값 저장
    double err;
    double a = 0.0, b = 1.0; //a, b를 1과 0으로 선언
    Tk = (b - a) * ( integrand(a) + integrand(b) ) / 2; //T0


    printf(" k     Tk     Tk+1        err     \n");
    for(k = 1; 1; k++){
        Tkold = Tk;
        Tk = trapezoid(Tk, k, a, b);
        err = fabs( (Tk - Tkold) / Tkold );

        printf("%2d %f %f %.6fe-02\n", k - 1 , Tkold, Tk, err * 100);

        if(err <= EPS){
            break;
        }
    }
}

double integrand(double x){
    double y;
    y = 4 / (1 + x * x);
    return y;
}

double trapezoid(double Tk, int k, double a, double b){
    int i; //loop number
    double y = 0.0; //f(x) 들의 합
    double h = (b - a) / pow(2, k);

    for(i = 0; i < pow(2, k - 1); i++){
        y += integrand(a + (2 * i + 1) * h );
    }

    Tk = Tk / 2 + h * y; // T(k+1) 를 T(k)를 이용해 구함

    return Tk;
}