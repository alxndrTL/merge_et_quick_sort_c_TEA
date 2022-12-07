#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int T_elt;

//////////////////////////////////////// tri rapide du TD ////////////////////////////////////////

void echanger(T_elt t[], int i1, int i2) {
	int temp = t[i1];
    t[i1] = t[i2];
    t[i2] = temp;
}

int Partitionner(T_elt t [], int d, int f){ 
	int i=d;
    int j=f-1; // On utilise i et j comme « pointeurs » qui se déplacent
	int pivot = f ; // On choisit le dernier élément comme pivot

	while (i<j) {
		// On déplace i et j jusqu’à trouver des valeurs incohérentes % pivot
		while ((i<j) && (t[i]<=t[pivot])) i++ ;	
		while ((i<j) && (t[j]>t[pivot])) j-- ;

		if (i < j) {
			echanger(t, i, j);
			i++;
            j--; 
		}
	}
	if (t[i]<=t[pivot]) i++ ; // Cf. ci-contre 
	echanger(t, i, pivot) ;
	return i ; 
}

void showTab(T_elt t[], int taille){
    for(int i = 0; i<taille; i++){
        printf("%d -", t[i]);
    }
	printf("\n");
}

void Tri_rapide(T_elt t[], int debut, int fin) {
    int iPivot;
    if (fin > debut) {
        iPivot = Partitionner(t, debut, fin);
		//Partitionner renvoit l'index du pivot, en prenant comme pivot le dernier elt
		//fait la procédure décrite sur la feuille (il y a des échanges)

        Tri_rapide(t, debut, iPivot - 1);
		//tri recursif à gauche du pivot

        Tri_rapide(t, iPivot + 1, fin);
		//tri recursif à droite du pivot
    }
}

//////////////////////////////////////// T_data ////////////////////////////////////////

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

//////////////////////////////////////// reimplementation de qsort ////////////////////////////////////////

int intComparator (const void * first, const void * second ) {
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

int main(void){
	printf("*************** tri rapide sur T_data *********\n");

    //int e[5] = {100, 99, 98, 97, 96};
	int e[6] = { 10, 50, 30, 20, 40, 60 };
    T_data data = genData(0, e);
	//showData(data, 6);
	quickSort(data, 6);
	showData(data, 6);
	
	printf("***************quicksort de C *********\n");

	int intArray[] = { 10, 50, 30, 20, 40, 60 };
	qsort(intArray, 6, sizeof(int), intComparator);
	
	for(int i=0; i<6; i++ ){
        printf( "%d - ", intArray[i]);
    }
    printf( "\n" );
	
	printf("***************quicksort de CHATGPT *********\n");

	int intArray4[] = { 10, 50, 30, 20, 40, 60 };
	qsort2(intArray4, 6, sizeof(int), intComparator);

	for(int i=0; i<6; i++ ){
        printf( "%d - ", intArray4[i]);
    }
    printf( "\n" );

    return 0;
}