#include <stdio.h>
#include <limits.h>

enum {
	MAX = 1000000
};

void merge(int *A, int p, int q, int r) {
	int i, j, k;
	int n1 = q - p + 1;
	int n2 = r - q;
	int L[n1+1], R[n2+1];
	for (i=0; i<n1; i++)
		L[i] = A[p + i];
	for (j=0; j<n2; j++)
		R[j] = A[q + j + 1];
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;
	i = 0;
	j = 0;
	for (k=p; k<=r; k++)
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
}

void merge_sort(int *A, int p, int r)
{
	int q;
	if (p<r) {
		q = (p + r)/2;
		merge_sort(A, p, q);
		merge_sort(A, q+1, r);
		merge(A, p, q, r);
	}
}

int main()
{
	int A[MAX], i;
	for (i=0; i < MAX; i++)
		scanf("%d", &A[i]);
	
	/*printf("\nInitial array: ");
	for (i=0; i < MAX; i++)
		printf("%d ", A[i]);*/
		
	merge_sort(A, 0, MAX-1);
	
	//printf("\nFinal array:");
	for (i=0; i < MAX; i++)
		printf("%d\n", A[i]);
	//printf("\n");
	
	return 0;
}