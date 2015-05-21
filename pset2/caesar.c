#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Function declarations
int to_Upper(int original, int key);
int to_Lower(int original, int key);

int main(int argc, string argv[])
{
    // Variable declarations
    int k; 
    string phrase;

    // If user doesn't enter a single command-line arugment return error
    if (argc != 2)
    {
        printf("Usage: /home/Dropbox/pset2/caesar <key>\n");
        return 1;
    }
    else
    {
        // Convert command-line argument from string to int
        k = atoi(argv[1]);

        // Check to make sure argument being passed is positive
        if (k < 0)
        {
            printf("Key must be a non-negative integer.\n");
            return 1;
        }
        // Get a string from user and store it
        else
        {
            phrase = GetString();
        }
    }

    // Iterate and print out enciphered string
    for (int i = 0, n = strlen(phrase); i < n; i++)
    {
        // Check to see if index value is an alphabetical letter
        if (isalpha(phrase[i]))
        {
            // uppercase => encipher => uppercase
            if (isupper(phrase[i]))
            {
                printf("%c", to_Upper(phrase[i], k));
            }
            // lowercase => encipher => lowercase
            else if (islower(phrase[i]))
            {
                printf("%c", to_Lower(phrase[i], k));
            }
        }
        else
        {
            // If not an alphabetical letter, print the character
            printf("%c", phrase[i]);
        }
    }

    printf("\n");
    return 0;
}


// These 2 case-sensitive functions will return a enciphered letter
int to_Upper(int original, int key)
{
    int deciphered = (((original - 65 + key) % 26) + 65);
    return deciphered;
}

int to_Lower(int original, int key)
{
    int deciphered = (((original - 97 + key) % 26) + 97);
    return deciphered;
}
