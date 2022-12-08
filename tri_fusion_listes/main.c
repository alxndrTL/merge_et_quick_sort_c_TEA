#include <stdio.h>
#include <stdlib.h>

#include "tri_fusion_listes.h"

void display_list(T_node *head) {
  if (head == NULL) {
    return;
  }

  T_node *current = head;

  while (current != NULL) {
    printf("%d ", current->data);
    current = current->pNext;
  }
  
  printf("\n");
}

int main(void){
    T_node *head = NULL;
    head = malloc(sizeof(T_node));
    head->data = 5;
    head->pNext = malloc(sizeof(T_node));
    head->pNext->data = 3;
    head->pNext->pNext = malloc(sizeof(T_node));
    head->pNext->pNext->data = 8;
    head->pNext->pNext->pNext = malloc(sizeof(T_node));
    head->pNext->pNext->pNext->data = 1;
    head->pNext->pNext->pNext->pNext = NULL;

    display_list(head);
    merge_sort(&head);
    display_list(head);
}