/**
    SORT ARRAY IN PLACE USING SELECTION SORT

for i = 0 to n - 2
    min = i;
    
    for j = i + 1 to n - 1
    
        if array[j] < array[min]
            min = j;
            
        if min != i
            swap array[min] and array[i];
**/
void sort(int array[], int size)
{
    // Iterate over array
    for (int i = 0; i < size - 1; i++)
    {
        // Smallest element and its position in sorted array
        int smallest = array[i];
        int position = i;
        
        // Look through unsorted part of array
        for (int k = i + 1; k < size - 1; k++)
        {
            // Find the next smallest element
            if (array[k] < smallest)
            {
                smallest = array[k];
                position = k;
            }
        }
        
        // Swap
        int temp = array[i];
        array[i] = smallest;
        array[position] = temp;
    }    
}
