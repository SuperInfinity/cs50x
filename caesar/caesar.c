#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


bool is_valid(string argv, int argc);
char rotate(int key, char c);

int main(int argc, string argv[])
{
      if (!is_valid(argv[1], argc))
      {
            return 1;
      }

      // convert string key into an int::
      int key = atoi(argv[1]);

      //get the text from user::
      string text = get_string("plaintext:  ");

      //rotate and then print::
      printf("ciphertext: ");

      int len = strlen(text);

      for (int i = 0; i < len; i++)
      {
            char c = rotate(key , text[i]);
            printf("%c", c);
      }

      printf("\n");
}

bool is_valid(string argv, int argc)
{
      int len = strlen(argv);

      if (argc != 2)
      {
            printf("Usage: ./caesar key\n");
            return false;
      }

      for (int i = 0; i < len; i++)
      {
            if (!isdigit(argv[i]))
            {
                  printf("Usage: ./caesar key\n");
                  return false;
            }
      }

      return true;
}

char rotate(int key, char c)
{
      if (isupper(c))
      {
            int index = ((int)c - 65 + key) % 26;
            char new = 'A' + index;

            return new;
      }

      else if (islower(c))
      {
            int index = ((int)c - 97 + key) % 26;
            char new = 'a' + index;

            return new;
      }

      else
      {
            return c;
      }
}

