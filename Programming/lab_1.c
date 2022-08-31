#include <stdio.h>

void solve_string()
{
    for (int i = 0; i < 5; ++i)
    {
        if (i % 2 == 0)
        {
            printf("  #    #  \n");
        }
        else
        {
            printf("##########\n");
        }
    }
}
void solve2()
{
    printf("\\         /\n");
    printf(" \\       /\n");
    printf("  \\     /\n");
    printf("   \\---/\n");
    printf("      /\n");
    printf("     /\n");
    printf("    /\n");
    printf("   /\n");
}

int main()
{
    solve_string();
    solve2();
    return 0;
}