#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 6
#define WHITE 1
#define GRAY 2
#define BLACK 0

struct adjv {
	int vpos;
	int weight;
	struct adjv *next;
};

struct vertex {
	int key;
	int color;
	int distance;
	struct vertex *parent;
	struct adjv *head;
};

struct Q {
	struct vertex *vertex;
	struct Q *next;
};

struct Q *head=NULL, *tail=NULL;

void Enqueue(struct vertex *new) {
	struct Q *temp;
	temp = malloc(sizeof(struct Q));
	temp->vertex=new;
	if ( head != NULL )
		tail->next=temp; 
	else {
		head = temp;
		tail = temp;
	}
}

struct vertex* Dequeue() {
	struct vertex *first;
	struct Q *temp;
	temp=head;
	first = head->vertex;
	head=head->next;
	free(temp);
	return first;
}

struct vertex *Adj[V];

void Reset(void) {
	int i;
	for(i=0; i < V; i++) {
		Adj[i]->color = WHITE;
		Adj[i]->distance = INT_MAX;
		Adj[i]->parent = NULL;
	}
}

void BFS (struct vertex *s) {
	struct vertex *u, *v;
	struct adjv *temp;
	Reset();
	s->color=GRAY;
	s->distance=0;
	s->parent=NULL;
	Enqueue(s);
	while( head != NULL ) {
		u = Dequeue();
		temp = u->head;
		while ( temp ) {
			v = Adj[(temp->vpos)-1];
			if(v->color == WHITE) {
				v->color = GRAY;
				v->distance = (u->distance) + temp->weight;
				v->parent = u;
				Enqueue(v);
			}
			temp = temp-> next;
		}
		u->color = BLACK;
	}
}

int main()
{
	FILE *fp;
	int i, c, d, s;
	struct adjv *edge;
	fp = fopen("bfsinput","r");
	
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

	BFS(Adj[s-1]);
	printf("\n\nResult of BFS:");
	for(i=0; i < V; i++)
		printf("\nKey: %d, Parent: %d,  Distance from s: %d", Adj[i]->key, (Adj[i]->parent != NULL)?Adj[i]->parent->key:Adj[i]->key, Adj[i]->distance);
	printf("\n");
	fclose(fp);
	return 0;
}
