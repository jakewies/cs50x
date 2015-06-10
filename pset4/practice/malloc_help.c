#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int* pointer_to_int = malloc(sizeof(int));
    
    if (pointer_to_int == NULL)
    {
        printf("Error-- Out of memory\n");
        return 1;
    }
    
    printf("Please enter an integer: ");
    *pointer_to_int = GetInt();
    printf("You entered: %d\n", *pointer_to_int);
    
    free(pointer_to_int);
    
    return 0;
}
