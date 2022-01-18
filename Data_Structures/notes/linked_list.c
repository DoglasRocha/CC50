#include <stdio.h>
#include <stdlib.h>

// making a node of a linked list
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    node *list = NULL;
    node *n = malloc(sizeof(node));
    
    if (n != NULL)
    {
        n->number = 1;
        n->next = NULL;
    }
    
    list = n;
    
    n = malloc(sizeof(node));
    
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    
    n->number = 2;
    n->next = NULL;
    
    list->next = n;
    
    n = malloc(sizeof(node));
    
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }
    
    n->number = 3;
    n->next = NULL;
    
    list->next->next = n;
    
    
    // putting something in the beggining of the list
    n = malloc(sizeof(node));
    
    if (n == NULL)
    {
        free(list->next->next);
        free(list->next);
        free(list);
        return 1;
    }
    
    n->number = 2;
    n->next = list->next;
    
    list->next = n;
    
    // iterating over the list
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    
    // freeing the list
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
    return 0;
}
