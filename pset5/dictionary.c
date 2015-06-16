/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

// Global variables
node* hashTable[HASH_SIZE];
unsigned int dictionary_size = 0;

// Prototypes
unsigned long hash(char* str);

/**
 * Returns true if word is in dictionary else false.
 **/
bool check(const char* word)
{
    // Convert word to lowercase
    int n = strlen(word);
    char currentWord[n + 1];

    for (int i = 0; i < n; i++)
        currentWord[i] = tolower(word[i]);

    currentWord[strlen(word)] = '\0';

    // Get hash value of word to be checked
    int tableIndex = hash(currentWord);

    // Point to first word in hash table at given hash
    node* ptrNode = hashTable[tableIndex];

    // Search for word in hash table
    while (ptrNode != NULL)
    {
        // If word is found at head of linked list return true
        if (strcmp(ptrNode->word, currentWord) == 0)
            return true;

        // Move down linked list if word isn't there
        ptrNode = ptrNode->next;
    }

    // If end of list is reached, return false
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 **/
bool load(const char* dictionary)
{
    // Initialize variables
    char currentWord[LENGTH + 1];
    int tableIndex;

    // Open dictionary
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
        return false;

    while(fscanf(dict, "%s", currentWord) == 1)
    {
        // Get hash value of word
        tableIndex = hash(currentWord);

        // Initialize new node
        node* newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            printf("Error: Out of memory\n");
            return false;
        }
        newNode->word = malloc((strlen(currentWord) + 1) * sizeof(char));
        if (newNode->word == NULL)
        {
            printf("Error: Out of memory\n");
            return false;
        }

        // Copy word into new node
        strcpy(newNode->word, currentWord);
        newNode->next = NULL;

        // If no collision, hash word into head of list
        if (hashTable[tableIndex] == NULL)
            hashTable[tableIndex] = newNode;

        // Create a pointer and move down list
        else
        {
            node* ptrNode = hashTable[tableIndex];

            while (ptrNode->next != NULL)
                ptrNode = ptrNode->next;

            // Append node to end of linked list
            ptrNode->next = newNode;
        }

        // Increase dictionary size
        dictionary_size++;
    }

    // Close dictionary and return true
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionary_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // Iterate through hash table
    for (int i = 0; i < HASH_SIZE; i++)
    {
        // Point to first node in linked list
        node* cursor = hashTable[i];

        while(cursor != NULL)
        {
            // Set temp pointer to hold current node, move cursor down list
            node* temp = cursor;
            cursor = cursor->next;

            // free actual word before node itself
            free(temp->word);
            free(temp);
        }
    }
    return true;
}

/**
 * djb2 Hash function
 **/
unsigned long hash(char* str)
{
  unsigned long hash = 5381;
  int c;
  while ((c = *str++) != 0)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % HASH_SIZE;
}
