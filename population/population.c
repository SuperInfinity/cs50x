#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int a;
    do
    {
        a = get_int("starting population: ");
    }

    while(a < 9);

    // TODO: Prompt for end size

    int b;

    do
    {
        b = get_int("end size: ");
    }

    while(b < a );

    // TODO: Calculate number of years until we reach threshold


    int n = 0;

    int x = a;

    if(a == b)
    {
        n = 0;
    }

    else
    {

        do
        {
            x = x + ( (int)x / (int)3 ) - ( (int)x / (int)4 );
            n = n + 1;
        }

        while(x < b);

    }




    // TODO: Print number of years

    printf("Years: %i \n" , n);

}
