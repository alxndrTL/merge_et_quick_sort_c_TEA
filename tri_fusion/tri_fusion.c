#include "tri_fusion.h"

// --------------- tri fusion sur un T_data --------------- //

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
		if(comparer(aux[i], aux[j]) <= 0){
			t[d + k++] = aux[i++];	// aux[i] est plus petit : on le place dans t 
		}else{
	 		t[d + k++] = aux[j++];	// aux[j] est plus petit : on le place dans t 
		}
	}
	for (; i <= m - d; t[d + k++] = aux[i++]); // le reste du tableau gauche
	for (; j <= f - d; t[d + k++] = aux[j++]); // le reste du tableau droit
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

// --------------- implémentation de fusionsort --------------- //

void merge(void * arr, int left, int mid, int right, size_t size, int (comp)(const void *, const void *)){
	// taille des 2 tableaux temporaires (a gauche et a droite du milieu)
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// on crée les 2 tableaux temporaires
	void * L = malloc(n1 * size);
	void * R = malloc(n2 * size);

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
