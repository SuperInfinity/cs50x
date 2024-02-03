#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

string get_input();
int count_letters(string sentence);
int count_words(string sentence);
int count_sentences(string sentence);
void Coleman_Liau_index(int letter_cnt, int word_cnt, int sentence_cnt);

// main function::
int main(void)
{
    // taking input:
    string sentence = get_input();

    // counting letters:
    int letter_cnt = count_letters(sentence);

    // counting words:
    int word_cnt = count_words(sentence);

    // counts sentences:
    int sentence_cnt = count_sentences(sentence);

    // gives index::
    Coleman_Liau_index(letter_cnt, word_cnt, sentence_cnt);
}

// function for input::
string get_input()
{
    string sentence = get_string("Text: ");
    return sentence;
}

// function for counting letters::
int count_letters(string sentence)
{
    int sen_len = strlen(sentence);
    int count = 0;

    // iterate thro the sentence::
    for (int i = 0; i < sen_len; i++)
    {
        // counts only aphabets::
        if ((sentence[i] >= 'a' && sentence[i] <= 'z') || (sentence[i] >= 'A' && sentence[i] <= 'Z'))
        {
            count++;
        }
    }

    return count;
}

// function for counting words::
int count_words(string sentence)
{
    int sen_len = strlen(sentence);
    int count = 0;

    for (int i = 0; i < sen_len; i++)
    {
        if ((isblank(sentence[i])) && !(isblank(sentence[i + 1])))
        {
            count++;
        }
    }

    return count + 1;
}

// function for counting sentences::
int count_sentences(string sentence)
{
    int sen_len = strlen(sentence);
    int count = 0;

    for (int i = 0; i < sen_len; i++)
    {
        if (sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?')
        {
            count++;
        }
    }

    return count;
}

void Coleman_Liau_index(int letter_cnt, int word_cnt, int sentence_cnt)
{
    float L = ((float) letter_cnt / word_cnt) * 100;
    float S = ((float) sentence_cnt / word_cnt) * 100;

    double index = (0.0588 * L - 0.296 * S - 15.8);
    int index1 = (int) round(index);

    if (index1 >= 16)
    {
        printf("Grade 16+\n");
    }

    else if (index1 < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", index1);
    }
}
