#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

enum {
	V = 5
};

typedef struct adjv adjv;
typedef struct vertex vertex;
typedef struct Q Q;

struct adjv {
	int vpos;
	int weight;
	adjv *next;
};

struct vertex {
	int key;
	int d;
	vertex *p;
	adjv *head;
};

vertex *Adj[V], *S[V];

void swap(int A[], int i, int j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

// Priority Queue
int heap_size=V;

void heapify(int A[], int i) {
	int smallest;
	int l = LEFT(i);
	int r = RIGHT(i);
	if (l <= heap_size && A[i] > A[l])
		smallest = l;
	else smallest = i;
	if (r <= heap_size && A[smallest] > A[r])
		smallest = r;
	if (smallest != i)
	{
		swap(A, i, smallest);
		heapify(A, smallest);
	}
}

void build_heap(int A[]) {
	int i;
	heap_size = V;
	for (i = V/2; i > 0; i -= 1)
	{
		heapify(A, i);
	}
}

int extract_min(int A[]){
	if (heap_size < 1)
	{
		printf("\nHeap underflow! Aborting extracting operation!\n");
		return 0;
	}
	int min = A[1];
	A[1] = A[heap_size--];
	heapify(A, 1);
	return min;
}
// Priority Queue implementation ends here



void InitializeSingleSource(int s) {
	int i;
	for(i=0; i < V; i++) {
		Adj[i]->d = INT_MAX;
		Adj[i]->p = NULL;
	}
	Adj[s-1]->d = 0;
}

void Relax(vertex *u, vertex *v, int weight) {
	if ( u->d > (v->d + weight) ) {
		v->d = u->d + weight;
		v->p = u;
	}
}

void Dijkstra(int s) {
	InitializeSingleSource(s);
	
	// Initializing S
	int i;
	for(i=0; i<V; i++)
		S[i] = (vertex *) malloc(sizeof(vertex));
	
	// Initializing Q
	//build_heap(arr)
}

int main()
{
	FILE *fp;
	int i, c, d, s;
	adjv *edge;
	
	fp = fopen("input","r");
	
	for(i=0; i<V; i++)
	{
		Adj[i] = (vertex *) malloc(sizeof(vertex));
		Adj[i]->key=i+1;
	}

	i = 0;
	while ( i < V ) {
		fscanf(fp, "%d", &c);
		if(c==0) {
			i++;
			continue;
		}
		fscanf(fp, "%d", &d);
		edge = (adjv *) malloc(sizeof(adjv));
		edge->vpos = c;
		edge->weight = d;
		edge->next = Adj[i]->head;
		Adj[i]->head = edge;
	}
		
	printf("Adjacency List:");
	for(i=0; i < V; i++)
	{
		printf("\nKey: %d, Neighbors: ", Adj[i]->key);
		edge = Adj[i]->head;
		while(edge) {
			printf("%d ", edge->vpos);
			edge = edge->next;
		}
	}
	
	fscanf(fp, "%d", &s);
	
	//Dijkstra(s);
	/*
	
	int arr[V];
	for (i = 0; i < V; i += 1)
		scanf("%d", &arr[i]);

//extract min
	build_heap(arr);
	for (i = 0; i < heap_size; i += 1)
		printf("%d ", arr[i]);
	
	printf("\n");

	printf("\nMin: %d\n", extract_min(arr));
// upto here

	printf("\nOutput starts here:\n===================\n");

	for (i = 0; i < heap_size; i += 1)
		printf("%d\n", arr[i]);
*/
	printf("\n");

	return 0;
}
