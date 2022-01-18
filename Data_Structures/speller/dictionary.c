// Implements a dictionary's functionality
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[26][26][26];

// variable to keep track of words in the dictionary
int words_in_dict = 0;

// Returns true if word is in dictionary, else false
// first, hashes the word to discover its location in the dictionary,
// then, iterate over the nodes
// if the word is in one of the nodes, return true
// if it has iterated over all the nodes and not found, return false
bool check(const char *word)
{
    int word_length = strlen(word);
    
    int index[3];
    for (int i = 0; i < 3; i++)
    {
        if (i <= word_length - 1)
        {
            const char *letter = &word[i];
            index[i] = hash(letter);
        }
        else
        {
            const char *a = "a";
            index[i] = hash(a);
        }
    }

    for (node *cursor = table[index[0]][index[1]][index[2]]; 
         cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number by getting its index in an alphabet array
unsigned int hash(const char *word)
{
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                       'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                       'w', 'x', 'y', 'z'
                      };

    int value; 
    for (int i = 0; i < N; i++)
    {
        if (tolower(word[0]) == alphabet[i])
        {
            return i;
        }
    }

    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
// and make the linked list of all the words
bool load(const char *dictionary)
{
    FILE *loaded_dict = fopen(dictionary, "r");
    if (loaded_dict == NULL)
    {
        return false;
    }

    char word[50];
    
    node *n = NULL;
    while (fscanf(loaded_dict, "%s", word) != EOF)
    {
        n = malloc(sizeof(node));
        
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);

        int index[3];
        int word_length = strlen(word);
        
        for (int i = 0; i < 3; i++)
        {
            if (i <= word_length - 1)
            {
                char *letter = &word[i];
                index[i] = hash(letter);
            }
            else
            {
                char *a = "a";
                index[i] = hash(a);
            }
        }

        // checking if the location is null to avoid possible memory leaks
        extern int words_in_dict;
        if (table[index[0]][index[1]][index[2]] == NULL)
        {   
            table[index[0]][index[1]][index[2]] = n;
            n->next = NULL;
        }
        else if (table[index[0]][index[1]][index[2]]->next == NULL)
        {
            table[index[0]][index[1]][index[2]]->next = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[index[0]][index[1]][index[2]]->next;
            table[index[0]][index[1]][index[2]]->next = n;
        }

        words_in_dict++;
    }  
    
    fclose(loaded_dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    extern int words_in_dict;
    return words_in_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
// iterates over all the hash table, freeing all the nodes
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                node *tmp = table[i][j][k];
                if (tmp != NULL)
                {
                    if (tmp->next != NULL)
                    {
                        for (node *cursor = table[i][j][k]->next; cursor != NULL;
                             cursor = cursor->next)
                        {
                            free(tmp);
                            tmp = cursor;
                        }
                        free(tmp);
                    }
                    else
                    {
                        free(tmp);
                    }
                }
            }
        }
    }
    return true;
}
