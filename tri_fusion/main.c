#include <stdio.h>
#include <stdlib.h>

#include "test_utils.h"
#include "tri_fusion.h"


//fonction à passer à fusionsort pour comparer (dans le cas où les éléments sont des int)
int comparerInt(const void * e1, const void * e2){
    int e1_int = * (const int *) e1;
    int e2_int = * (const int *) e2;
    return e1_int - e2_int;
}

void showTabInt(int * p, int len){
	for(int i=0; i<len; i++){
		printf("%d -", p[i]);
	}
	printf("\n");
}

int main(void){
	printf("********** tri fusion sur T_data ************ \n");

	int tab1[6] = {10, 50, 30, 20, 40, 60};
    T_data data = genData(0, tab1);
	triFusion(data, 6);
	showTabInt(data.pElt, 6);

	printf("*************** fusionsort ***********\n");
	int tab2[] = {10, 50, 30, 20, 40, 60};
	fusionsort(tab2, 6, sizeof(int), comparerInt);
	showTabInt(tab2, 6);

    return 0;
}