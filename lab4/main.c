#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cnt = 3;
double a, b, c = 0;
double e = 0.01;
double answer[] = {0.5, 0.5, 0.5};

void printm(double **matrix) //вывод матрицы на экран
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

void str_move(double **matrix, int fr, int to) //перемещение строк (откуда - куда)
{
    double tmp = 0;
    for (int i = 0; i < cnt + 1; i++) {
        tmp = matrix[to][i];
        matrix[to][i] = matrix[fr][i];
        matrix[fr][i] = tmp;
    }
}

void max_move(double **matrix, int i) //модификация
{
    double max[] = {matrix[i][i], (double) i};
    for (int j = i; j < cnt; j++) {
        if (fabs(max[0]) < fabs(matrix[j][i])) {
            max[0] = matrix[j][i];
            max[1] = j;
            }
        }
    str_move(matrix, max[1], i);
}

void gauss(double **matrix, double *answer_gauss)
{
    for (int j = 0; j < cnt; j++) {
        max_move(matrix, j);
        for (int i = j + 1; i < cnt; i++) {
            double koeff = matrix[i][j] / matrix[j][j];
            for (int k = 0; k < cnt + 1; k++) 
                matrix[i][k] = matrix[i][k] - matrix[j][k] * koeff;
		}
	}
    for (int i = cnt - 1; i >= 0; i--) {
        double tmp = 0;
        for (int j = cnt - 1; j > i; j--) 
            tmp += matrix[i][j] * answer_gauss[j];
        answer_gauss[i] = (matrix[i][cnt] - tmp) / matrix[i][i];
    }
    for (int i = 0; i < cnt; i++)
        printf("answ: %.5lf ", answer[i]);
    printf("\n");
    printf("\n");
}

double f1(double x, double y, double z)
{
    return x * x + y * y + z * z - 1;
}

double f2(double x, double y, double z)
{
    return 2 * x * x + y * y - 4 * z;
}

double f3(double x, double y, double z)
{
    return 3 * x * x - 4 * y + z * z;
}

double f1x(double x)
{
    return 2 * x;
}

double f1y(double y)
{
    return 2 * y;
}

double f1z(double z)
{
    return 2 * z;
}

double f2x(double x)
{
    return 4 * x;
}

double f2y(double y)
{
    return 2 * y;
}

double f2z()
{
    return -4;
}

double f3x(double x)
{
    return 6 * x;
}

double f3y()
{
    return -4;
}

double f3z(double z)
{
    return 2 * z;
}

/*
 *double f1(double x, double y)
 *{
 *    return (0.1 * pow(x, 2) + x + 0.2 * pow(y, 2) - 0.3);
 *}
 *
 *double f2(double x, double y)
 *{
 *    return (0.2 * powl(x, 2) + y - 0.1 * x * y - 0.7);
 *}
 *
 *double f1x(double x)
 *{
 *    return (0.2 * x + 1);
 *}
 *
 *double f1y(double y)
 *{
 *    return (0.4 * y);
 *}
 *
 *double f2x(double x, double y)
 *{
 *    return (0.4 * x + 0.1 * y);
 *}
 *
 *double f2y(double x)
 *{
 *    return (1 + 0.1 * x);
 *}
 */

int check(double *prev)
{
    double tmp;
    double curr[cnt];
    for (int i = 0; i < cnt; i++)
        curr[i] = answer[i];
    for (int i = 0; i < cnt; i++)
        curr[i] -= prev[i];
    tmp = fabs(curr[0]);
    for (int i = 1; i < cnt; i++)
        if (fabs(curr[i]) > tmp)
            tmp = fabs(curr[i]);
    return tmp > e;
}

void mmn()
{
    int i = 0;
    double prev[cnt];
    double **w = (double**) malloc(sizeof(double) * cnt);
    for (int j = 0; j < cnt + 1; j++)
        w[j] = (double*) malloc(sizeof(double) * (cnt + 1));
    do {
        i++;
        for (int k = 0; k < cnt; k++)
            prev[k] = answer[k];
        double f[] = {-f1(answer[0], answer[1], answer[2]),
            -f2(answer[0], answer[1], answer[2]), 
            -f3(answer[0], answer[1], answer[2])};
        w[0][0] = f1x(answer[0]);
        w[0][1] = f1y(answer[1]);
        w[0][2] = f1z(answer[2]);
        w[0][3] = f[0];
        w[1][0] = f2x(answer[0]);
        w[1][1] = f2y(answer[1]);
        w[1][2] = f2z();
        w[1][3] = f[1];
        w[2][0] = f3x(answer[0]);
        w[2][1] = f3y();
        w[2][2] = f3z(answer[2]);
        w[2][3] = f[2];
        double tmp[cnt];
        for (int k = 0; k < cnt; k++)
            tmp[k] = 0;
        gauss(w, tmp);
        for (int k = 0; k < cnt; k++)
            answer[k] = prev[k] + tmp[k];
    } while(check(prev));
    printf("steps: %d\n", i);
}

int main()
{
    mmn();
    return 0;
}
