#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    double x[] = {-2.00, -1.75, -1.50, -1.25, -1.00, -0.75, -0.50, -0.25, 0.00, 0.25, 0.50, 0.75, 1.00, 1.25, 1.50, 1.75, 2.00};
    double y[] = {0.757, 1.058, 0.724, -0.147, 0.128, 0.149, 0.156, -0.552, -0.030, -0.824, -1.213, -1.368, -1.486, -1.560, -1.291, -1.709, -2.023};
    int i;
    int n = 16;
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, x1y1 = 0.0;
    double a, b;

    for(i = 0; i <= n; i++){
        x1 += x[i];
        y1 += y[i];
        x2 += x[i]*x[i];
        x1y1 += x[i]*y[i];
    }

    a = (x1 * y1 - n*x1y1) / (x1*x1 - x2*n);
    b = (x1*x1y1 - x2*y1) / (x1*x1 - x2*n);



    printf("%lu  %lu\n", sizeof(y), sizeof(x));
    for(i = 0; i <= n; i++){
        printf("%f  %f\n", y[i], x[i]);
    }

    printf("\n y = %fx + %f\n", a, b);


}