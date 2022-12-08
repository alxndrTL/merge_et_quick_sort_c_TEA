#include "tri_rapide.h"

// ------------------ tri rapide sur un T_data ---------------- //

void echanger(T_elt t[], int i1, int i2) {
	int temp = t[i1];
    t[i1] = t[i2];
    t[i2] = temp;
}

int comparer(T_elt e1, T_elt e2){
	stats.nbComparisons++;
	return e1-e2;
}

//fonction issue du TD
int partionner(T_elt t [], int d, int f){
	int i=d;
    int j=f-1; // On utilise i et j comme « pointeurs » qui se déplacent
	int pivot = f; // pivot=dernier element

	while (i<j) {
		// On déplace i et j jusqu’à trouver des valeurs incohérentes % pivot
		while ((i<j) && (comparer(t[i], t[pivot]) <= 0 )) i++;
		while ((i<j) && (comparer(t[j], t[pivot]) > 0)) j--;

		if (i < j) {
			echanger(t, i, j);
			i++;
            j--; 
		}
	}
	if (comparer(t[i], t[pivot]) <= 0) i++;
	
	echanger(t, i, pivot);
	return i; 
}

void triRapide(T_data d, int n) { //n=nombre d'elements à partir du debut de d.pElt
	int debut = 0;
	int fin = n - 1;
	int iPivot;

	T_elt * A = d.pElt; //tableau à trier

	if(fin>debut){
		iPivot = partionner(A, debut, fin);
		//partionner de debut jusqu'a fin

		triRapide(d, iPivot-debut);
		//tri de début à ipivot-1

		triRapide(genData(d.elt, &A[iPivot+1]), fin-iPivot);
		//tri de ipivot+1 à fin
	}
}

// ------------------ réimplémentation de qsort ---------------- //

//fonction utilisée pour échanger 2 valeurs dans un tableau de type void *
//equivalent de la fonction echanger ci-dessus
void swap(void *a, void *b, size_t size) {
  void *temp = malloc(size);
  memcpy(temp, a, size);
  memcpy(a, b, size);
  memcpy(b, temp, size);
  free(temp);
}

//reimplemntation de qsort
void quicksort(void * base, size_t nmemb, size_t size, int (* compar)(const void *, const void *)){
	//cas de base
    if (nmemb <= 1) return;
        
	char * gauche = base;
    char * droite = base + (nmemb - 1) * size;
	
    //char * pivot = base + (nmemb / 2) * size; //pivot = au milieu
	char * pivot = base + (nmemb - 1) * size; //pivot = dernier elt

	//meme principe que la fonction partionner
    while (gauche <= droite) {
        while (compar(gauche, pivot) < 0) gauche += size;
        while (compar(droite, pivot) > 0) droite -= size;

        if (gauche <= droite) {
			swap(droite, gauche, size);

            gauche += size;
            droite -= size;
        }
    }

    quicksort(base, (droite - (char *) base) / size + 1, size, compar);
	//tri récursif du ss-tableau situé à gauche du pivot

    quicksort(gauche, ((char * ) base + (nmemb * size) - gauche) / size, size, compar);
	//tri récursif du ss-tableau situé à droite du pivot
}