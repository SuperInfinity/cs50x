#include <cs50.h>
#include <stdio.h>

// functions exist down below....... real down......!

int get_height(void);
void print_hashes(int h);

int main(void)
{
    // getting input
    int h = get_height();

    // printing hashes
    print_hashes(h);
}

int get_height(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }

    while (h >= 9 || h <= 0);

    return h;
}

// function for blank spaces and hashes............!!(it was hard to figure that out) and apollogies for messy code..!

void print_hashes(int h)
{
    int g = h - 1;

    for (int j = 0; j < h; j++)
    {
        int k = 0;

        if (g > 0)
        {
            do
            {
                k++;
                printf(" ");
            }

            while (k < g);
        }

        if (g >= 1)
        {
            g = g - 1;
        }

        else
        {
            g = 0;
        }

        // prints hashes

        int o = 0;

        do
        {
            o++;
            printf("#");
        }

        while (o <= j);

        // print next dots

        printf("  ");

        // prints the next sets of hashes

        int p = 0;

        do
        {
            p++;
            printf("#");
        }

        while (p <= j);

        printf("\n");
    }
}