#include <stdlib.h>
#include <string.h> //memcpy

#include "test_utils.h"


// --------------- tri fusion sur un T_data --------------- //
int comparer(T_elt e1, T_elt e2);
void fusionner(T_elt t [], int d, int m, int f);
void tri_fusion_2(T_data d, int n);

// --------------- implémentation de fusionsort --------------- //
void merge(void * arr, int left, int mid, int right, size_t size, int (comp)(const void *, const void *));
void fusion_sort_rec(void * arr, int left, int right, size_t size, int (comp)(const void * , const void *));
void fusionsort(void * arr, size_t n, size_t size, int (comp)(const void *, const void *));