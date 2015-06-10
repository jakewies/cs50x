#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int* x;
    int* y;

    x = malloc(sizeof(int));

    *x = 42;
    
    printf("X equals: %d\n", *x);

    y = x;

    *y = 13;
    
    printf("X equals: %d\n", *x);
    
    printf("Y equals: %d\n", *y);
}
