#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float x = 2.28; //<--ЗНАЧЕНИЕ ХЭ ПИСАТЬ СЮДА)00)))00))
float beg = 0; //начало интервала
float end = 4; //конец
float intrvl = 1; //длина интервала
int cnt = 3; //кол-во переменных для лагранжа

float f(float x)
{
    return x * x + 2;
}

void output(float tmp, int i, float *x_val, float *y_val)
{
    for (int k = 0; k < cnt; k++) {
        if (k == i)
            continue;
        printf("(%.1f - %.1f)", x, x_val[k]);
    }
    printf("\n");
    for (int k = 0; k < cnt - 1; k++)
        printf("-----------");
    printf(" * %.1f = %.1f\n", y_val[i], tmp * y_val[i]);
    for (int k = 0; k < cnt; k++) {
        if (k == i)
            continue;
        printf("(%.1f - %.1f)", x_val[i], x_val[k]);
    }
    printf("\n");
    printf("\n");
    return;
}

float langrage(float *x_val, float *y_val)
{
    float res = 0;
    for (int i = 0; i < cnt; i++) {
        float tmp = 1;
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
    int point_cnt = floor(fabsf(end - beg) / intrvl) + 1;
    float *x_val = NULL, *y_val = NULL;
    x_val = (float*) malloc(sizeof(float) * point_cnt);
    y_val = (float*) malloc(sizeof(float) * point_cnt);
    float k = beg;
    for (int i = 0; i < point_cnt; i++) {
        x_val[i] = k;
        k += intrvl;
        y_val[i] = f(x_val[i]);
    }
    float answ = langrage(x_val, y_val);
    printf("%.1f ", answ);
    printf("\n");
    return 0;
}
