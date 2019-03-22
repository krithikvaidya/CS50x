#include<stdio.h>
#include<cs50.h>

int main(void)
{
    long long num = get_long_long("Number: "), num2 = num, num3 = num;
    int ctr = 0, sum = 0, prod, i, start = 0;

    while (num2 > 0)
    {

        if (num2/100 == 0 && num2/10 != 0)
            start += num2%10;
        else if(num2/10 == 0)
            start += num2%10 * 10;

        ctr++;
        num2 /= 10;
    }

    if (ctr == 13 || ctr == 15 || ctr == 16)
    {
        for (i = 0; i < ctr; i++)
        {
            if (i % 2 == 1)
            {
                prod = num % 10 * 2;
                while (prod > 0)
                {
                    sum += prod % 10;
                    prod /= 10;
                }
            }
            num /= 10;
        }

        for (i = 0; i < ctr; i++)
        {

            if (i % 2 == 0)
                sum += num3 % 10;

            num3 /= 10;

        }
        if (sum % 10 == 0)
        {

            if(ctr == 15 && (start == 34 || start == 37))
                printf("AMEX\n");

            else if(ctr == 16 && (start == 51 || start == 52 || start == 53 || start == 54 || start == 55))
                printf("MASTERCARD\n");

            else if((ctr == 13 || ctr == 16) && (start/10 == 4))
                printf("VISA\n");

            else
                printf("INVALID\n");
        }

        else
            printf("INVALID\n");
    }

    else
        printf("INVALID\n");

    return 0;
}