#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ll long long int

char dict[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char *strrev(char *str) // Функция из string.h, добавлена сюда поскольку в linux string.h ее нет. Если на сервере у них винда, то можно убрать
{
    char *p1, *p2;

    if (!str || !*str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

char *translate(ll start, int cc)
{ //Функция, возвращающая указатель на первый символ строки, в которой хранится переведенное значение
    ll start_tmp = abs(start);
    char num[256] = "";
    while (start_tmp > cc)
    {
        int ost = start_tmp % cc;
        char value = dict[ost];
        strncat(num, &value, 1);
        start_tmp = start_tmp / cc;
    }
    char value = dict[start_tmp];
    strncat(num, &value, 1);
    return ("%s", strrev(num));
}

void print_a()
{
    short a = -3812;
    if (a > 0)
    {
        printf("short %d=%s %d\n", a, translate(a, 12), 12);
    }
    else
    {
        printf("short %d=-%s %d\n", a, translate(a, 12), 12);
    }
}
void print_b()
{
    int b = -1940964136;
    if (b > 0)
    {
        printf("int %d=%s %d\n", b, translate(b, 28), 28);
    }
    else
    {
        printf("int %d=-%s %d\n", b, translate(b, 28), 28);
    }
}
void print_c()
{
    unsigned int c = 2370610470;
    if (c > 0)
    {
        printf("unsigned int %u=%s %d\n", c, translate(c, 29), 29);
    }
    else
    {
        printf("unsigned int %u=-%s %d\n", c, translate(c, 29), 29);
    }
}
void print_d()
{
    long d = 1809767856;
    if (d > 0)
    {
        printf("long %ld=%s %d\n", d, translate(d, 33), 33);
    }
    else
    {
        printf("long %ld=-%s %d\n", d, translate(d, 33), 33);
    }
}
void print_e()
{
    unsigned long e = 1855715378;
    if (e > 0)
    {
        printf("unsigned long %u=%s %d\n", e, translate(e, 26), 26);
    }
    else
    {
        printf("unsigned long %u=-%s %d\n", e, translate(e, 26), 26);
    }
}

int main()
{
    print_a();
    print_b();
    print_c();
    print_d();
    print_e();
}