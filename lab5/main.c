#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double beg = -4; //начало интервала
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
    return sin(x);
}

double langrage(double *xs, double x, int point_cnt)
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
            x_val[i] = xs[i];
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

    for (int i = 0; i < cnt - 1; i++) {
        double tmp = 1;
        for (int j = 0; j < cnt; j++) {
            if (i == j)
                continue;
            tmp *= (x - x_val[j]) / (x_val[i] - x_val[j]);
        }
        res += tmp * y_val[i];
        printf("L%d(x) = %.6lf\t", i + 1, res);
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
    FILE *out = fopen("data", "w");
    fprintf(out, "%d\n", point_cnt * 2 - 2);
    for (double x = x_val[0]; x < x_val[point_cnt - 1]; x += intrvl / 2) {
        printf("x = %.2lf\t", x);
        fprintf(out, "%lf ", x);
        double answ = langrage(x_val, x, point_cnt);
        fprintf(out, "%lf ", answ);
        printf("f(x) = %.2lf\n", f(x));
        fprintf(out, "%lf\n", f(x));
    }
    return 0;
}
