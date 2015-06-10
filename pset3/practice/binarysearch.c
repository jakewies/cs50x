/*
Return true if value is in array of n values, else false.
*/

#include <stdio.h>
#include <cs50.h>

bool search(int value, int values[], int n);

int main(int argc, string argv[])
{
    int some_value = atoi(argv[1]);
    int myArray[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    printf("%d\n", search(some_value, myArray, 10));
}
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

bool search(int value, int values[], int n)
{  
    if (n < 0)
    {
        return false;
    }
    
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
    }
    return false;
}

