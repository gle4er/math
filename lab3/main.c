#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MPD
//#define MX
//#define MN

double a, b, c = 0;
double e = 0.001;
double intrvl = 0.5;

double f(double x)
{
    return x * x + 2 * x - 3;
}

double f1(double x)
{
    return 2 * x + 2;
}

void mpd()
{
    while (fabs(b - a) > e || f(c) != 0) {
        c = (a + b) / 2;
        if (f(c) == 0)
            break;
        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
    }
}

void mx()
{
    double tmp = 0;
    while (fabs(c - tmp) > e || f(c) != 0) {
        tmp = c;
        c = a - f(a) * (b - a) / (f(b) - f(a));
        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
    } 
}

void mn()
{
    double tmp = a;
    for (double i = a; i <= b; i += intrvl)
        if (fabs(f(tmp)) > fabs(f(i)))
            tmp = i;
    c = (-1) * (f(tmp) / f1(tmp)) + tmp;
    while (f(c) != 0 || fabs(c - tmp) > e) {
        tmp = c;
        c = tmp - (f(tmp) / f1(tmp));
    } 
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
