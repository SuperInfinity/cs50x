// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string name);

int main(int argc, string argv[])
{
      //if error::
      if (argc != 2)
      {
            printf("only one word allowed.. \n");
            return 1;
      }

      //say no theres error::
      else
      {
            string n1 = replace(argv[1]);

            printf("%s \n" , n1);
      }
}

//the finction::
string replace(string name)
{
      int len = strlen(name);

      for (int i = 0; i < len ; i++)
      {
            switch(name[i])
            {
                  case 'a':
                        name[i] = name[i] - 43;
                        break;

                  case 'e':
                        name[i] = name[i] - 50;
                        break;

                  case 'i':
                        name[i] = name[i] - 56;
                        break;

                  case 'o':
                        name[i] = name[i] - 63;
                        break;

                  default:
                        break;

            }
      }

      return name;
}
