#include <cs50.h>
#include <stdio.h>

int get_height();
void print_hashes();

int main(void)
{
    // taking the height from the user
    int h = get_height();

    // printing hashes using function
    print_hashes(h);
}

// getting the height using a function
int get_height()
{
    int h;

    do
    {
        h = get_int("Height: ");
    }

    while (h < 1 || h > 8);

    return h;
}

// function for printing hashes
void print_hashes(int h)
{
    // first for loop
    for (int i = 0; i < h; i++)
    {
        // printing blank spaces sing while
        int k = h - 1;

        while (k > i)
        {
            printf(" ");
            k--;
        }

        // printing hashes using while
        int j = 0;

        while (j <= i)
        {
            printf("#");
            j++;
        }

        // printing a blank line
        printf("\n");
    }
}