#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    
    /* Prompt the user for the pyramid height
    and continue to prompt the user if they enter 
    a negative number or a number greater than 23 */
    do 
    {
        printf("Please enter the pyramid height: ");
        height = GetInt();
    } while (height < 0 || height > 23);   
    
    // Loop through each row
    for (int row = 0; row < height; row++) 
    {
        // Create spaces
        for (int space = 0; space < height - row - 1; space++) 
        {
            printf(" ");   
        }   
        
        // Create hashes
        for (int hash = 0; hash < row + 2; hash++)
        {
            printf("#");
        }
        
        // Create new lines
        printf("\n");
    }
}
