#include <stdio.h>
#include <stdlib.h>

void solve()
{
    int a[10] = {};
    int tmp = 0;
    for (int i = 0; i < 10; i++)
    {
        a[i] = rand();
        printf("%d ", a[i]);
        if (i == 9)
        {
            printf("\n");
        }
    }
    for (int k = 0; k < 10; k++)
    {
        for (int j = k + 1; j < 10; j++)
        {
            if (a[k] > a[j])
            {
                tmp = a[k];
                a[k] = a[j];
                a[j] = tmp;
            }
        }
    }
    printf("Mins: %d %d", a[0], a[1]);
}

int main()
{
    solve();
}