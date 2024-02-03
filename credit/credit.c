#include <cs50.h>
#include <stdio.h>

long a;

int main(void)
{
    a = get_double("Number: \n");

    // counting  number of digits

    long p = a;

    int n = 0;

    while (p > 0)
    {
        n++;

        int x = p % 10;

        p = p / 10;
    }

    // end of the block

    // block for the lums algorithm:

    long q = a;
    int e;
    int h;
    int o = 0;
    int d;
    int w;
    int k = 0;
    int s = 0;
    int f;

    for (int i = 1; i <= n; i++)
    {

        int y = q % 10;

        q = q / 10;

        // to take the first two digits::

        if (i == n - 2)
        {
            e = q;
        }

        // to take last digit::

        else if (i == n - 1)
        {
            h = q;
        }

        // block for numbers which are multiplied by two

        if (i % 2 == 0)
        {

            o = y * 2;

            if (o % 10 != 0)
            {
                d = o % 10;
                o = o / 10;
                w = o + d;
            }

            else if (o == 10)

            {
                w = 1;
            }

            else
            {
                w = o;
            }

            k = w + k;
        }

        // block for numbers not multiplied by two
        else
        {
            s = s + y;
        }
    }

    f = k + s;

    if (f % 10 == 0)
    {
        if (n == 15 && (e == 37 || e == 34))
        {
            printf("AMEX\n");
        }

        else if (n == 16 && (e == 51 || e == 52 || e == 53 || e == 54 || e == 55))
        {
            printf("MASTERCARD\n");
        }

        else if ((n == 13 || n == 16) && h == 4)
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}