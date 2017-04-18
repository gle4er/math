#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double beg = 0; //начало интервала
double end = 4; //конец
double intrvl = 1; //длина интервала

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

double* m = NULL;

void printm(double **matrix, int cnt) //вывод матрицы на экран
{
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt + 1; j++)
            if (j == cnt - 1)
                printf("%.3lf | ", matrix[i][j]);
            else
                printf("%.3lf ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void gauss(double **matrix, int cnt)
{
    printm(matrix, cnt);
    for (int j = 0; j < cnt; j++) {
        for (int i = j + 1; i < cnt; i++) {
            double koeff = matrix[i][j] / matrix[j][j];
            for (int k = 0; k < cnt + 1; k++) 
                matrix[i][k] = matrix[i][k] - matrix[j][k] * koeff;
		}
	}
    for (int i = cnt - 1; i >= 0; i--) {
        double tmp = 0;
        for (int j = cnt - 1; j > i; j--) 
            tmp += matrix[i][j] * m[j];
        m[i + 1] = (matrix[i][cnt] - tmp) / matrix[i][i];
    }
}

/*
 *void spline(int point_cnt, double *x_val, double *y_val)
 *{
 *    if (point_cnt < 3) {
 *        fprintf(stderr, "BEPHYTb FIGU\n");
 *        exit(EXIT_FAILURE);
 *    }
 *    double* a = (double*) malloc(sizeof(double) * point_cnt);
 *    b = (double*) malloc(sizeof(double) * point_cnt);
 *    double* delta = (double*) malloc(sizeof(double) * point_cnt);
 *    double* h = (double*) malloc(sizeof(double) * point_cnt);
 *    double** matrix = (double**) malloc(sizeof(double) * 3);
 *
 *    for (int i = 0; i < 3; i++)
 *        matrix[i] = (double*) malloc(sizeof(double) * (point_cnt + 1));
 *
 *    double x3 = 0,
 *           xn = 0;
 *    x3 = x_val[2] - x_val[0];
 *    xn = x_val[point_cnt - 1] - x_val[point_cnt - 3];
 *
 *    for (int i = 0; i < point_cnt - 1; i++) {
 *        a[i] = y_val[i];
 *        h[i] = x_val[i + 1] - x_val[i];
 *        delta[i] = (y_val[i + 1] - y_val[i]) / h[i];
 *        matrix[0][i] = (i > 0) ? h[i] : x3;
 *        matrix[i][point_cnt] = (i > 0) ? 3 * (h[i] * delta[i - 1] + h[i - 1] * delta[i]) : 0;
 *    }
 *    matrix[1][0] = h[0];
 *    matrix[2][0] = h[0];
 *
 *    for (int i = 1; i < point_cnt - 1; i++) {
 *            matrix[1][i] = 2 * (h[i] + h[i - 1]);
 *            matrix[2][i] = h[i];
 *    }
 *    matrix[1][point_cnt - 1] = h[point_cnt - 2];
 *    matrix[2][point_cnt - 1] = xn;
 *    matrix[0][point_cnt - 1] = h[point_cnt - 2];
 *    
 *    
 *    matrix[0][point_cnt] = ((h[0] + 2 * x3) * h[1] * 
 *            delta[0] + pow(h[0], 2) * delta[1]) / x3;
 *
 *    matrix[point_cnt - 1][point_cnt] = (pow(h[point_cnt - 2], 2) * 
 *            delta[point_cnt - 3] + (2 * xn + h[point_cnt - 2]) 
 *            * h[point_cnt - 3] * delta[point_cnt - 2]) / xn;
 *    
 *    gauss(matrix);
 *
 *    m = (double**) malloc(sizeof(double) * 4);
 *    for (int i = 0; i < 4; i++)
 *        m[i] = (double*) malloc(sizeof(double) * point_cnt);
 *    for (int i = 0; i < point_cnt - 1; i++) {
 *        m[i][0] = a[i];
 *        m[i][1] = b[i];
 *        m[i][2] = 2 * (delta[i] - b[i]) 
 *            / h[i] - (b[i + 1] - delta[i]) / h[i];
 *        m[i][3] = (b[i + 1] + b[i] - 2 * delta[i]) / (h[i] * h[i]);
 *    }
 *}
 */

void spline(int point_cnt, double *y_val)
{
     if (point_cnt < 3) {
         fprintf(stderr, "BEPHYTb FIGU\n");
         exit(EXIT_FAILURE);
     }
     int n = point_cnt - 1;
     double **matrix = (double**) malloc(sizeof(double*) * n);
     double *d = (double*) malloc(sizeof(double) * n);
     for (int i = 0; i <= n; i++) {
         if (i != n)
            matrix[i] = (double*) malloc(sizeof(double) * point_cnt);
         if (i == 0)
             continue;
         d[i - 1] = (y_val[i + 1] - y_val[i]) / (intrvl + 1) -
             (y_val[i] - y_val[i - 1]) / intrvl;
     }
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
             if (i == j)
                 matrix[i][j] = 2 * intrvl / 3;
             if (j == i + 1)
                 matrix[i][j] = (intrvl + 1) / 6;
             if (j == i - 1)
                 matrix[i][j] = intrvl / 6;
             if (abs(i - j) > 1)
                 matrix[i][j] = 0;
         }
         matrix[i][n] = d[i];
     }
     m = (double*) calloc(sizeof(double), point_cnt);
     gauss(matrix, n);
}

double interpolate(double x, double *x_val, double *y_val)
{
	int i;
    for (i = 1; x_val[i] < x; i++);
	return m[i - 1] * pow(x_val[i] - x, 3) / (6 * intrvl) +
        (y_val[i - 1] - (m[i - 1] * pow(intrvl, 2) / 6)) * (x_val[i] - x) / intrvl +
         (y_val[i] - (m[i] * pow(intrvl, 2) / 6)) * (x - x_val[i - 1]) / intrvl;
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
	spline(point_cnt, y_val);
    for (int i = 0; i < point_cnt; i++) {
        double x = beg + intrvl / 2 * i;
        printf("x = %.2lf\t", x);
        printf("S(x) = %.2lf\t", interpolate(x, x_val, y_val));
        printf("f(x) = %.2lf\n", f(x));
    }
	return 0;
}
