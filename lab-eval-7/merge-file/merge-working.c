#include <stdio.h>
#include <limits.h>

enum {
	MAX = 100000
};

void merge(FILE *A, int p, int q, int r) {
	int i, j, temp1, temp2;
	int n1 = q - p + 1;
	int n2 = r - q;
	
	FILE *fpL, *fpR;
	fpL = fopen("left","wb+");
	fpR = fopen("right","wb+");
	
	fseek(A, p*sizeof(int), SEEK_SET);
	
	for (i=0; i<n1; i++){
		fread(&temp1, sizeof(int), 1, A);
		fwrite(&temp1, sizeof(int), 1, fpL);
	}
	
	fseek(A, (q+1)*sizeof(int), SEEK_SET);
	
	for (j=0; j<n2; j++) {
		fread(&temp2, sizeof(int), 1, A);
		fwrite(&temp2, sizeof(int), 1, fpR);
	}
	
	temp1=INT_MAX;
	fwrite(&temp1, sizeof(int), 1, fpL);
	fwrite(&temp1, sizeof(int), 1, fpR);
	
	fseek(fpL, 0, SEEK_SET);
	fseek(fpR, 0, SEEK_SET);
	
	fseek(A, p*sizeof(int), SEEK_SET);
	
	fread(&temp1, sizeof(int), 1, fpL);
	fread(&temp2, sizeof(int), 1, fpR);
	
	while( ftell(A) <= (r)*sizeof(int) ) {
		
		if (temp1 <= temp2) {
			fwrite(&temp1, sizeof(int), 1, A);
			fread(&temp1, sizeof(int), 1, fpL);
		}
		else {
			fwrite(&temp2, sizeof(int), 1, A);
			fread(&temp2, sizeof(int), 1, fpR);
		}
	}
	fclose(fpL);
	fclose(fpR);
}

void merge_sort(FILE *A, int p, int r)
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
	int temp, i;
	FILE *fpin;
	fpin = fopen("input","rb+");
	//int A[MAX], i;
	/*for (i=0; i<MAX; i++){
		fread(&temp, sizeof(int), 1, fpin);
		printf("%d\n", temp);
	}*/
	//for (i=0; i < MAX; i++)
	//	scanf("%d", &A[i]);
	
	/*printf("\nInitial array: ");
	for (i=0; i < MAX; i++)
		printf("%d ", A[i]);*/
		
	merge_sort(fpin, 0, MAX-1);
	
	//printf("\nFinal array:");
	//for (i=0; i < MAX; i++)
	//	printf("%d\n", A[i]);
	//printf("\n");
	fseek(fpin, 0, SEEK_SET);
	for (i=0; i<MAX; i++){
		fread(&temp, sizeof(int), 1, fpin);
		printf("%d\n", temp);
	}
	
	fclose(fpin);
	
	return 0;
}