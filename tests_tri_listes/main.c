#include <stdio.h>
#include <stdlib.h>

//#include "elt.h"
//#include "list.h"

typedef struct node {
  int data;
  struct node *next;
} node;

// Split the linked list into two halves
void split(node *head, node **front, node **back){
  node *fast, *slow;

  //cas dans lequel la liste ne contient que un ou deux élements : il n'y a pas de split à faire
  if (head == NULL || head->next == NULL) {
    // If the list has 0 or 1 elements, there is no need to split it
    *front = head;
    *back = NULL;
    return;
  }

  // Use the fast/slow pointer method to split the list in half
  slow = head;
  fast = head->next;
  while(fast != NULL){
    fast = fast->next;
    if(fast != NULL){
      slow = slow->next;
      fast = fast->next;
    }
  }
  *front = head;
  *back = slow->next;
  slow->next = NULL;
}

// Merge two sorted linked lists
node * merge(node * first, node * second) {
  node * result = NULL;

  //cas de base
  if (first == NULL){
    return second;
  } else if (second == NULL){
    return first;
  }

  // Compare the data in the two lists and add the smaller element to the result list
  if (first->data <= second->data){
    result = first;
    result->next = merge(first->next, second);
  }else{
    result = second;
    result->next = merge(first, second->next);
  }
  return result;
}

// Sort a linked list using the merge sort algorithm
void merge_sort(node **head) {
  node *first, *second;

  //cas de base où la liste ne contient que un ou deux éléments
  if (*head == NULL || (*head)->next == NULL) {
    return;
  }

  //split
  split(*head, &first, &second);

  //tri récursif de chaque moitié
  merge_sort(&first);
  merge_sort(&second);

  //fusion
  *head = merge(first, second);
}

// function to display the elements of the linked list
void display_list(node *head) {
  // check if the linked list is empty
  if (head == NULL) {
    printf("Linked list is empty\n");
    return;
  }

  // create a pointer to traverse the linked list
  node *current = head;

  // loop through the linked list and print each element
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }

  // print a new line after all the elements have been printed
  printf("\n");
}

int main(void){
    node *head = NULL;
    head = malloc(sizeof(node));
    head->data = 5;
    head->next = malloc(sizeof(node));
    head->next->data = 3;
    head->next->next = malloc(sizeof(node));
    head->next->next->data = 8;
    head->next->next->next = malloc(sizeof(node));
    head->next->next->next->data = 1;
    head->next->next->next->next = NULL;

    display_list(head);
    merge_sort(&head);
    display_list(head);
}