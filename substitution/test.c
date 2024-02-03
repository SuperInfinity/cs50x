#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void cipher_it(string key, string text);

int main()
{
      char a[26] = "VCHPRZGJNTLSKFBDQWAXEUYMOI";
      char b[] = "Hello, World";

      int len = strlen(a);
      cipher_it(a, b);
}


void cipher_it(string key, string text)
{
      printf("Cipher Text: ");

      int len = strlen(text);
      int indexes[len];

      for (int i = 0; i < len; i++)
      {
            if (isupper(text[i]))
            {
                  int index = text[i] - 65;
                  indexes[i] = index;
                  printf("%c", toupper(key[index]));

            }

            else if (islower(text[i]))
            {
                  int index = text[i] - 97;
                  indexes[i] = index;
                  printf("%c", tolower(key[index]));
            }

            else
            {
                  printf("%c", text[i]);
            }
      }

      printf("\n");
}
