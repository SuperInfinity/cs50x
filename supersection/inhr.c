// Simulating genetic inheritance of blood type

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Each parent has two parents and two alleles
typedef struct person
{
      struct person *parents[2];
      char alleles[2];
}
person;

const int GENERATIONS = 5;
const int INDENT_LENGTH = 4;

person *create_family(int generation);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
      // seed random number generator;
      srand(time(0));

      //create new family with three generations;
      person *p = create_family(GENERATIONS);

      //print family;
      print_family(p, 0);

      //free memory;
      free_family(p);
}

person *create_family(int generations)
{
      //allocate memory for new person;
      person *new_person = malloc(sizeof(person));

      if (new_person == NULL)
      {
            printf("error allocating memory for a person..!\n");
            return NULL;
      }

      if (generations > 1)
      {
            // create new parents for the current parent by recurcively calling create family;
            person *parent0 = create_family(generations - 1);
            person *parent1 = create_family(generations - 1);

            // setting parent pointers to these current pointers;
            new_person->parents[0] = parent0;
            new_person->parents[1] = parent1;

            // randomly assinging alleles based on their parents alleles
            new_person->alleles[0] = parent0->alleles[rand() % 2];
            new_person->alleles[1] = parent1->alleles[rand() % 2];

            return new_person;
      }

      else
      {
            // if this is the last generation, then set the parent's pointer to NULL:
            new_person->parents[0] = NULL;
            new_person->parents[1] = NULL;

            // randomly assign some alleles to the person:
            new_person->alleles[0] = random_allele();
            new_person->alleles[1] = random_allele();

            return new_person;
      }
}

void free_family(person *p)
{
      // base case
      if (p == NULL)
      {
            return;
      }

      // free parents recurcively
      free_family(p->parents[0]);
      free_family(p->parents[1]);

      free(p);
}

char random_allele()
{
      int r = rand() % 3;

      if (r == 0)
      {
            return 'A';
      }

      else if (r == 1)
      {
            return 'B';
      }

      else
      {
            return 'O';
      }
}

void print_family(person *p, int generation)
{
      if (p == NULL)
      {
            return;
      }

      // print indentation
      for (int i = 0; i < generation * INDENT_LENGTH; i++)
      {
            printf("-");
      }

      // print person
      if (generation == 0)
      {
            printf("Child (Generation %i): bloodgroup type %c%c\n", generation, p->alleles[0], p->alleles[1]);
      }

      else if (generation == 1)
      {
            printf("Parent (Generation %i): bloodgroup type %c%c\n", generation, p->alleles[0], p->alleles[1]);
      }

      else
      {
            for (int i = 0; i < generation - 2; i++)
            {
                  printf("Great-");
            }
            printf("Grandparents (Generation %i): bloodgroup type %c%c\n", generation, p->alleles[0], p->alleles[1]);
      }

      // print parents of current generation
      print_family(p->parents[0], generation + 1);
      print_family(p->parents[1], generation + 1);
}
