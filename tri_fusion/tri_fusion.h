#include <stdlib.h>
#include <string.h> //memcpy

#include "test_utils.h"


// --------------- tri fusion sur un T_data --------------- //
int comparer(T_elt e1, T_elt e2);
void fusionner(T_elt t [], int d, int m, int f);
void triFusion(T_data d, int n);

// --------------- implémentation de fusionsort --------------- //
void merge(void * base, int gauche, int milieu, int droite, size_t size, int (* compar)(const void *, const void *));
void fusionsort_rec(void * base, int gauche, int droite, size_t size, int (* compar)(const void * , const void *));
void fusionsort(void * base, size_t nmemb, size_t size, int (* compar)(const void *, const void *));