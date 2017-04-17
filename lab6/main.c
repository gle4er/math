#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double beg = 0; //начало интервала
double end = 6; //конец
double intrvl = 0.5; //длина интервала

double f(double x)
{
    return sqrt(x);
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

int eitken(int pnt_cnt, double *xs, double *y_val, double x)
{
    double ys[pnt_cnt];
    for (int i = 0; i < pnt_cnt; i++)
        ys[i] = y_val[i];
    for (int i = 1; i < pnt_cnt; i++) {
        for (int j = 0, cnt = 0; (i + j) < pnt_cnt; j += i, cnt++) {
            double tmp = ys[j] * (x - xs[i + j]) - ys[j + 1] * (x - xs[j]);
            tmp /= (xs[j] - xs[i + j]);
            ys[cnt] = tmp;
        }
    }
    printf("P(x) = %.2f\t", ys[0]);
    return 0;
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
        eitken(point_cnt, x_val, y_val, x);
        printf("f(x) = %.2lf\n", f(x));
    }
    return 0;
}
