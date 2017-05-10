#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double beg = 0.6; //начало интервала
double end = 1.21; //конец
double intrvl = 0.2; //длина интервала

double *x_val = NULL;
double *y_val = NULL;

double f(double x)
{
    return cbrt(x);
}

void tabl(int point_cnt)
{
    printf("x\t");
    for (int i = 0; i < point_cnt; i++)
        printf("%.2lf\t", x_val[i]);
    printf("h = %.2lf\ny\t", intrvl);
    for (int i = 0; i < point_cnt; i++)
        printf("%.2lf\t", y_val[i]);
}

double eitken(int n, int m, double x)
{
    if (m == n)
        return y_val[n];
    return ((x - x_val[n]) * eitken(n + 1, m, x) - 
            (x - x_val[m]) * eitken(n, m - 1, x)) /
            (x_val[m] - x_val[n]);
    return 0;
}

int main()
{
    int point_cnt = floor(fabs(end - beg) / intrvl) + 1;
    x_val = (double*) malloc(sizeof(double) * point_cnt);
    y_val = (double*) malloc(sizeof(double) * point_cnt);
    double k = beg;
    for (int i = 0; i < point_cnt; i++) {
        x_val[i] = k;
        k += intrvl;
        y_val[i] = f(x_val[i]);
    }
    tabl(point_cnt);
    printf("\n");
    printf("%d\n", point_cnt);
    for (int i = 0; i < point_cnt * 2 - 1; i++) {
        double x = beg + intrvl / 2 * i;
        printf("x = %.2lf\t", x);
        double answ = eitken(0, point_cnt - 1, x);
        printf("p(x) = %lf\t f(x) = %lf\n", answ, f(x));
    }
    return 0;
}
