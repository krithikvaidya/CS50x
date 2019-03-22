#include<crypt.h> //for crypt() function
#include<stdio.h> //for basic i/o functions
#include<string.h> //for strcmp

int main(int argc, char *argv[])
{

    //Checks if only one command line argument has has been entered

    if (argc != 2)
    {
        printf("Usage: ./crack <hash>\n");
        return 1;
    }

    //Initialising loop control variables

    int i, j, k, l, m;

    //Declaring a character array containing all lowercase and uppercase alphabet

    char alphabet[52];

    //Assigning values to alphabet array(first capital letters, then small)

    for (i = 0; i < 52; i++)
    {
        if (i < 26)
        {
            alphabet[i] = i + 65;
        }

        else
        {
            alphabet[i] = (i - 26) + 97;
        }
    }

    //Initializes and gives the value to salt

    char salt[2];
    salt[0] = argv[1][0];
    salt[1] = argv[1][1];

    //Decrypting the hash

    //Checking if the key is a single character

    for (i = 0; i < 52; i++)
    {
        char a[2];
        a[0] = alphabet[i];

        if (strcmp(crypt(a, salt), argv[1]) == 0)
        {
            printf("%s\n", a);
            goto end;
        }
    }

    //Checking if the key is two character

    for (i = 0; i < 52; i++)
    {
        char a[3];
        a[0] = alphabet[i];

        for (j = 0; j < 52; j++)
        {
            a[1] = alphabet[j];
            if (strcmp(crypt(a, salt), argv[1]) == 0)
            {

                printf("%s\n", a);
                goto end;

            }

        }
    }

    //Checking if the key is three character

    for (i = 0; i < 52; i++)
    {
        char a[4];
        a[0] = alphabet[i];

        for (j = 0; j < 52; j++)
        {
            a[1] = alphabet[j];
            for (k = 0; k < 52; k++)
            {
                a[2] = alphabet[k];
                if (strcmp(crypt(a, salt), argv[1]) == 0)
                {
                    printf("%s\n", a);
                    goto end;
                }
            }
        }
    }

    //Checks for four characters
    for (i = 0; i < 52; i++)
    {
        char a[5];
        a[0] = alphabet[i];

        for (j = 0; j < 52; j++)
        {
            a[1] = alphabet[j];
            for (k = 0; k < 52; k++)
            {
                a[2] = alphabet[k];
                for (l = 0; l < 52; l++)
                {
                    a[3] = alphabet[l];
                    if (strcmp(crypt(a, salt), argv[1]) == 0)
                    {
                        printf("%s\n", a);
                        goto end;
                    }
                }
            }
        }
    }
    //Checks for five characters

    for (i = 0; i < 52; i++)
    {
        char a[5];
        a[0] = alphabet[i];

        for (j = 0; j < 52; j++)
        {
            a[1] = alphabet[j];
            for (k = 0; k < 52; k++)
            {
                a[2] = alphabet[k];
                for (l = 0; l < 52; l++)
                {
                    a[3] = alphabet[l];
                    for (m = 0; m < 52; m++)
                    {
                        a[4] = alphabet[m];
                        if (strcmp(crypt(a, salt), argv[1]) == 0)
                        {
                            printf("%s\n", a);
                            goto end;
                        }
                    }
                }
            }
        }
    }

end:
    return 0;
}