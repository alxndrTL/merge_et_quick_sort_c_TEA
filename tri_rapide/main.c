#include <stdio.h>
#include <stdlib.h>

#include "test_utils.h"
#include "tri_rapide.h"

//prototypes des ofnctions à tester 


int comparerInt(const void * first, const void * second){
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;

    return firstInt - secondInt;
}

void showTab(T_elt t[], int taille){
    for(int i = 0; i<taille; i++){
        printf("%d -", t[i]);
    }
	printf("\n");
}

void showData(T_data data, int len){
    int * tab = data.pElt;

    for(int i = 0; i<len; i++){
        printf("%d -", tab[i]);
    }
	printf("\n");
}

void showTabInt(int * p, int len){
	for(int i=0; i<len; i++){
		printf("%d -", p[i]);
	}
	printf("\n");
}

int main(void){
	printf("*************** tri rapide sur T_data *********\n");

	int e[6] = { 10, 50, 30, 20, 40, 60 };
    T_data data = genData(0, e);
	//showData(data, 6);
	quickSort(data, 6);
	showData(data, 6);
	
	printf("***************quicksort de C *********\n");

	int intArray[] = { 10, 50, 30, 20, 40, 60 };
	qsort(intArray, 6, sizeof(int), comparerInt);
	
	showTabInt(intArray, 6);
	
	printf("***************quicksort de CHATGPT *********\n");

	int intArray4[] = { 10, 50, 30, 20, 40, 60 };
	qsort2(intArray4, 6, sizeof(int), comparerInt);

	showTabInt(intArray, 6);

    return 0;
}