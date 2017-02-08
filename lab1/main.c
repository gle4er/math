#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cnt = 0; //длина матрицы
double **matrix = 0;
double *answer = 0;

void printm() //вывод матрицы на экран
{
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt + 1; j++)
            printf("%.1lf ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void str_move(int fr, int to) //перемещение строк (откуда - куда)
{
    double tmp = 0;
    for (int i = 0; i < cnt + 1; i++) {
        tmp = matrix[to][i];
        matrix[to][i] = matrix[fr][i];
        matrix[fr][i] = tmp;
    }
}

void max_move(int i) //модификация
{
    double max[] = {matrix[i][i], (double) i};
    for (int j = i; j < cnt; j++) {
        if (abs(max[0]) < abs(matrix[j][i])) {
            max[0] = matrix[j][i];
            max[1] = j;
            }
        }
    str_move(max[1], i);
}

void calc(int mda)
{
    double tmp = 0;
    for (int i = cnt - 1; i > mda; i--) 
        tmp += matrix[mda][i] * answer[i];
    answer[mda] = (matrix[mda][cnt] - tmp) / matrix[mda][mda];
}

void load() //загрузка матрицы с файла
{
    FILE *file = fopen("./file", "r");
    char tmp = 0;
    while (tmp != '\n') {
        fscanf(file, "%c", &tmp);
        if (tmp == ' ')
            cnt++;
    }
    matrix = (double**) malloc(sizeof(double) * cnt);
    for (int i = 0; i < cnt; i++)
        matrix[i] = (double*) malloc(sizeof(double) * (cnt + 1));
    file = fopen("./file", "r");
    for (int i = 0; i < cnt; i++)
        for (int j = 0; j < cnt + 1; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    answer = (double*) malloc(sizeof(double) * cnt);
    return;
}

void gauss_forward()
{
    for (int j = 0; j < cnt; j++) {
        max_move(j);
        for (int i = j + 1; i < cnt; i++) {
            double koeff = matrix[i][j] / matrix[j][j];
            for (int k = 0; k < cnt + 1; k++) 
                matrix[i][k] = matrix[i][k] - matrix[j][k] * koeff;
        }
    }
}

void gauss_backward()
{
    answer[cnt - 1] = matrix[cnt - 1][cnt] / matrix[cnt - 1][cnt - 1];
    for (int i = cnt - 2; i >= 0; i--) 
        calc(i);
}

int main()
{
    load();
    printm();
    gauss_forward();
    gauss_backward();
    for (int i = 0; i < cnt; i++)
        printf("x%d = %.1lf; ", i + 1, answer[i]);
    printf("\n");
    return 0;
}
