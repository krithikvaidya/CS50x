#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    int i,j, key_length=0, pt_length;
    if(argc!=2)
    {
        printf("Please enter a valid number of command line arguments!\n");
        return 1;
    }

    for(i=0;i<strlen(argv[1]);i++)
    {
        if(!isalpha(argv[1][i]))
        {
            printf("Enter alphabet only!\n");
            return 1;
        }
        key_length++;
    }

    char pt[10000];
    printf("plaintext: ");
    fgets(pt, sizeof(pt), stdin);

    pt_length = strlen(pt);

    char new_key[pt_length];
    char ct[pt_length];

    for(i=0,j=0;i<pt_length;i++,j++)
    {
        if(j==key_length)
        {
            j=0;
        }
       new_key[i] = tolower(argv[1][j]);

    }
    new_key[pt_length-1] = '\0';

    int a;
    for(i=0,j=0;i<pt_length-1;i++)
    {
        if(isalpha(pt[i]))
        {
            if(islower(pt[i]))
            {
                a = (pt[i] + (new_key[j]-96)) - 1;
                if(a > 122)
                {
                    ct[i] = (a%122) + 96;
                }
                else
                ct[i] = a;
                j++;

            }

            if(isupper(pt[i]))
            {
                a = (pt[i] + (new_key[j]-96)) - 1;
                if(a > 90)
                {
                    ct[i] = (a%90) + 64;
                }
                else
                ct[i] = a;
                j++;
            }
        }
        else
        ct[i] = pt[i];

    }
    ct[i] = '\0';
    printf("ciphertext: ");
    puts(ct);
}