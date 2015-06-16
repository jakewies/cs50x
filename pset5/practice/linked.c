#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct island
{
    char* name;
    struct island* next;
} island;

// Function prototypes
bool search(island* start, char* name);

int main (void)
{      
    // declare islands
    island amity = {"Amity", NULL};
    island craggy = {"Craggy", NULL};
    island isla_nublar = {"Isla Nublar", NULL};
    island shutter = {"Shutter", NULL};
    
    // link islands together
    amity.next = &craggy;
    craggy.next = &isla_nublar;
    isla_nublar.next = &shutter;
    shutter.next = NULL;
    
    // insert new island
    island skull = {"Skull", NULL};
    isla_nublar.next = &skull;
    skull.next = &shutter;
    
    int x = search(&amity, "Amity");
    
    if (x == 0)
        printf("false..\n");
    else 
        printf("true!\n");
}

// search linked list for desired island
bool search(island* start, char* name)
{
    // declare pointer to point to first island
    island* ptr = start;
    
    // iterate through list until NULL    
    while (ptr != NULL)
    {
        if (ptr->name == name)
        {
            return true;
        }
        // set pointer to next island
        ptr = ptr->next;
    }
    return false;
}
