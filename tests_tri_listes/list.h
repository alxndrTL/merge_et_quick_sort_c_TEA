#include "elt.h" // T_elt

typedef struct node {
	T_elt data;
	struct node *pNext;
} T_node, * T_list;

T_node * newNode(T_elt e);
T_node * addNode (T_elt e, T_node * n);
void showList(T_list l);
void freeList(T_list l);
T_elt getFirstElt(T_list l);
T_list removeFirstNode(T_list l);


