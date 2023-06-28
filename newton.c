#include <stdio.h>
#include <math.h>

int main(void){

    double x = 1.0; //x0
    double f0 = 2.0 * pow(x,3) - 8.0 * pow(x,2) - 3.0 * x - 10.0; //f 원함수
    double f1 = 6.0 * pow(x,2) - 16.0 * x - 3.0; // f 도함수
    double xold = x;
    double xnew = x - f0 / f1;

    double e = fabs(xnew - xold); //상대오차

    while( e >= 1.0 * pow(10, -6) ){ //상대오차가 0.000001보다 작을경우 반복
        xold = xnew;

        f0 = 2.0 * pow(xold,3) - 8.0 * pow(xold,2) - 3.0 * xold - 10.0; // f(x new)
        f1 = 6 * pow(xold,2) - 16 * xold - 3.0; //f'(x new)

        xnew = xold - f0 / f1; // x(new)

        e = fabs(xnew - xold);
    }

    printf("x = %f (근사치)\n", xnew);
    printf("f(xnew) = %f\n", 2*xnew*xnew*xnew - 8*xnew*xnew - 3*xnew - 10);


}