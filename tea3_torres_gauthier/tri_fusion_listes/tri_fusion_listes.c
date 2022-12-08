#include "tri_fusion_listes.h"

// couper la liste de tête head en deux listes, de têtes respectives head_1 et head_2
void couper(T_node *head, T_node **head_1, T_node **head_2){
  //les pointeurs qui vont parcourir la liste
  //slow parcourt une maille par une maille, fast deux mailles par deux mailles
  T_node *fast, *slow;

  //cas dans lequel la liste ne contient que un ou deux élements : il n'y a pas de split à faire
  if (head == NULL || head->pNext == NULL) {
    *head_1 = head;
    *head_2 = NULL;
    return;
  }

  slow = head;
  fast = head->pNext;

  while(fast != NULL){
    fast = fast->pNext;

    if(fast != NULL){
      slow = slow->pNext;
      fast = fast->pNext;
    }
  }

  //fast est arrivé en fin de liste : parcourt terminé

  //la tete de la premiere liste (liste de gauche) est la meme que la tête de la liste d'entrée 
  *head_1 = head;

  //la tete de la seconde liste (liste de droite) est la maille suivant slow
  *head_2 = slow->pNext;
  slow->pNext = NULL; //pour séparer les 2 listes
}

// fusionner deux listes triées
T_node * fusion(T_node * head_1, T_node * head_2){
  T_node * head = NULL;

  //cas de base
  if (head_1 == NULL){
    return head_2;
  } else if (head_2 == NULL){
    return head_1;
  }

  //comme les listes sont triées, on n'a besoin de regarder que l'élément présent de la maille de la tête
  if (head_1->data <= head_2->data){
    head = head_1;
    head->pNext = fusion(head_1->pNext, head_2);
  }else{
    head = head_2;
    head->pNext = fusion(head_1, head_2->pNext);
  }
  return head;
}

// tri fusion d'une liste chaînée
void triFusionListes(T_node **head){
  T_node *head_1, *head_2;

  //cas de base où la liste ne contient que un ou deux éléments
  if (*head == NULL || (*head)->pNext == NULL) {
    return;
  }

  //on coupe la liste en deux moitiés
  couper(*head, &head_1, &head_2);

  //tri récursif de chaque moitié
  triFusionListes(&head_1);
  triFusionListes(&head_2);

  //fusion
  *head = fusion(head_1, head_2);
}