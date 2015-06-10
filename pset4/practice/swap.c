// Swap two values using pointers

#include <stdio.h>

void swap(int* a, int* b);

int main(void)
{
    int x = 45;
    int y = 21;

    // print original values
    printf("x is equal to: %d\n", x);
    printf("y is equal to: %d\n", y);
    
    // swap x and y
    swap(&x, &y);
    
    printf("Swapped!\n");
    
    // print new values
    printf("x is now equal to: %d\n", x);
    printf("y is now equal to: %d\n", y);   
}

void swap(int* a, int* b) 
{
    // create temporary place holder
    int temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
}
