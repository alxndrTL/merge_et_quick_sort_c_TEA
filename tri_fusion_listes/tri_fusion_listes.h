#include <stdlib.h>

#include "elt.h"
#include "list.h"

void split(T_node *head, T_node **front, T_node **back);
T_node * merge(T_node * first, T_node * second);
void merge_sort(T_node **head);