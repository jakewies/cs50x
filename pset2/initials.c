#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // Get a name from the user
    string name = GetString();
    
    // Immediately print the first letter of the name capitalized
    printf("%c", toupper(name[0])); 
    
    /* Loop through the length of the string and capitalize
    the letter following a space */
    for (int i = 0, n = strlen(name); i < n; i++)
    {       
        /* Notice no 'newline' being printed. Make sure
        there aren't anymore words in the string, else the letter 
        will be printed on a new line */
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1])); 
        }
    }
    // After looping through the entire string print 'newline'
    printf("\n");  
}
