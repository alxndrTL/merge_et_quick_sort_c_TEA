#include "tri_fusion.h"

// --------------- tri fusion sur un T_data --------------- //

int comparer(T_elt e1, T_elt e2){
	stats.nbComparisons++;
	return e1-e2;
}

//fonction reprise du TD
void fusionner(T_elt t [], int d, int m, int f){
	T_elt aux[f - d + 1]; // !! Allocation dynamique sur la pile (standard C99) 
	int i, j, k;

	memcpy(aux, &t[d], (f - d + 1) * sizeof(T_elt));	// Copie des données à fusionner
	stats.nbOperations += (f - d + 1);

	i = 0; j = m - d + 1; k = 0;
	while (i <= m - d && j <= f - d){
		if(comparer(aux[i], aux[j]) <= 0){
			t[d + k++] = aux[i++];	// aux[i] est plus petit : on le place dans t
			stats.nbOperations++;
		}else{
	 		t[d + k++] = aux[j++];	// aux[j] est plus petit : on le place dans t
			stats.nbOperations++;
		}
	}
	for (; i <= m - d; t[d + k++] = aux[i++]); // le reste du tableau gauche
	for (; j <= f - d; t[d + k++] = aux[j++]); // le reste du tableau droit
}

//effectue le tri fusion du tableau contenu dans d, en considérant les n premiers éléments
void triFusion(T_data d, int n){
	int milieu;

	T_elt * A = d.pElt; // tableau à trier

	int debut = 0;
	int fin = n - 1;

	if (n > 1){
		milieu = (debut + fin)/2;

		triFusion(d, milieu-debut+1);
		//tri fusion de debut jusqu'a milieu

		triFusion(genData(d.elt, &A[milieu+1]), fin-milieu);
		//tri fusion de milieu+1 jusqu'a fin

		fusionner(A, debut, milieu, fin);
		//on fusionne les parties triées récursivement
	}
}

// --------------- implémentation de fusionsort --------------- //

//effectue la fusion des sous-tableaux triés du tableau base : de gauche à milieu et de milieu+1 à droite
void merge(void * base, int gauche, int milieu, int droite, size_t size, int (* compar)(const void *, const void *)){
	// taille des 2 tableaux temporaires (de gauche à milieu, et de milieu+1 à droite)
	int n1 = milieu - gauche + 1;
	int n2 = droite - milieu;

	// on va travailler avec des tableaux temporaires dans lesquels on va stocker les données à fusionner
	// on crée les 2 tableaux temporaires
	void * L = malloc(n1 * size);
	void * R = malloc(n2 * size);

	// on copie dans ces tableaux avec memcpy(desination, source, size source)
	memcpy(L, base + gauche * size, n1 * size);
	memcpy(R, base + (milieu + 1) * size, n2 * size);

	// fusion de ces 2 tableaux (meme principe que fonction fusionner)
	int i = 0, j = 0, k = gauche;
	while (i < n1 && j < n2){
		if (compar(L + i * size, R + j * size) <= 0){
			memcpy(base + k * size, L + i * size, size);
			i++;
		}
		else{
			memcpy(base + k * size, R + j * size, size);
			j++;
		}
		k++;
	}

	// on copie le reste du tableau gauche
	while (i < n1){
		memcpy(base + k * size, L + i * size, size);
		i++;
		k++;
	}

	// on copie le reste du tableau droite
	while (j < n2){
		memcpy(base + k * size, R + j * size, size);
		j++;
		k++;
	}

	free(L);
	free(R);
}

void fusionsort_rec(void * base, int gauche, int droite, size_t size, int (* compar)(const void * , const void *)){
	if (gauche < droite){
		int milieu = gauche + (droite - gauche) / 2;

		// trie recursif des 2 tableaux (de gauche jusqu'a milieu, de milieu+1 jusqu'a droite)
		fusionsort_rec(base, gauche, milieu, size, compar);
		fusionsort_rec(base, milieu + 1, droite, size, compar);

		// fusion des tableaux triés
		merge(base, gauche, milieu, droite, size, compar);
	}
}

//deuxieme fonction pour que l'en-tête corresponde à celle demandée
void fusionsort(void * base, size_t nmemb, size_t size, int (* compar)(const void *, const void *)){
	fusionsort_rec(base, 0, nmemb - 1, size, compar);
}
