// Implements a dictionary's functionality


// https://cs50.harvard.edu/x/2023/psets/5/speller/
/* Requirements
implementation of check must be case-insensitive
implementation of check should only return true for words actually in dictionary
the only possessives allowed are those actually in dictionary i.e. even if foo is in dictionary, check should return false given foo's if foo's is not also in dictionary.
any dictionary passed to your program will be structured exactly like ours, alphabetically sorted from top to bottom with one word per line, each of which ends with \n
dictionary will contain at least one word, that no word will be longer than LENGTH
no word will appear more than once
each word will contain only lowercase alphabetical characters and possibly apostrophes
and that no word will start with an apostrophe.
check will only be passed words that contain (uppercase or lowercase) alphabetical characters and possibly apostrophes
Your spell checker must not leak any memory. Be sure to check for leaks with valgrind.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next; //pointer to the next node
} node;


//dictionary word count
int dictWordCount = 0;

//TODO: change me
const unsigned int N = 26*LENGTH;
// Hash table (global pointer array)
node *table[N]; //declared not initialised
// int dist[N] = {0};

//TODO: change me
// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int len = strlen(word)-1;
    return len * (toupper(word[0]) - 'A');
}
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hashValue = hash(word);
    //get start of linked list from table
    node *cursor = table[hashValue];
    while (cursor != NULL) //will be null when end of linked list
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        //move cursor to next mode
        cursor= cursor->next;
    }
    //reached end of linked list, word not found
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    // Open dictionary file
    FILE *dictPtr = fopen(dictionary, "r");
    if (dictPtr  == NULL)
    {
        printf("EXCEPTION: FILE %s is NULL\n", dictionary);
        return false;
    }

    char wordBuffer[LENGTH + 1];
    // dictWordCount = 0;

    //initialise head of tables to nullptr //does not work, use calloc solution instead of malloc
    // for (int i = 0; i < N; i++)
    // {
    //     table[i] = NULL;
    // }

    //for each word in dictionary
    while (fscanf(dictPtr, "%s", wordBuffer) != EOF)
    {
        //create new node struct for each dictionary word
        node *n = calloc(1,sizeof(node)); //calloc instead of malloc to initialize pointer to 0 instead of uninitialized
        // node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("EXCEPTION: unable to create node\n");
            return false;
        }
        strcpy(n->word,wordBuffer);
        int hashIndex = hash(wordBuffer);

        //insert node at hash_value location in table, at head of linked list
        if (table[hashIndex] != NULL)
        {
            //unshift node in the linked list
            n->next = table[hashIndex];
        }
        table[hashIndex] = n;
        // dist[hashIndex]++;
        dictWordCount++;
    }

    printf("SUCCESS: %d words read from %s",dictWordCount,dictionary);
    fclose(dictPtr);

    // for (int i = 0; i < N; i++)
    // {
    //     printf("\nBucket %d contains %d items",i,dist[i]);
    // }
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictWordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //for each head in hashtable
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        //loop through linkedlist
        while (cursor != NULL)
        {
            //store cursor address to be freed
            node *temp = cursor;
            //move cursor to next
            cursor = cursor->next;
            free(temp);
        }

        //completed entire hash table, return true
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    printf("EXCEPTION: Unloading Failed");
    return false;
}
