#include <stdio.h>
#include <stdlib.h>

#include "tri_fusion_listes.h"

int main(void){
    T_node * head = newNode(1);
    head = addNode(8, head);
    head = addNode(3, head);
    head = addNode(5, head);

    showList(head);
    triFusion(&head);
    showList(head);
}