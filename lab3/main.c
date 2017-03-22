#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define MPD
//#define MX
#define MN

double a, b, c = 0;
double e = 0.001;
double intrvl = 0.5;

double f(double x)
{
    return x * x - 1;
}

double f1(double x)
{
    return 2 * x;
}

void mpd()
{
    int i;
    for (i = 0; fabs(b - a) > e && f(c) != 0; i++) {
        c = (a + b) / 2;
        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
    }
    printf("steps: %d\n", i);
}

void mx()
{
    double tmp = 0;
    int i, flg = 0;
    for (i = 0; (fabs(c - tmp) > e || !flg) && f(c) != 0; i++) {
        flg++;
        tmp = c;
        c = a - f(a) * (b - a) / (f(b) - f(a));
        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
    } 
    printf("steps: %d\n", i);
}

void mn()
{
    double tmp = a;
    int j;
    c = (-1) * (f(tmp) / f1(tmp)) + tmp;
    for (j = 0; f(c) != 0 && fabs(c - tmp) > e; j++) {
        tmp = c;
        c = tmp - (f(tmp) / f1(tmp));
    } 
    printf("steps: %d\n", j);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usg: %s a b\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (b < a) {
        fprintf(stderr, "BEPHYTb FUGY\n");
        exit(EXIT_FAILURE);
    }
    a = atoi(argv[1]);
    b = atoi(argv[2]);
#ifdef MPD
    mpd();
#endif
#ifdef MX
    mx();
#endif
#ifdef MN
    mn();
#endif
    printf("answ: %.2lf\n", c);
    return 0;
}
