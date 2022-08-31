#include <stdio.h>
void char_solve()
{
    unsigned char a;
    int tmp = 2, i = 0;
    do
    {
        a = tmp;
        tmp *= 2;
        i += 1;

    } while (a != 0);
    printf("char lenght: %d byte\n", i / 8);
}
void short_solve()
{
    unsigned short a;
    int tmp = 2, i = 0;
    do
    {
        a = tmp;
        tmp *= 2;
        i += 1;

    } while (a != 0);
    printf("short lenght: %d bytes\n", i / 8);
}
void int_solve()
{
    unsigned int a;
    int tmp = 2, i = 0;
    do
    {
        a = tmp;
        tmp *= 2;
        i += 1;

    } while (a != 0);
    printf("int lenght: %d bytes\n", i / 8);
}
void long_solve()
{
    unsigned long int a;
    int tmp = 2, i = 0;
    do
    {
        a = tmp;
        tmp *= 2;
        i += 1;

    } while (a != 0);
    printf("long lenght: %d bytes\n", i / 8);
}
void llong_solve()
{
    unsigned long long int b;
    long long int tmp = 2, i = 0;
    do
    {
        b = tmp;
        tmp *= 2;
        i += 1;

    } while (b != 0);
    printf("long long lenght: %d bytes\n", i / 8);
}
void char_values()
{
    printf("char values: ");
    char i = -128;
    do
    {
        printf("%d ", i);
        i++;
    } while (i != 128);
}

int main()
{
    char_solve();
    short_solve();
    int_solve();
    long_solve();
    llong_solve();
    char_values();
}