/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include "dictionary.h"


//root of tries:
tries *root;
unsigned int wordcounter;
void clearing (tries *ptr);
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    tries *ptr = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        char c = tolower(word[i]);
        //When the character is aspostrophe
        if (c == '\'')
        {
            //Store apostrophe at the end of array
            tries *nextnode = ptr->children[26];
            if (nextnode == NULL)
            {
                return false;
            }
            else
            {
                ptr = nextnode;
            }
        }
        //When the character is not aspostrophe
        else
        {
            tries *nextnode = ptr->children[c-97];
            if (nextnode == NULL)
            {
                return false;
            }
            else
            {
                ptr = nextnode;
            }
        }

    }
    //determine if the word is correct
    if (ptr->word)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    root = calloc(1, sizeof(tries));
    tries *ptr = root;
    char c;
    while((c = tolower(fgetc(dict))) != EOF)
    {
        if (c == '\n' && ptr != root)
        {
            ptr->word = true;
            wordcounter++;
            ptr = root;
        }
        else
        {
            //When the character is aspostrophe
            if (c == '\'')
            {   //to put aspostrophe at the ending of array
                tries *nextnode = ptr->children[26];
                if (nextnode != NULL)
                {
                    ptr = nextnode;
                }
                else
                {
                    ptr->children[26] = calloc(1, sizeof(tries));
                    ptr = ptr->children[26];
                }
            }
            //When the character is not aspostrophe
            else
            {
                tries *nextnode = ptr->children[c-97];
                if (nextnode != NULL)
                {
                    ptr = nextnode;
                }
                else
                {
                    ptr->children[c-97] = calloc(1, sizeof(tries));
                    ptr = ptr->children[c-97];
                }
            }
        }
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcounter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
void clearing (tries *ptr)
{
    for (int j = 0; j < 27; j++)
    {
        if (ptr->children[j] != NULL)
        {
            clearing(ptr->children[j]);
        }
    }
    free(ptr);
}

bool unload(void)
{
    clearing(root);
    return true;
}
