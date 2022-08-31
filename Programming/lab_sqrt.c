#include <stdio.h>
#include <math.h>

#define ull unsigned long long

int check(ull number)
{
    ull rd = (ull)sqrt((double)number);
    for (ull i = rd; i <= rd + 10; i++)
    {
        if (i * i == number)
        {
            return 1;
        }
    }
    return 0;
}

int solve(int n, ull *nums)
{
    ull max = 0;
    for (int i = 0; i < n; i++)
    {
        if (check(nums[i]) == 1 && nums[i] >= max)
        {
            max = nums[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (nums[i] == max)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    int n;
    scanf("%d", &n);
    ull a[20];
    for (int i = 0; i < n; i++)
    {
        scanf("%llu", &a[i]);
    }
    ull *b = a;

    printf("%d", solve(n, &a));
    return 0;
}