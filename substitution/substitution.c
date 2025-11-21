#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) // Ensure exactly one argument (besides program name) is provided
    {
        printf("Usage: ./program key\n");
        return 1;
    }

    string key = argv[1];

    // key size must be 26
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // initialize array with alphabet ***
    char alphabet[26];
    char letter = 65;
    for (int i = 0; i < 26; i++)
    {
        alphabet[i] = letter;
        letter++;
    }
    // check if character is alphabetical and double
    for (int i = 0; i < 26; i++)
    {
        // if is alphabetical
        if (isalpha(key[i]) != 0)
        {
            // check for doubles
            for (int j = 0; j < 26; j++)
            {
                // We use two loops in a single array so we have to prevent overlap
                if (i != j)
                {
                    if (toupper(key[i]) == toupper(key[j]))
                    {
                        printf("Key contains double characters.\n");
                        return 1;
                    }
                }
            }
        }
        // else if not alphabetical
        else
        {
            printf("Key contains non-alphabetical symbols.\n");
            return 1;
        }
    }
    string message = get_string("plaintext: ");
    string cipher = message;

    // loop through the message
    for (int i = 0; i < strlen(message); i++)
    {
        //  also loop through alphabet
        for (int j = 0; j < 26; j++)
        {
            // and compare it to key[j]
            if (toupper(message[i]) == toupper(alphabet[j]))
            {
                if (islower(message[i]) != 0)
                {
                    cipher[i] = tolower(key[j]);
                }
                else if (isupper(message[i]) != 0)
                {
                    cipher[i] = toupper(key[j]);
                }
                break;
            }
        }
        if (ispunct(message[i]) != 0)
        {
            cipher[i] = message[i];
        }
    }
    printf("ciphertext: %s\n", cipher);
    return 0;
}
