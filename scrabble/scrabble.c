#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins! \n");
    }

    else if (score1 < score2)
    {
        printf("Player 2 wins! \n");
    }

    else
    {
        printf("Tie! \n");
    }
    // end.
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    int score;
    int sum = 0;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        // deals case sensitivity::(all to lower)
        if (isupper(word[i]))
        {
            word[i] = tolower(word[i]);
        }

        // ignore symbols & calcs score::
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            int index = word[i] - 97;
            score = POINTS[index];
            sum = sum + score;

            printf("score of %c is %d \n", word[i], sum);
        }
    }

    return sum;
}
