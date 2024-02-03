#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool rectify_key(string key, int argc);
void cipher_it(string key, string text);

int main(int argc, string argv[])
{
    string key = argv[1];

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    bool cue = rectify_key(key, argc);

    if (!cue)
    {
        return 1;
    }

    // getting text from user::
    string text = get_string("plaintext: ");

    // calculating and printing ciphertext::
    cipher_it(key, text);
}

// function to rectify the key..!
bool rectify_key(string key, int argc)
{
    char testkey[26];
    // convert key into smallchars::

    for (int i = 0; i < 26; i++)
    {
        testkey[i] = tolower(key[i]);
    }

    // validation of the key::
    // no complete key::
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    // complete key but invalid key!
    // key has non alphabetic characters or has repetative charecters::

    for (int i = 0; i < 26; i++)
    {
        int j = i;
        if ((isalpha(testkey[i])))
        {
            if (strchr(testkey, testkey[i]) == strrchr(testkey, testkey[j]))
            {
                int l = 1221;
            }

            else
            {
                return false;
                break;
            }
        }

        else
        {
            return false;
            break;
        }
    }
    // defalut return::
    return true;
    // errors for the keys end...and we get a pure key!!!
}

void cipher_it(string key, string text)
{
    printf("ciphertext: ");

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
