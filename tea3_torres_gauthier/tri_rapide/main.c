#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "test_utils.h"
#include "tri_rapide.h"

//prototypes des fonctions à tester :
void triRapide(T_data d, int n);

T_mode m[] = {
	{MODE_TAB_ORDONNE, "ordonne", 0, 1}, 
	{MODE_TAB_ALEATOIRE, "aleatoire", 0, 1}, 
	{MODE_TAB_INVERSE, "inverse", 0, 1}, 
	{MODE_EVAL_X, "x=2.0", 2.0, 0}, 
	{MODE_TAB_ORDONNE, "ordonne (x=59)", 59, 0}, 
	{MODE_TAB_ORDONNE, "hanoi", 1, 0}
};

void showTabInt(int * p, int len){
	for(int i=0; i<len; i++){
		printf("%d -", p[i]);
	}
	printf("\n");
}

//fonction à passer à quicksort pour comparer (dans le cas où les éléments sont des int)
int comparerInt(const void * first, const void * second){
	stats.nbComparisons++;

    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;

    return firstInt - secondInt;
}

//todo : comparerString

int main(void){
	printf("*************** tri rapide sur T_data *********\n");

	int e[6] = {10, 50, 30, 20, 40, 60};
    T_data data = genData(0, e);

	triRapide(data, 6);
	showTabInt(data.pElt, 6);
	
	printf("*************** qsort de C *********\n");

	int intArray[] = {10, 50, 30, 20, 40, 60};

	qsort(intArray, 6, sizeof(int), comparerInt);
	showTabInt(intArray, 6);
	
	printf("*************** qsort réimplémenté *********\n");

	int intArray4[] = {10, 50, 30, 20, 40, 60};

	quicksort(intArray4, 6, sizeof(int), comparerInt);
	showTabInt(intArray, 6);

	/*
	printf("************** graphiques ***************\n");

	T_elt tab [MAX_ELT];
	outputPath = "output";
	srand((unsigned int)time(NULL));
	Test_Fn("TRI RAPIDE", triRapide, tab, MAX_ELT/10, m[MODE_TAB_ALEATOIRE]);
	Test_FnV2("TRI RAPIDE", triRapide, tab, 512, m[MODE_TAB_ALEATOIRE]);
	*/

	/*
	printf("**************** timing ******************\n");

	time_t start = time(NULL);

	for(int j = 0; j<100; j++){
		T_elt tab2 [MAX_ELT];
		for(int i = 0; i<MAX_ELT; i++){
			tab2[i] = rand();
		}
	
		quicksort(tab2, MAX_ELT, sizeof(int), comparerInt);
	}

	time_t end = time(NULL);
	printf("%f\n", difftime(end, start));
	*/

	printf("*********** test tri ************\n");
	T_elt montab[20];
	for(int i = 0; i<20; i++){
		montab[i] = i;
	}

	T_data data4 = {0, montab};

	stats.nbComparisons = 0;

	triRapide(data4, 20);
	showTabInt(data4.pElt, 20);
	printf("%llu\n", stats.nbComparisons);
	
    return 0;
}