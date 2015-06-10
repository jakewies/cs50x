#include <stdio.h>
#include <cs50.h>
#include <string.h>

// pass sort() function an array of ints and the size of the array
void sort(int array[], int n)
{
    // declare a variable that will be a temporary value holder
    int value_holder;
    
    // Cycles through the array
    for (int k = 0; k < n - 1; k++)
    {
        // Reset counter to zero
        int swap_counter = 0;
    
        // Step through array and sort it
        for (int i = 0; i < n - 1 - k; i++)
        {
            if (myArray[i + 1] < myArray[i])
            {
                // Swap values using temp holder variable declared eariler
                value_holder = myArray[i + 1];
                myArray[i + 1] == myArray[i];
                myArray[i] = value_holder;
                
                // Increment counter so we know that we've swapped something
                swap_counter++;
            }
        }
        // If there have been no swaps, end loop
        if (!swap_counter)
        {
            break;
        }   
    }
}
