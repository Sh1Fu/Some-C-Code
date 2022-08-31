#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define ull unsigned long long

int find(int len, int ostat, int *ost_mas) // Находим тот момент, когда остаток повториться
{
    for (int i = 0; i < len; i++)
    {
        if (ost_mas[i] == ostat)
        {
            return 1;
        }
    }
    return 0;
}
int check(int delitel)
{
    int ost[50000];
    int *p = ost;
    int tmp = abs(delitel);
    int i = 0;
    int os = 1; // Изначальный остаток 1 т.к. с самого начала мы имеем дело с дробью вида 1/n
    while (!find(i, os, p))
    { //Алгоритм деления в столбик
        ost[i-1] = os;
        os = (os % tmp) * 10;
        i++;
    }

    return i-1;
}
int solve(int n)
{
    if (n == 1)
    {
        return 0;
    }
    if (n % 10 == 0)
    {
        while (n % 2 == 0)
        {
            n = n / 2;
        }
        while (n % 5 == 0)
        {
            n = n / 5;
        }
        if (n == 1)
        {
            return 0;
        }
        return check(n);
    }
    if (n % 2 == 0 || n % 5 == 0)
    {
        if (n % 2 == 0)
        {
            while (n % 2 == 0)
            {
                n = n / 2;
            }
            if (n == 1)
            {
                return 0;
            }
            return check(n);
        }
        if (n % 5 == 0)
        {
            while (n % 5 == 0)
            {
                n = n / 5;
            }
            if (n == 1)
            {
                return 0;
            }
            return check(n);
        }
    }
    else
    {
        return check(n);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", solve(n));
    return 0;
}