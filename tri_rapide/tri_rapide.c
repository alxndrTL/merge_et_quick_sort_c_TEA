#include "tri_rapide.h"

//T_data

void echanger(T_elt t[], int i1, int i2) {
	int temp = t[i1];
    t[i1] = t[i2];
    t[i2] = temp;
}

int comparer(T_elt e1, T_elt e2){
	return e1-e2;
}

int Partionnement(T_elt t [], int d, int f){
	int i=d;
    int j=f-1; // On utilise i et j comme « pointeurs » qui se déplacent
	int pivot = f ; // On choisit le dernier élément comme pivot

	while (i<j) {
		// On déplace i et j jusqu’à trouver des valeurs incohérentes % pivot
		while ((i<j) && (t[i]<=t[pivot])) i++;
		while ((i<j) && (t[j]>t[pivot])) j--;

		if (i < j) {
			echanger(t, i, j);
			i++;
            j--; 
		}
	}
	if (t[i]<=t[pivot]) i++;
	
	echanger(t, i, pivot);
	return i; 
}

void quickSort(T_data d, int n) { //n=nombre d'elements à partir du debut de d.pElt
	int Debut = 0;
	int Fin = n - 1;
	int iPivot;

	T_elt * A = d.pElt; //tableau à trier
	T_elt e = d.elt;

	if(Fin>Debut){
		iPivot = Partionnement(A, Debut, Fin);
		//partionner de debut jusqu'a fin

		quickSort(d, iPivot-Debut);
		//quicksort de début à ipivot-1

		quickSort(genData(e, &A[iPivot+1]), Fin-iPivot);
		//quicksort de ipivot+1 à fin
	}
}

//qsort2
void swap(void *a, void *b, size_t size) {
  void *temp = malloc(size);
  memcpy(temp, a, size);
  memcpy(a, b, size);
  memcpy(b, temp, size);
  free(temp);
}

void qsort2(void * base, size_t nmemb, size_t size, int (* compar)(const void *, const void *))
{
	//cas de base
    if (nmemb <= 1) return;
        
	char * left = base;
    char * right = base + (nmemb - 1) * size;
	
    //char * pivot = base + (nmemb / 2) * size; //pivot = au milieu
	char * pivot = base + (nmemb - 1) * size; //pivot = dernier elt

    while (left <= right) {
        while (compar(left, pivot) < 0) left += size;
        while (compar(right, pivot) > 0) right -= size;

        if (left <= right) {
			swap(right, left, size);

            left += size;
            right -= size;
        }
    }

    qsort2(base, (right - (char *) base) / size + 1, size, compar);
    qsort2(left, ((char * ) base + (nmemb * size) - left) / size, size, compar);
}