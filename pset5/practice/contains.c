#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct node
{
    // the value to store in this node
    int n;

    // the link to the next node in the list
    struct node* next;
}
node;

node* head = NULL;

// Function declarations
bool contains(int i);

int main(int argc, char* argv[])
{
    // create linked list
    for (int i = SIZE; i > 0; i--)
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

    printf("What value are you looking for? ");
    int i = GetInt();

    if (contains(i))
    {
        printf("Found it! The list contains %d!\n", i);
    }
    else
    {
        printf("Sorry, the list only contains: ");
    	for (node*  ptr = head; ptr != NULL; ptr = ptr->next)
        	printf("%i ", ptr->n);
    }
    printf("\n");
    
    return 0;
}

// search linked list for a number i
bool contains(int i)
{
    // create pointer that points to head
    node* ptr = head;
    
    // iterate thru list until NULL
    while (ptr != NULL)
    {    
        // return true if number found
    	if (ptr->n == i)
        	return true;
        // if number not found, set pointer to next node in list
    	else
        	ptr = ptr->next;
    }
    // return false if reached
    return false;
}

