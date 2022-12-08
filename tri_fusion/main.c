#include <stdio.h>
#include <stdlib.h>

#include "test_utils.h"
#include "tri_fusion.h"


int intComparator (const void * first, const void * second ){
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}

void showTabInt(int * p, int len){
	for(int i=0; i<len; i++){
		printf("%d -", p[i]);
	}
	printf("\n");
}

int main(void){
	printf("********** tri fusion sur T_data ************ \n");

	int f[6] = { 10, 50, 30, 20, 40, 60 };
    T_data data2 = genData(0, f);
	tri_fusion_2(data2, 6);
	showTabInt(data2.pElt, 6);

	printf("*************** fusionsort ***********\n");
	int arr[] = {5, 2, 4, 6, 1, 3};
	fusionsort(arr, 6, sizeof(int), intComparator);
	showTabInt(arr, 6);

    return 0;
}