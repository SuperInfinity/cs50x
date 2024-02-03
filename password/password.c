// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{


    int len = strlen(password);

    //keys::
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    for (int i = 0; i < len; i++)
    {

        if (password[i] >= 'a' && password[i] <= 'z')
        {
            a = 5;
        }

        else if (password[i] >= 'A' && password[i] <= 'Z')
        {
            b = 5;
        }

        else if (password[i] >= '0' && password[i] <= '9')
        {
            c = 5;
        }

        else if (password[i] == '!' || password[i] == '#' || password[i] == '$')
        {
            d = 5;
        }
    }

    // if all keys are correct

    if(a == 5 && b == 5 && c == 5 && d == 5)
    {
        return true;
    }

    //default return
    return false;
}
