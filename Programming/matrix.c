#include <stdio.h>
#include <math.h>

#define N 3
#define M 3
int A[N][M];
int isprime(int number)
{
    if (number <= 1)
    {
        return 0;
    }
    else if (number > 2 && number % 2 == 0)
    {
        return 0;
    }
    if (number > 1)
    {

        for (int i = 3; i < (int)sqrt(number) + 1; i += 2)
        {
            if (number % i == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void solve(int *mas)
{
    int max = -1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (isprime(A[i][j]) && A[i][j] >= max)
            {
                max = A[i][j];
                mas[0] = i;
                mas[1] = j;
            }
        }
    }
}

int main()
{
    int res[2];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
    int *r = res;
    solve(r);
    for(int i = 0; i < 2; i++){
        printf("%d ", res[i]);
    }
    
    return 0;
}
