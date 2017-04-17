#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double beg = 2; //начало интервала
double end = 8; //конец
double intrvl = 1; //длина интервала

double f(double x)
{
    return x * x;
}

void tabl(double *x_val, double *y_val, int point_cnt)
{
    printf("x\t");
    for (int i = 0; i < point_cnt; i++)
        printf("%.2lf\t", x_val[i]);
    printf("h = %.2lf\ny\t", intrvl);
    for (int i = 0; i < point_cnt; i++)
        printf("%.2lf\t", y_val[i]);
}

double fact(double val)
{
    int res = 1;
    for (int i = 1; i < val; i++)
        res *= (i + 1);
    return res;
}

double newton(int point_cnt, double *x_val, double *y_val, double x)
{
    double res = y_val[0],
            ys[point_cnt];
    for (int i = 0; i < point_cnt; i++)
        ys[i] = y_val[i];
    for (int i = point_cnt - 1, j = 0; i > 0; i--, j++) {
        for (int k = 0; k < i; k++) {
            ys[k] = ys[k + 1] - ys[k];
        }
        double q = (x - x_val[0]) / intrvl;
        double tmp = q;
        for (int k = 1; k <= j; k++)
            tmp *= (q - k);
        q = tmp;
        res += ys[0] / fact(j + 1) * q;
    }
    printf("P(x) = %.2f\t", res);
    return res;
}

int main()
{
    int point_cnt = floor(fabs(end - beg) / intrvl) + 1;
    double *x_val = NULL, *y_val = NULL;
    x_val = (double*) malloc(sizeof(double) * point_cnt);
    y_val = (double*) malloc(sizeof(double) * point_cnt);
    double k = beg;
    for (int i = 0; i < point_cnt; i++) {
        x_val[i] = k;
        k += intrvl;
        y_val[i] = f(x_val[i]);
    }
    tabl(x_val, y_val, point_cnt);
    printf("\n");
    printf("%d\n", point_cnt);
    for (int i = 0; i < point_cnt; i++) {
        double x = beg + intrvl / 2 * i;
        printf("x = %.2lf\t", x);
        newton(point_cnt, x_val, y_val, x);
        printf("f(x) = %.2lf\n", f(x));
    }
    return 0;
}
