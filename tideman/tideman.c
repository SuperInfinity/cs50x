#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }

        // added by me to set all prefrences to zero first..!
        for (int j = i; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    // temporary for printing preference matrix..!!!
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d ", preferences[i][j]);
        }

        printf("\n");
    }

    printf("\n");

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // first checking if the name is in the candidates::
    int key = 0, index = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            key = 1;
            index = i;
        }
    }
    // if not erturn false::
    if (key != 1)
    {
        return false;
    }

    // else just append the name to the ranks::
    ranks[rank] = index;

    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int index = 0;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[index].winner = i;
                pairs[index].loser = j;

                index++;
                pair_count++;
            }

            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[index].winner = j;
                pairs[index].loser = i;

                index++;
                pair_count++;
            }

            // if tied or anything.. do nothing..
            else
            {
                int lol = 69;
            }
        }
    }

    printf("\n%i\n\n", pair_count);

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int l = pair_count;

    for (int i = 0; i < l; i++)
    {
        bool swapped = false;

        for (int j = 0; j < l - 1; j++)
        {
            pair temp;

            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;

                swapped = true;
            }
        }

        if (swapped == false)
        {
            break;
        }
    }

    return;
}

// this algorithm uses an array to check if the edges form a loop or not;

// bool cycle(int current_size, int edges[], int winner)
// {
//     int loser = edges[current_size - 1];

//     if (current_size <= 0)
//     {
//         return false;
//     }

//     else if (winner == loser)
//     {
//         return true;
//     }

//     if (cycle(current_size - 2, edges, winner))
//     {
//         return true;
//     }

//     return false;
// }

bool cycle(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (cycle(winner, i))
            {
                return true;
            }
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int edges[pair_count * 2];
    int current_size = 0;

    // main loop to lock the pairs..!
    for (int i = 0; i < pair_count; i++)
    {
        // if there are less than 2 edges::
        if (i < 2)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;

            // edges[current_size] = pairs[i].winner;
            // current_size++;

            // edges[current_size] = pairs[i].loser;
            // current_size++;
        }

        // now for more than 2 edges..!
        else
        {
            // edges[current_size] = pairs[i].winner;
            // current_size++;
            // edges[current_size] = pairs[i].loser;
            // current_size++;

            if (!cycle(pairs[i].winner, pairs[i].loser))
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }

            // else
            // {
            //     current_size -= 2;
            // }
        }
    }

    // print the locked matrix..!!
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                printf("%i ", 1);
            }

            else
            {
                printf("%i ", 0);
            }
        }

        printf("\n");
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO

    for (int i = 0; i < candidate_count; i++)
    {
        int key = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                key++;
            }
        }

        if (key == candidate_count)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }

    return;
}
