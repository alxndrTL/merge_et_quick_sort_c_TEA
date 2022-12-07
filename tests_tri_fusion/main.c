#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int T_elt;

//////////////////////////////////////// tri fusion du TD ////////////////////////////////////////

int comparer(T_elt e1, T_elt e2){
	return e1-e2;
}

void fusionner(T_elt t [], int d, int m, int f){
	T_elt aux[f - d + 1]; // !! Allocation dynamique sur la pile (standard C99) 
	int i, j, k;

	memcpy(aux, &t[d], (f - d + 1) * sizeof(T_elt));	// Copie des données à fusionner
	//stats.nbOperations += (f - d + 1);

	i = 0; j = m - d + 1; k = 0;
	while (i <= m - d && j <= f - d){
		//if(aux[i] <= aux[j]){
		if(comparer(aux[i], aux[j]) <= 0){
			t[d + k++] = aux[i++];	// aux[i] est plus petit : on le place dans t 
		}else{
	 		t[d + k++] = aux[j++];	// aux[j] est plus petit : on le place dans t 
		}
	}
	for (; i <= m - d; t[d + k++] = aux[i++]); // le reste du tableau gauche
	for (; j <= f - d; t[d + k++] = aux[j++]); // le reste du tableau droit
}

void tri_fusion(T_elt t [], int debut, int fin){
	int milieu;
	if (debut < fin){
		milieu = (debut + fin)/2;

		tri_fusion(t, debut, milieu);

		tri_fusion(t, milieu + 1, fin);

		fusionner(t, debut, milieu, fin);
	}
}

////////////////////////////////////////// tri fusion sur un T_data //////////////////////////////////////

typedef struct {
	int elt; 
	int * pElt; 
} T_data;

T_data genData(T_elt e, T_elt * pE){
	T_data d;
	d.elt = e; 
	d.pElt = pE; 
	return d; 
}

void showData(T_data data, int len){
    int * tab = data.pElt;

    for(int i = 0; i<len; i++){
        printf("%d -", tab[i]);
    }
	printf("\n");
}

void tri_fusion_2(T_data d, int n){ // n = nombre d'elements
	int milieu;

	T_elt * A = d.pElt; // Le tableau à trier 
	T_elt e = d.elt; // L'élément recherché (blc)

	int Debut = 0;
	int Fin = n - 1;

	if (n > 1){
		milieu = (Debut + Fin)/2;

		tri_fusion_2(d, milieu-Debut+1);
		//tri fusion du debut jusqu'a milieu

		tri_fusion_2(genData(e, &A[milieu+1]), Fin-milieu);
		//tri fusion du milieu+1 jusqu'a fin

		fusionner(A, Debut, milieu, Fin);
		//on fusionne les parties triées récursivement
	}
}

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

void merge(void * arr, int left, int mid, int right, size_t size, int (comp)(const void *, const void *)){
	// taille des 2 tableaux temporaires (a gauche et a droite du milieu)
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// on crée les 2 tableaux temporaires
	void *L = malloc(n1 * size);
	void *R = malloc(n2 * size);

	// on copie dans ces tableaux avec memcpy(desination, source, size source)
	memcpy(L, arr + left * size, n1 * size);
	memcpy(R, arr + (mid + 1) * size, n2 * size);

	// fusion de ces 2 tableaux
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2){
		if (comp(L + i * size, R + j * size) <= 0){
			memcpy(arr + k * size, L + i * size, size);
			i++;
		}
		else{
			memcpy(arr + k * size, R + j * size, size);
			j++;
		}
		k++;
	}

	// on copie le reste du tableau gauche
	while (i < n1){
		memcpy(arr + k * size, L + i * size, size);
		i++;
		k++;
	}

	// on copie le reste du tableau droit
	while (j < n2){
		memcpy(arr + k * size, R + j * size, size);
		j++;
		k++;
	}

	free(L);
	free(R);
}

void fusion_sort_rec(void * arr, int left, int right, size_t size, int (comp)(const void * , const void *)){
	if (left < right){
		int mid = left + (right - left) / 2;

		// trie recursif des 2 tableaux (de left jusqu'a mid, de mid+1 jusqu'a right)
		fusion_sort_rec(arr, left, mid, size, comp);
		fusion_sort_rec(arr, mid + 1, right, size, comp);

		// fusion des tableaux triés
		merge(arr, left, mid, right, size, comp);
	}
}

void fusionsort(void * arr, size_t n, size_t size, int (comp)(const void *, const void *)){
	fusion_sort_rec(arr, 0, n - 1, size, comp);
}


int main(void){
	printf("********** tri fusion sur T_elt [] ************ \n");

	int e[6] = { 10, 50, 30, 20, 40, 60 };
    T_data data = genData(0, e);
	tri_fusion(data.pElt, 0, 5);
	showData(data, 6);

	printf("********** tri fusion sur T_data ************ \n");

	int f[6] = { 10, 50, 30, 20, 40, 60 };
    T_data data2 = genData(0, f);
	tri_fusion_2(data2, 6);
	showData(data2, 6);

	printf("*************** fsort CHATGPT ***********\n");
	int arr[] = {5, 2, 4, 6, 1, 3};
	fusionsort(arr, 6, sizeof(int), intComparator);
	showTabInt(arr, 6);

    return 0;
}