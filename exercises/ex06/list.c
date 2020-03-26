/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
*
* val: value to store in the node.
* next: pointer to the next node
*
* returns: pointer to a new node
*/
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}


/* Prints the values in a list.
*
* list: pointer to pointer to Node
*/
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
*
* list: pointer to pointer to Node
*
* returns: int or -1 if the list is empty
*/
int pop(Node **list) {
    // Get the pointer to the current head
    Node* head = *list;
    // If there is a head
    if (head) {
      // Move the head_ptr to te next node and update the list
      *list = head->next;
      return head->val;
    }
    return -1;
}


/* Adds a new element to the beginning of the list.
*
* list: pointer to pointer to Node
* val: value to add
*/
void push(Node **list, int val) {
    Node* head = *list;
    Node* new = make_node(val, head);
    *list = new;
}


/* Removes the first element with the given value
*
* Frees the removed node.
*
* list: pointer to pointer to Node
* val: value to remove
*
* returns: number of nodes removed
*/
int remove_by_value(Node **list, int val) {
    Node* current = *list;
    Node* prev = *list;
    while (current && current->val != val) {
      prev = current;
      current = current->next;
    }
    if (current) {
      Node* old_next = current->next;
      prev->next = old_next;
      free(current);
      return 1;
    }
    return 0;
}


/* Reverses the elements of the list.
*
* Does not allocate or free nodes.
*
* list: pointer to pointer to Node
*/
void reverse(Node **list) {
  Node* current = *list;
  Node* prev = NULL;
  Node* next = NULL;
  while (current) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  *list = prev;
}


int main() {
    Node *head = make_node(1, NULL);
    head->next = make_node(2, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(4, NULL);

    printf("Testing initialization\n");
    Node **list = &head;
    print_list(list);

    printf("Testing pop\n");
    int retval = pop(list);
    print_list(list);

    printf("Testing push\n");
    push(list, retval+10);
    print_list(list);

    printf("Testing remove by value that exists\n");
    remove_by_value(list, 3);
    print_list(list);

    printf("Testing remove by value that does not exist\n");
    remove_by_value(list, 7);
    print_list(list);
    
    printf("Testing reverse\n");
    reverse(list);
    print_list(list);
}
