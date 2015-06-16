#include <cs50.h>
#include <stdio.h>

// define struct for linked list
typedef struct node
{
    int n;
    struct node* next;
} node;

// *** Function prototypes *** //
void list(node* head);

int main (void)
{
    // create nodes
    node first = {4, NULL};
    node second = {5, NULL};
    node third = {19, NULL};
    node fourth = {34, NULL};
    
    first.next = &second;
    second.next = &third;
    third.next = &fourth;
    
    // print out nums --> 4, 5, 19, 34
    list(&first);
}

void list(node* start)
{
    // set a pointer = to first num in list
    node* ptr = start;
    
    while (ptr != NULL)
    {
        // print numbers
        printf("%d\n", ptr->n);
        
        // set pointer = to next number
        ptr = ptr->next;
    }
}
