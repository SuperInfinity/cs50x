#include<stdio.h>
#include<cs50.h>

// make user promt a good input

int main(void)
{
    int n;

    do
    {
        n = get_int("size:  ");

    }

    while (n < 1);

// printing the grid

    int i;
    int j;

    for ( i = 0 ; i < n ; i++ )
    {
        for( j = 0 ; j < n ; j++ )
        {
            printf("#");
        }

        printf("\n");
    }
}