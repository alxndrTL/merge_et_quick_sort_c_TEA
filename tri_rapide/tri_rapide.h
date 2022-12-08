#include <stdlib.h>
#include <string.h> //memcpy

#include "test_utils.h"

// ------------------ tri rapide sur un T_data ---------------- //
void echanger(T_elt t[], int i1, int i2);
int comparer(T_elt e1, T_elt e2);
int Partionnement(T_elt t [], int d, int f);
void quickSort(T_data d, int n);

// ------------------ réimplémentation de qsort ---------------- //
void swap(void *a, void *b, size_t size);
void qsort2(void * base, size_t nmemb, size_t size, int (* compar)(const void *, const void *));
