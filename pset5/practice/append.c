#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node
{
    // the value to store in this node
    int n;

    // the link to the next node in the list
    struct node* next;
}node;

// init head to null
node* head = NULL;

// Function prototypes
void append(int i);

int main(int argc, char* argv[])
{
    // creating list
    printf("Appending ints 0-%i onto the list...\n", SIZE - 1);
    for (int i = 0; i < SIZE; i++)
    {
        append(i);
    }
    printf("done!\n");

    // printing out list
    printf("Your list contains: ");
    for (node*  ptr = head; ptr != NULL; ptr = ptr->next)
    {
        printf("%i ", ptr->n);
    }
    printf("\n");

    return 0;
}

void append(int i)
{
    // create new node
    node* new = malloc(sizeof(node));
	
    if (new == NULL)
    {
    	exit(1);
    }

    // init new node
    new->n = i;
    new->next = NULL;
    
    //check if new is head
    node* prev = NULL;
    
    for (node* cur = head; cur != NULL; cur = cur->next)
    {
        prev = cur;
    }

    // if the list is empty, prepend
    if (prev == NULL)
    {
        head = new;
    }

    // else add new node to end of list
    else
    {
        prev->next = new;
    }
}
