#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

struct node
{
	int key;
	int size;
	struct node *left, *right, *parent;
} *root=NULL, *parent=NULL;

struct node* create_node(struct node *p, int key)
{
	struct node *temp;
	temp = malloc(sizeof(struct node));
	temp->key = key;
	temp->parent = p;
	temp->left = NULL;
	temp->right = NULL;
	temp->size = 0;
	return temp;
}

void resize(struct node *x, int value) 
{
	while (x != root) {
		if(x->parent->left == x)
			x->parent->size += value;
		x = x->parent;
	}
}

void insert(struct node *p, struct node **x, int key)
{
	if(*x == NULL) 
	{
		*x = create_node(p, key);
		resize(*x,1);
	}
	else if( (*x)->key <= key )
		insert(*x, &((*x)->right), key);
	else
		insert((*x), &((*x)->left), key);
}

struct node * search(struct node *x, int key)
{
	while (x!=NULL && x->key != key)
	{
		if( x->key > key )
			x = x->left;
		else x = x->right;
	}
	return x;
}

void transplant(struct node *u, struct node *v)
{
	if((u->parent) == NULL)
		root = v;
	else if(u == (u->parent)->left)
		(u->parent)->left = v;
	else
		(u->parent)->right = v;
	if(v != NULL)
		v->parent = u->parent;
}

struct node * treemin(struct node *u)
{
	while((u->left)!=NULL)
		u=u->left;
	return u;
}

void delete(int key) {
	struct node *x = search (root, key), *next;
	if (x==NULL) {
		printf("Key not found. Aborting delete operation!\n");
		return;
	}

	if (x->left == NULL)
	{
		transplant(x, x->right);
		x->parent->size--;
	}
	else if( x->right == NULL )
		transplant(x, x->left);
	else {
		next = treemin(x->right);
		if(next->right!=NULL && (next->parent) != x) {
			transplant(next, next->right);
			(next->right)->parent = next->parent;
		}
		if((next->parent) == x) {
			transplant(next, next->right);
			next->right = x->right;
			if(next->right!=NULL)
				(next->right)->parent = next;
		}
		else
			next->parent->left = next->right;
		
		transplant(x, next);
		next->left = x->left;
		next->size = x->size;
		(next->left)->parent = next;
		next->right = x->right;
		if(next->right!=NULL)
			(next->right)->parent = next;
	}
	resize(x->parent, -1);
	free(x);
}

void inorder(struct node *x)
{
	if(x!=NULL) {
		inorder(x->left);
		printf("%d %d\n",x->key,x->size);
		inorder(x->right);
	}
}

int main()
{
	int i;
	int key;
	struct node *temp;
	
	for (i = 0; i < LENGTH; i++) {
		scanf("%d", &key);
		insert(parent, &root, key);
	}
	printf("\nInput:\n");
	inorder(root);
	printf("\nPlease enter the key to be deleted: ");
	scanf("%d", &key);
	delete(key);/*
	if ( temp=search(root, key) )
		printf("Search key found: %d\n", temp->key);
	else
		printf("Key not found!\n");*/

	inorder(root);	
	return 0;
}
