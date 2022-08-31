#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>


double factorial(double n)
{
    if (n == 1.0 || n == 0.0)
    {
        return 1.0;
    }
    else
    {
        return n * factorial(n - 1.0);
    }
}

double result(double i, double x){
    double ch = pow(-1.0, i) * pow(x, (2 * i + 1));
    double zn = factorial((2.0 * i - 1.0)) * factorial(2.0 * i - 2.0);
    double dop = sin(i * (M_PI / 6.0)) * cos(i * (M_PI / 3));
    return (ch/zn * dop);
}

void solve(double x)
{
    double i = 1.0;
    double slag,  eps = 0.001, sum = 0.0, prev = 0.0;
    do
    {
        prev = sum;
        slag = result(i, x);
        printf("i: %f %.15f\n",i ,slag);
        sum += slag;
        i++;
    }while(slag != 0);
    printf("i: %f  %.25f\n", i, sum);
}

int main()
{
    double x;
    scanf("%lf", &x);
    solve(x);
    return 0;
}