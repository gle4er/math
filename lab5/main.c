#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LVL 2

double langrage(double *x_val, double *y_val, double x, int cnt)
{
    double res = 0;
    for (int i = 0; i < cnt + 1; i++) {
        double tmp = 1;
        for (int j = 0; j < cnt + 1; j++) {
            if (i == j)
                continue;
            tmp *= (x - x_val[j]) / (x_val[i] - x_val[j]);
        }
        res += tmp * y_val[i];
    }
    return res;
}

void load(double **x_val, double **y_val, double *intrvl, int *cnt)
{
    FILE *f = fopen("file", "r");
    char tmp = 0;
    while (tmp != '\n') {
        fscanf(f, "%c", &tmp);
        if (tmp == ' ')
            *cnt += 1;
    }
    *cnt += 1;
    double *tmp1 = (double*) malloc(sizeof(double) * *cnt);
    double *tmp2 = (double*) malloc(sizeof(double) * *cnt);
    f = fopen("file", "r");
    for (int i = 0; i < *cnt; i++)
        fscanf(f, "%lf", &tmp1[i]);
    *x_val = tmp1;
    for (int i = 0; i < *cnt; i++)
        fscanf(f, "%lf", &tmp2[i]);
    *y_val = tmp2;
    fscanf(f, "%lf", intrvl);
    fclose(f);
    return;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usg: %s x_begin x_end\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int cnt = 0;
    double *x_val = NULL, *y_val = NULL, *answ = NULL, intrvl = 0;
    load(&x_val, &y_val, &intrvl, &cnt);
    int beg = atoi(argv[1]);
    int end = atoi(argv[2]);
    int cnt_points = floor(abs(end - beg) / intrvl) + 1;
    answ = (double*) malloc(sizeof(double) * cnt_points);
    int k = 0;
    for (double i = beg; k < cnt_points; i += intrvl, k++) 
        answ[k] = langrage(x_val, y_val, i, LVL);
    for (int i = 0; i < cnt_points; i++)
        printf("%.2lf ", answ[i]);
    printf("\n");
    return 0;
}
