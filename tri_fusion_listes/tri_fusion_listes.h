#include <stdlib.h>

#include "elt.h"
#include "list.h"

void couper(T_node *head, T_node **head_1, T_node **head_2);
T_node * fusion(T_node * first, T_node * second);
void triFusion(T_node **head);