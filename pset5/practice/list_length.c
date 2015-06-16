/*
 *
 * This program checks to see if
 * a newly created linked list equals
 * a predetermined size
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// define node data type
typedef struct node
{
    int n;
    struct node* next;
} node;

// init head to null
node* head = NULL;

// Function prototypes
int length(node* start);

int main(int argc, char* argv[])
{
    // create linked list
    for (int i = 0; i < SIZE; i++)
    {
        node* new = malloc(sizeof(node));

        if (new == NULL)
        {
            exit(1);
        }
        new->n = i;
        new->next = head;
        head = new;
    }

    printf("Making sure that list length is indeed %i...\n", SIZE);

    // test length function
    if (length(head) == SIZE)
        printf("Good!\n");
    else
        printf("Linked list does not equal 10!\n");
        
    printf("%d\n", head->n);

    return 0;
}

int length(node* start)
{
    node* ptr = start;
    int counter = 0;
    
    while(ptr != NULL)
    {
        counter++;
        ptr = ptr->next;  
    }
    return counter;
}
