#include<stdio.h>
int main(void)
{
    int i, j, n;

    //Repeatedly asks user for input till non-negative integer not exceeding 23 is entered

    do
    {
        printf("Height: ");
        scanf("%d", &n);
    }
    while (n < 0 || n > 23);

    //Prints the pattern

    for (i = 0; i < n; i++)
    {
        for (j = n - i - 1; j > 0; j--)
        printf(" ");

        for(j = 0; j <= i; j++)
        printf("#");

        printf("  ");

        for(j = 0; j <= i; j++)
        printf("#");

        printf("\n");
    }
}