/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Set values for top and bottom of search
    int lower = 0;
    int upper = n - 1;
    
    // Binary search
    while (lower <= upper) 
    {
         // Find the middle
         int middle = (upper + lower) / 2;
         
         // Compare middle to value wanted
         if (values[middle] == value)
         {
            return true;
         }
         
         else if (values[middle] < value)
         {
            lower = middle + 1;   
         }
         else if (values[middle] > value)
         {
            upper = middle - 1;
         }
    }
    
    // If value is not in array
    return false;
}

/**
 * Sorts array of n values.
**/
void sort(int values[], int n)
{
    int temp = 0;
    
    // Count iteration cycles 
    for (int i = 0; i < n - 1; i++)
    {
        // Declare smallest variable and position
        int smallest = values[i];
        int position = i;
        
        // Iterate through array
        for (int j = i + 1; j < n; j++)
        {
            if (values[j] < smallest)
            {
                smallest = values[j];
                position = j;
            }
        }
        
        // Swap smallest value with current value at index i
        temp = values[i];
        values[i] = smallest;
        values[position] = temp;       
    }
    return;
} 
