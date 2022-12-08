#include "tri_fusion_listes.h"

// Split the linked list into two halves
void split(T_node *head, T_node **front, T_node **back){
  T_node *fast, *slow;

  //cas dans lequel la liste ne contient que un ou deux élements : il n'y a pas de split à faire
  if (head == NULL || head->pNext == NULL) {
    // If the list has 0 or 1 elements, there is no need to split it
    *front = head;
    *back = NULL;
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
  *front = head;
  *back = slow->pNext;
  slow->pNext = NULL;
}

// Merge two sorted linked lists
T_node * merge(T_node * first, T_node * second){
  T_node * result = NULL;

  //cas de base
  if (first == NULL){
    return second;
  } else if (second == NULL){
    return first;
  }

  // Compare the data in the two lists and add the smaller element to the result list
  if (first->data <= second->data){
    result = first;
    result->pNext = merge(first->pNext, second);
  }else{
    result = second;
    result->pNext = merge(first, second->pNext);
  }
  return result;
}

// Sort a linked list using the merge sort algorithm
void merge_sort(T_node **head){
  T_node *first, *second;

  //cas de base où la liste ne contient que un ou deux éléments
  if (*head == NULL || (*head)->pNext == NULL) {
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