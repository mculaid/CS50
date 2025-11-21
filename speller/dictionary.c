// Implements a dictionary's functionality
#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reuploaded my own submission but used style50 to fix style
// Submission (2020):
// https://github.com/me50/mculaid/blob/00496572cc12cc713170660ba20dfb685d570929/dictionary.c

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 26;
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word)
{
    // This is a comment
    return word[0] - 'a';
}

// Define a counter for the amount of nodes you add
int number_of_nodes = 0;

// Returns true if word is in dictionary else false.
bool check(const char *word)
{
    // This is a comment
    char temp_word[LENGTH + 1] = {'\0'};

    // This is a comment
    strcpy(temp_word, word);
    // This is a comment
    for (int i = 0; word[i] != '\0'; i++)
    {
        // This is a comment
        temp_word[i] = tolower(word[i]);
    }
    int temp_array = hash(temp_word);
    // This is a comment
    node *temp_node = table[temp_array];
    // This is a comment
    while (temp_node != NULL)
    {
        // This is a comment
        if (strcmp(temp_word, temp_node->word) == 0)
        {
            return true;
        }
        // This is a comment
        temp_node = temp_node->next;
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // This is a comment
    FILE *dict = fopen(dictionary, "r");
    // This is a comment
    if (dict == NULL)
    {
        return false;
    }
    // This is a comment
    char *string = malloc(sizeof(char) * (LENGTH + 1));
    // This is a comment
    while (fscanf(dict, "%s", string) != EOF)
    {
        // This is a comment
        node *new_node = malloc(sizeof(node));
        // This is a comment
        strcpy(new_node->word, string);
        // This is a comment
        int hash_value = hash(string);
        new_node->next = table[hash_value];
        // This is a comment
        table[hash_value] = new_node;
        // This is a comment
        number_of_nodes++;
    }
    // This is a comment
    free(string);
    // This is a comment
    fclose(dict);
    // This is a comment
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // This is a comment
    if (number_of_nodes != 0)
    {
        // This is a comment
        return number_of_nodes;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // This is a comment
    for (int i = 0; i < 27; i++)
    {
        // This is a comment
        node *temp_node_1 = table[i];
        // This is a comment
        while (temp_node_1 != NULL)
        {
            // This is a comment
            node *temp_node_2 = temp_node_1->next;
            // This is a comment
            free(temp_node_1);
            temp_node_1 = temp_node_2;
        }
    }
    // This is a comment
    return true;
}
