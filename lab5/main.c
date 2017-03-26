#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double x = 2.28; //<--ЗНАЧЕНИЕ ХЭ ПИСАТЬ СЮДА)00)))00))
double beg = 0; //начало интервала
double end = 4; //конец
double intrvl = 1; //длина интервала
int cnt = 3; //кол-во переменных для лагранжа

double f(double x)
{
    return x * x + 2;
}

void output(double tmp, int i, double *x_val, double *y_val)
{
    for (int k = 0; k < cnt; k++) {
        if (k == i)
            continue;
        printf("(%.3lf - %.3lf)", x, x_val[k]);
    }
    printf("\n");
    for (int k = 0; k < cnt - 1; k++)
        printf("---------------");
    printf(" * %.3lf = %.3lf\n", y_val[i], tmp * y_val[i]);
    for (int k = 0; k < cnt; k++) {
        if (k == i)
            continue;
        printf("(%.3lf - %.3lf)", x_val[i], x_val[k]);
    }
    printf("\n");
    printf("\n");
    return;
}

double langrage(double *x_val, double *y_val)
{
    double res = 0;
    for (int i = 0; i < cnt; i++) {
        double tmp = 1;
        for (int j = 0; j < cnt; j++) {
            if (i == j)
                continue;
            tmp *= (x - x_val[j]) / (x_val[i] - x_val[j]);
        }
        res += tmp * y_val[i];
        output(tmp, i, x_val, y_val);
    }
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
    double answ = langrage(x_val, y_val);
    printf("%.3lf ", answ);
    printf("\n");
    return 0;
}
