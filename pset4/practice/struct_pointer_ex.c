#include <stdio.h>
#include <cs50.h>

int main (void)
{
    struct person
    {
        char* name;
        int age;
    };
    
    struct person Jake;
    Jake.name = "Jake";
    Jake.age = 24;
    
    struct person* pointer = &Jake;
    
    printf("Jake is %d years old\n", pointer->age);
}
