#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function declarations
int to_Upper(int original, int key);
int to_Lower(int original, int key);

int main(int argc, string argv[])
{
    // Variable declarations
    string k;
    int key_length;

    // If user enters the wrong number of command-line arguments
    if (argc != 2)
    {
        // Return error
        printf("Usage: vigenere <keyword>\n");
        return 1;
    }
    // If user enters only 1 command-line argument, store as <key>
    else
    {
        k = argv[1];
        // Get length of <key>
        key_length = strlen(k);
    }

    // Create an array to hold numeric values of each character in the <key>
    int key_array[key_length];

    // Loop through <key> to check that it only contains letters
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        // If <key> contains characters other than letters
        if (!isalpha(k[i]))
        {
            // Return error
            printf("Keyword must only contain A-Z and a-z\n");
            return 1;
        }
        else
        {
            // Convert uppercase characters in <key> to numeric values 0-25
            if (isupper(k[i]))
            {
                key_array[i] = k[i] - 65;
            }
            // Convert lowercase characters in <key> to numeric values 0-25
            else if (islower(k[i]))
            {
                key_array[i] = k[i] - 97;
            }
        }
    }

    // Get string to encipher from user
    string p = GetString();

    int key_index;
    int key_counter = 0;

    // Encipher string using keyword
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // Only apply cipher to letters
        if (isalpha(p[i]))
        {
            key_index = key_counter % key_length;

            // uppercase => encipher => uppercase
            if (isupper(p[i]))
            {
                printf("%c", to_Upper(p[i], key_array[key_index]));
            }
            // lowercase => encipher => lowercase
            else if (islower(p[i]))
            {
                printf("%c", to_Lower(p[i], key_array[key_index]));
            }
            // Update <key> to move to the next character
            key_counter++;
        }
        // Print non-letter characters as they are and DON'T iterate to next character in <key>
        else
        {
            printf("%c", p[i]);
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
