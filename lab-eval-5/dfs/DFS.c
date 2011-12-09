#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 6
#define WHITE 1
#define GRAY 2
#define BLACK 0
int time = 0;

struct adjv {
	int vpos;
	struct adjv *next;
};

struct vertex {
	int key;
	int color;
	int s;
	int f;
	struct vertex *p;
	struct adjv *head;
};


struct vertex *Adj[V];

void Reset(void) {
	int i;
	for(i=0; i < V; i++) {
		Adj[i]->color = WHITE;
		Adj[i]->s = 0 ;
		Adj[i]->f = 0 ;
		Adj[i]->p = NULL;
	}
}

void DFS_Visit(struct vertex *u) {
	time++;
	u->s = time;
	u->color = GRAY;
	struct adjv *v = u->head;
	while (v) {
		if (Adj[(v->vpos)-1]->color == WHITE) {
			Adj[(v->vpos)-1]->p = u;
			DFS_Visit(Adj[(v->vpos)-1]);
		}
		v=v->next;
	}
	u->color = BLACK;
	u->f = ++time;
}

void DFS () {
	Reset();
	int i;
	for (i=0; i<V; i++)
		if (Adj[i]->color == WHITE)
			DFS_Visit(Adj[i]);
}



int main()
{
	FILE *fp;
	int i, c, d, s;
	struct adjv *edge;
	fp = fopen("dfsinput","r");
	
	for(i=0; i<V; i++)
	{
		Adj[i] = (struct vertex *) malloc(sizeof(struct vertex));
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
			edge = (struct adjv *) malloc(sizeof(struct adjv));
			edge->vpos = c;
			edge->next = Adj[i]->head;
			Adj[i]->head = edge;
		}
		
	printf("Adjacency List:\n");
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
	
	//fscanf(fp, "%d", &s);

	DFS();
	
	printf("\n\nResult of DFS:");
	for(i=0; i < V; i++)
		printf("\nKey: %d, Parent: %d, Start: %d, Finish: %d, Color: %d",\
		 Adj[i]->key, (Adj[i]->p != NULL)?Adj[i]->p->key:Adj[i]->key, Adj[i]->s, Adj[i]->f, Adj[i]->color);
	printf("\n");
	fclose(fp);
	return 0;
}
