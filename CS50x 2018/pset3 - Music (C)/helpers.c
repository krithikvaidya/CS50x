// Helper functions for music

#include <cs50.h>
#include <string.h>
#include "helpers.h"
#include <math.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int num = atoi(&fraction[0]);
    int den = atoi(&fraction[2]);

    float mult_factor = (8.0/den);
    num*=mult_factor;

    return (int)num;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int n=0, temp;
    char ch = note[0], ch2 = note[1], ch3 = note[2];

    if(ch3 == '\0')
    {
        temp = (atoi(&note[1]) - 4);
        if(ch == 'A')
            n = ((atoi(&note[1]) - 4)) * 12;

        else if(ch == 'B')
            n = ((atoi(&note[1]) - 4)) * 12 + 2;

        else if(ch == 'G')
        {
            if(temp<0)
            n = -(abs((atoi(&note[1]) - 4)) * 12 + 2);
            else
            n = (abs((atoi(&note[1]) - 4)) * 12 - 2);

        }

        else if(ch == 'F')
        {
            if(temp<0)
            n = -(abs((atoi(&note[1]) - 4)) * 12 + 4);
            else
            n = (abs((atoi(&note[1]) - 4)) * 12 - 4);

        }

        else if(ch == 'E')
        {
            if(temp<0)
            n = -(abs((atoi(&note[1]) - 4)) * 12 + 5);
            else
            n = (abs((atoi(&note[1]) - 4)) * 12 - 5);

        }

        else if(ch == 'D')
        {
            if(temp<0)
            n = -(abs((atoi(&note[1]) - 4)) * 12 + 7);
            else
            n = (abs((atoi(&note[1]) - 4)) * 12 - 7);

        }

        else if(ch == 'C')
        {
            if(temp<0)
            n = -(abs((atoi(&note[1]) - 4)) * 12 + 9);
            else
            n = (abs((atoi(&note[1]) - 4)) * 12 - 9);

        }
    }

    else
    {
        if(ch2 == '#')
        {
            temp = atoi(&note[2]) - 4;
            if(ch == 'A')
                n = ((atoi(&note[2]) - 4)) * 12 + 1;
            else if(ch == 'G')
            {
                if(temp<0)
                n = -(abs((atoi(&note[2]) - 4)) * 12 + 1);
                else
                n = (abs((atoi(&note[2]) - 4)) * 12 - 1);
            }
            else if(ch == 'F')
            {
                if(temp<0)
                n = -(abs((atoi(&note[2]) - 4)) * 12 + 3);
                else
                n = (abs((atoi(&note[2]) - 4)) * 12 - 3);
            }
            else if(ch == 'D')
            {
                if(temp<0)
                n = -(abs((atoi(&note[2]) - 4)) * 12 + 6);
                else
                n = (abs((atoi(&note[2]) - 4)) * 12 - 6);
            }
            else if(ch == 'C')
            {
                if(temp<0)
                n = -(abs((atoi(&note[2]) - 4)) * 12 + 8);
                else
                n = (abs((atoi(&note[2]) - 4)) * 12 - 8);
            }

        }
        else if(ch2 == 'b')
        {
            temp = atoi(&note[2]) - 4;

            if(ch == 'B')
                n = (atoi(&note[2]) - 4) * 12 + 1;
            else if(ch == 'A')
            {
                if(temp<0)
                n = -(abs((atoi(&note[2]) - 4)) * 12 + 1);
                else
                n = (abs((atoi(&note[2]) - 4)) * 12 - 1);
            }
            else if(ch == 'G')
            {
                if(temp<0)
                n = -(abs((atoi(&note[2]) - 4)) * 12 + 3);
                else
                n = (abs((atoi(&note[2]) - 4)) * 12 - 3);
            }
            else if(ch == 'E')
            {
                if(temp<0)
                n = -(abs((atoi(&note[2]) - 4)) * 12 + 6);
                else
                n = (abs((atoi(&note[2]) - 4)) * 12 - 6);
            }
            else if(ch == 'D')
            {
                if(temp<0)
                n = -(abs((atoi(&note[2]) - 4)) * 12 + 8);
                else
                n = (abs((atoi(&note[2]) - 4)) * 12 - 8);
            }
        }
    }

    float freq = pow(2,(n/12.0)) * 440;

    return round(freq);



}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if(strcmp(s,"") == 0)
        return 1;
    else
        return 0;
}
