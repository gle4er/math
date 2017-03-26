#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LVL 2

float x = 2.28; //<--ЗНАЧЕНИЕ ХЭ ПИСАТЬ СЮДА)00)))00))

double langrage(float *x_val, float *y_val, int cnt)
{
    float res = 0;
    for (int i = 0; i < cnt + 1; i++) {
        float tmp = 1;
        for (int j = 0; j < cnt + 1; j++) {
            if (i == j)
                continue;
            tmp *= (x - x_val[j]) / (x_val[i] - x_val[j]);
        }
        res += tmp * y_val[i];
    }
    return res;
}

void load(float **x_val, float **y_val, float *intrvl, int *cnt)
{
    FILE *f = fopen("file", "r");
    char tmp = 0;
    while (tmp != '\n') {
        fscanf(f, "%c", &tmp);
        if (tmp == ' ')
            *cnt += 1;
    }
    *cnt += 1;
    float *tmp1 = (float*) malloc(sizeof(float) * *cnt);
    float *tmp2 = (float*) malloc(sizeof(float) * *cnt);
    f = fopen("file", "r");
    for (int i = 0; i < *cnt; i++)
        fscanf(f, "%f", &tmp1[i]);
    *x_val = tmp1;
    for (int i = 0; i < *cnt; i++)
        fscanf(f, "%f", &tmp2[i]);
    *y_val = tmp2;
    fscanf(f, "%f", intrvl);
    fclose(f);
    return;
}

int main()
{
    int cnt = 0;
    float *x_val = NULL, *y_val = NULL, intrvl = 0;
    load(&x_val, &y_val, &intrvl, &cnt);
    float answ = langrage(x_val, y_val, LVL);
    printf("%.2f ", answ);
    printf("\n");
    return 0;
}
