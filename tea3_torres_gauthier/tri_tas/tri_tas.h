#include "test_utils.h"

#define MAXIMIER
//#define MINIMIER

#define iLCHILD(i) 			(2*i)+1
#define iRCHILD(i) 			(2*i)+2

void echanger(T_elt *p, int i, int j);
int comparer(T_elt a, T_elt b);

void tassifier(T_data d, int n, int root);
void heap_sort(T_data d, int n);