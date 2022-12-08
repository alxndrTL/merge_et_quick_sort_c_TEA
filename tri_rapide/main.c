#include <stdio.h>
#include <stdlib.h>

#include "test_utils.h"
#include "tri_rapide.h"

//prototypes des fonctions à tester :

void showTabInt(int * p, int len){
	for(int i=0; i<len; i++){
		printf("%d -", p[i]);
	}
	printf("\n");
}

int comparerInt(const void * first, const void * second){
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;

    return firstInt - secondInt;
}

//todo : comparerString

int main(void){
	printf("*************** tri rapide sur T_data *********\n");

	int e[6] = { 10, 50, 30, 20, 40, 60 };
    T_data data = genData(0, e);
	triRapide(data, 6);
	showTabInt(data.pElt, 6);
	
	printf("*************** qsort de C *********\n");

	int intArray[] = { 10, 50, 30, 20, 40, 60 };
	qsort(intArray, 6, sizeof(int), comparerInt);
	
	showTabInt(intArray, 6);
	
	printf("*************** qsort réimplémenté *********\n");

	int intArray4[] = { 10, 50, 30, 20, 40, 60 };
	quicksort(intArray4, 6, sizeof(int), comparerInt);

	showTabInt(intArray, 6);

    return 0;
}