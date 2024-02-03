// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    int hash_value = hash(word);
    node *ptr = table[hash_value];
    int key = 0;

    while (ptr != NULL)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            key = 1;
            break;
        }

        ptr = ptr->next;
    }

    if (key == 1)
    {
        return true;
    }

    else
    {
        return false;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int len = strlen(word);

    if (len >= 3)
    {
        unsigned int index1, index2, index3;

        index1 = tolower(word[0]) - 'a';

        index1 += (index1 * 675);

        if (word[1] == '\'')
        {
            index2 = 0;
        }

        else
        {
            index2 = tolower(word[1]) - 'a';
            index2 += (index2 * 25);
        }

        if (word[2] == '\'')
        {
            index3 = 0;
        }

        else
        {
            index3 = tolower(word[2]) - 'a';
        }

        return (index1 + index2 + index3);
    }

    // if word length is less than three..
    else
    {
        if (len == 2)
        {
            unsigned int index1, index2;

            index1 = tolower(word[0]) - 'a';

            index1 += (index1 * 675);

            if (word[1] == '\'')
            {
                index2 = 0;
            }

            else
            {
                index2 = tolower(word[1]) - 'a';
                index2 += (index2 * 25);
            }

            return (index1 + index2);
        }

        else
        {
            unsigned int index1;

            index1 = tolower(word[0]) - 'a';

            index1 += (index1 * 675);

            return index1;
        }
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // opening the dictionary
    char buffer[42];

    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        printf("ERROR opening dictionary..!\n");
        fclose(source);
        return false;
    }

    // reading each word in the file

    while (fscanf(source, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("Error while mallocing..!\n");
            return false;
        }

        unsigned int index = hash(buffer);

        // if this is the first value in this table value
        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;

            strcpy(n->word, buffer);
            word_count++;
        }

        // if not empty, then append the new node at the start..!
        else
        {
            n->next = table[index];
            table[index] = n;

            strcpy(n->word, buffer);
            word_count++;
        }
    }

    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    node *ptr = NULL;
    node *tmp = NULL;

    for (int i = 0; i < N; i++)
    {
        ptr = table[i];

        while (ptr != NULL)
        {
            tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }

    return true;
}
