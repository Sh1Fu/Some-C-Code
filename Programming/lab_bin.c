#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char dict[2] = {'0', '1'};
char res[33] = "";

char *strrev(char *str) // Функция из string.h, добавлена сюда поскольку в linux string.h ее нет. Если на сервере она есть, то можно убрать
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

void solve(signed long long int a)
{
    short ost, cc = 2;
    signed long long int tmp = abs(a);
    char value;
    while (tmp >= cc - 1)
    {
        ost = tmp % cc;
        if (a > 0)
        {
            value = dict[ost];
        }
        if (a < 0)
        {
            value = dict[ost ^ 1];
        }
        strncat(res, &value, 1);
        tmp = tmp / cc;
    }
    if (a == 0)
    {
        printf("%s\n", "0");
    }
    if (a > 0)
    {
        printf("%s\n", strrev(res));
    }
    if (a < 0)
    {
        for (int i = strlen(res); i < 32; i++)
        {
            printf("1");
        }
        for (int j = 0; j < strlen(res); j++)
        {
            if (res[j] == '0')
            {
                res[j] = '1';
                break;
            }
            if (res[j] == '1')
            {
                res[j] = '0';
            }
        }
        printf("%s\n", strrev(res));
    }
}

int main()
{
    signed long long int start;
    scanf("%lld", &start);
    solve(start);
    return 0;
}