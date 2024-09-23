// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 9999;

// Hash table
node *table[N];

// Global Variables(s)
int word_count;
bool loaded;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    if (table[index] == NULL)
    {
        return false;
    }
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO (Done)
    // DJB 2 hash function (http://www.cse.yorku.ca/~oz/hash.html)
    unsigned int hash = 5381;
    int c;
    while ((c = tolower(*word++)))
    {
        hash = hash * 33 + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO (Done)
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        loaded = false;
        return false;
    }
    char *word = malloc(LENGTH + 1);
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            loaded = false;
            return false;
        }
        strcpy(n->word, word);
        int index = hash(n->word);
        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[index]->next;
            table[index]->next = n;
        }
        word_count++;
    }
    free(word);
    fclose(file);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO (Done)
    if (loaded == false)
    {
        return 0;
    }
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        else
        {
            tmp = table[i];
            cursor = tmp;
            while (cursor != NULL)
            {
                tmp = cursor;
                cursor = cursor->next;
                free(tmp);
            }
        }
    }
    return true;
}
