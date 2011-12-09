#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum {
	V = 8,
	WHITE = 1,
	GRAY = 2,
	BLACK = 0
};

typedef struct adjv adjv;
typedef struct vertex vertex;

int time = 0;

struct adjv {
	int vpos;
	adjv *next;
};

struct vertex {
	int key;
	int color;
	int s;
	int f;
	vertex *p;
	adjv *head;
};


vertex *Adj[V], *Tadj[V];

void Reset(vertex **adj) {
	int i;
	for(i=0; i < V; i++) {
		adj[i]->color = WHITE;
		adj[i]->s = 0 ;
		adj[i]->f = 0 ;
		adj[i]->p = NULL;
	}
}

void DFS_Visit(vertex **adj, vertex *u) {
	time++;
	u->s = time;
	u->color = GRAY;
	adjv *v = u->head;
	while (v) {
		if (adj[(v->vpos)-1]->color == WHITE) {
			adj[(v->vpos)-1]->p = u;
			DFS_Visit(adj, adj[(v->vpos)-1]);
		}
		v=v->next;
	}
	u->color = BLACK;
	u->f = ++time;
}

void DFS (vertex **adj) {
	Reset(adj);
	int i;
	for (i=0; i<V; i++)
		if (adj[i]->color == WHITE)
			DFS_Visit(adj, adj[i]);
}

void DFSR (vertex **adj, vertex **adj2) {
	Reset(adj);
	time=0;
	int seq[2*V],i=0;
	
	for (i=0; i<2*V; i++) 
		seq[i]=-1;
	
	for (i=0; i<V; i++) 
		seq[adj2[i]->f]=i;
	
	for(i=(2*V)-1;i>=0;i--)
		if (seq[i]>-1 && adj[seq[i]]->color == WHITE)
			DFS_Visit(adj, adj[seq[i]]);
	
}

int main()
{
	FILE *fp;
	int i, c, d, s;
	adjv *edge, *redge;
	fp = fopen("input","r");
	
	for(i=0; i<V; i++)
	{
		Adj[i] = (vertex *) malloc(sizeof(vertex));
		Adj[i]->key=i+1;
	}
	
	for(i=0; i<V; i++)
	{
		Tadj[i] = (vertex *) malloc(sizeof(vertex));
		Tadj[i]->key=i+1;
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
		edge->next = Adj[i]->head;
		Adj[i]->head = edge;
		
		redge = (adjv *) malloc(sizeof(adjv));
		redge->vpos =i+1;
		redge->next = Tadj[c-1]->head;
		Tadj[c-1]->head = redge;
	}
	
	printf("\nAdjacency List:\n");
	for(i=0; i < V; i++)
	{
		printf("Key: %d, Neighbors: ", Adj[i]->key);
		edge = Adj[i]->head;
		while(edge) {
			printf("%d ", edge->vpos);
			edge = edge->next;
		}
		printf("\n");
	}
	
	printf("\nTranspose Adjacency List:\n");
	for(i=0; i < V; i++)
	{
		printf("Key: %d, Neighbors: ", Tadj[i]->key);
		redge = Tadj[i]->head;
		while(redge) {
			printf("%d ", redge->vpos);
			redge = redge->next;
		}
		printf("\n");
	}
	
	DFS(Adj);
	DFSR(Tadj, Adj);
	
	printf("\nResult of DFS:\n");
	for(i=0; i < V; i++)
		printf("Key: %d, Parent: %d, Start: %d,\tFinish: %d\n",\
		Adj[i]->key, (Adj[i]->p != NULL)?Adj[i]->p->key:Adj[i]->key, Adj[i]->s, Adj[i]->f);
	
	printf("\nResult of DFSR on Transposed AL:\n");
	for(i=0; i < V; i++)
		printf("Key: %d, Parent: %d, Start: %d,\tFinish: %d\n",\
		Tadj[i]->key, (Tadj[i]->p != NULL)?Tadj[i]->p->key:Tadj[i]->key, Tadj[i]->s, Tadj[i]->f);
	
	printf("\nStrongly Connected Components:\n");
	for(s=1;s<=2*V;s++) {
		i=0;
		while (i<V) {
			if( Tadj[i]->s == s ) {
				printf("%d ", Tadj[i]->key);
				s++;
				i=0;
				continue;
			}
			i++;
		}
		printf("\n");
	}
	
	printf("\n");
	fclose(fp);
	return 0;
}
