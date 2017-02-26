#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSYL 0.001

int cnt = 0; //длина матрицы
double **matrix = 0;
double *answer = 0;
double *answer_tmp = 0;

void check()
{
    int flg = 0;
    for (int i = 0; i < cnt; i++) {
        for (int j = i + 1; j < cnt; j++) {
            double koeff = matrix[i][0] / matrix[j][0];
            for (int k = 0; k < cnt + 1; k++) 
                if (matrix[i][k] / matrix[j][k] == koeff)
                    flg++;
            if (flg == cnt + 1) {
                fprintf(stderr, "this matrix is virojdennaya\n");
                exit(EXIT_FAILURE);
            } else
                flg = 0;
        }
    }
}

void printm() //вывод матрицы на экран
{
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt + 1; j++)
            if (j == cnt - 1)
                printf("%.1lf | ", matrix[i][j]);
            else
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
    answer_tmp = (double*) malloc(sizeof(double) * cnt);
    return;
}

int calculating()
{
    double max = 0, tmp, N = 0;
    for (int i = 0; i < cnt; i++) {
        tmp = 0;
        for (int j = 0; j < cnt; j++) {
            if (matrix[i][j] < 0)
                matrix[i][j] *= -1;
            tmp += matrix[i][j];
        }
        if (tmp > max)
            max = tmp;
    }
    tmp = 0;
    for (int i = 0; i < cnt; i++) {
        if (matrix[i][3] < 0)
            matrix[i][3] *= -1;
        if (matrix[i][3] > tmp)
            tmp = matrix[i][3];
    }
    N = (double) EPSYL * (1 - max) / tmp;
    N = log(N);
    N /= log(max);
    N += 1;
    return floor(N);
}

void mpi()
{
    for (int i = 0; i < cnt; i++) {
        double koeff = matrix[i][i];
        for (int j = 0; j < cnt + 1; j++) {
            if (i == j)
                matrix[i][i] = 0;
            matrix[i][j] /= koeff;
        }
    }
    int N = calculating();
    printf("%d waroB\n", N);
}

int main()
{
    load();
    printm();
    check();
    mpi();
    for (int i = 0; i < cnt; i++)
        printf("x%d = %.1lf; ", i + 1, answer[i]);
    printf("\n");
    return 0;
}
