#include "tri_fusion_listes.h"

// Split the linked list into two halves
void couper(T_node *head, T_node **head_1, T_node **head_2){
  T_node *fast, *slow;

  //cas dans lequel la liste ne contient que un ou deux élements : il n'y a pas de split à faire
  if (head == NULL || head->pNext == NULL) {
    // If the list has 0 or 1 elements, there is no need to split it
    *head_1 = head;
    *head_2 = NULL;
    return;
  }

  // Use the fast/slow pointer method to split the list in half
  slow = head;
  fast = head->pNext;

  while(fast != NULL){
    fast = fast->pNext;

    if(fast != NULL){
      slow = slow->pNext;
      fast = fast->pNext;
    }
  }

  *head_1 = head;
  *head_2 = slow->pNext;
  slow->pNext = NULL;
}

// Merge two sorted linked lists
T_node * fusion(T_node * head_1, T_node * head_2){
  T_node * head = NULL;

  //cas de base
  if (head_1 == NULL){
    return head_2;
  } else if (head_2 == NULL){
    return head_1;
  }

  // Compare the data in the two lists and add the smaller element to the result list
  if (head_1->data <= head_2->data){
    head = head_1;
    head->pNext = fusion(head_1->pNext, head_2);
  }else{
    head = head_2;
    head->pNext = fusion(head_1, head_2->pNext);
  }
  return head;
}

// Sort a linked list using the merge sort algorithm
void triFusion(T_node **head){
  T_node *head_1, *head_2;

  //cas de base où la liste ne contient que un ou deux éléments
  if (*head == NULL || (*head)->pNext == NULL) {
    return;
  }

  //on coupe la liste en deux moitiés
  couper(*head, &head_1, &head_2);

  //tri récursif de chaque moitié
  triFusion(&head_1);
  triFusion(&head_2);

  //fusion
  *head = fusion(head_1, head_2);
}