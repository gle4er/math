#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double beg = 1; //начало интервала
double end = 4; //конец
double intrvl = 0.5; //длина интервала
int cnt = 3; //кол-во переменных для лагранжа

void tabl(double *x_val, double *y_val, int point_cnt)
{
    printf("x\t");
    for (int i = 0; i < point_cnt; i++)
        printf("%.2lf\t", x_val[i]);
    printf("h = %.2lf\ny\t", intrvl);
    for (int i = 0; i < point_cnt; i++)
        printf("%.2lf\t", y_val[i]);
}

double f(double x)
{
    return x * x;
}

void output(double tmp, int i, double *x_val, double *y_val, double x) //красивый вывод расчёта многочленов ланграге
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

double langrage(double *xs, double *ys, double x, int point_cnt)
{
    double res = 0;
    double x_val[cnt],
            y_val[cnt];
    int mda;
    for (mda = 0; mda < point_cnt; mda++) 
        if (xs[mda] >= x)
            break;
    if (mda == 0) {
        for (int i = 0; i < cnt; i++) {
            x_val[i] = xs[i + 1];
            y_val[i] = f(x_val[i]);
        }
    } else if (mda == point_cnt) {
        for (int i = 0; i < cnt; i++) {
            x_val[i] = xs[mda - 1 - i];
            y_val[i] = f(x_val[i]);
        }
    } else {
        for (int i = 0; i < cnt; i++) {
            x_val[i] = xs[mda + i * (int)pow(-1, i)];
            y_val[i] = f(x_val[i]);
        }
    }
    for (int i = 0; i < cnt; i++) {
        double tmp = 1;
        for (int j = 0; j < cnt; j++) {
            if (i == j)
                continue;
            tmp *= (x - x_val[j]) / (x_val[i] - x_val[j]);
        }
        res += tmp * y_val[i];
        printf("L%d(x) = %.2lf\t", i + 1, res);
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
    tabl(x_val, y_val, point_cnt);
    printf("\n");
    for (int i = 0; i < point_cnt; i++) {
        double x = beg + intrvl / 2 * i;
        printf("x = %.2lf\t", x);
        langrage(x_val, y_val, x, point_cnt);
        printf("f(x) = %.2lf\n", f(x));
    }
    return 0;
}
