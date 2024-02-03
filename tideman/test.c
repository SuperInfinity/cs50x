#include <stdio.h>
#include <cs50.h>

bool locked[3][3];


int edges[] = {0,1,1,2,2,0};

bool cycle(int edges1[] , int n)
{
      int l = n;

      for (int i = 0; edges1[i] != '\0'; i++)
      {
            l++;
      }

      printf("%i\n", l);

      //for even:
      int i = 0;
      //for odd:
      int j = l - 1;

      int x = 0;

      while (x <= ((l / 2) - 1))
      {
            if (i == j)
            {
                  return false;
            }

            if (edges1[i] == edges1[j])
            {
                  return true;
            }

            else
            {
                  i += 2;
                  j -= 2;
            }

            x++;
      }

      return false;
}

int main(void)
{
      if (cycle(edges, 6))
      {
            printf("this is a loop/ cycle..!!\n");
      }

      return 0;
}
