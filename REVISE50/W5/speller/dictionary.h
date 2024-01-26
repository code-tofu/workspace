// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

//defines bool
#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/*
char * with /0 is string
bool check(const string word);
unsigned int hash(const string word);
bool load(const string dictionary);
*/

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
