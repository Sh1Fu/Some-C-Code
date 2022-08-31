#include <stdio.h>
#include <limits.h>

#define ll long long int

void solve(ll minimum, ll maximum)
{
    ll tmp = 1125899906842624;
    short max_del = maximum / tmp;
    for (short i = -max_del; i <= max_del; ++i)
    {
        if (minimum <= tmp * i <= maximum)
        {
            printf("%lld", tmp * i);
            if (i < max_del + 1)
            {
                printf(", ");
            }
        }
    }
}

int main()
{
    ll mmin = LLONG_MIN;
    ll mmax = LLONG_MAX;
    solve(mmin, mmax);
    return 0;
}