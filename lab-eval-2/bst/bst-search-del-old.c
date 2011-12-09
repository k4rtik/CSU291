#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

struct node
{
	int key;
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
	return temp;
}

void insert(struct node *p, struct node **x, int key)
{
	if(*x == NULL) 
		*x = create_node(p, key);
	else if( (*x)->key <= key )
		insert(*x, &((*x)->right), key);
	else
		insert((*x), &((*x)->left), key);
}

struct node * search(struct node *x, int key)
{
	while (x!=NULL and x->key != key)
	{
		if( x->key > key )
			x = x->left;
		else x = x->right;
	}
	return x;
}

void delete(int key) {
	struct node *x = search (root, key), *temp;
	if (x==NULL) {
		printf("Key not found. Aborting delete operation!\n");
		return;
	}
	
	//Case 1: No children
	if ( x->left == NULL && x->right==NULL ) {
		temp = x;
		if (temp == root) {
			temp->parent = parent;
		}
		else if( temp->parent->right == temp )
			temp->parent->right = NULL;
		else temp->parent->left = NULL;
		free(x);
		return;
	}
	
	//Case 2: Only one child
	if ( x->left == NULL ) {
		temp = x;
		x = x->right;
		if (temp == root) {
			temp->parent = parent;
		}
		else if( temp->parent->right == temp )
			temp->parent->right = x;
		else temp->parent->left = x;
		x->parent = temp->parent;
		free(temp);
		return;
	}
	else if ( x->right == NULL ) {
		temp = x;
		x = x->left;
		if (temp == root) {
			temp->parent = parent;
		}
		else if( temp->parent->right == temp )
			temp->parent->right = x;
		else temp->parent->left = x;
		x->parent = temp->parent;
		free(temp);
		return;
	}
	
	//Case 3.1: Both children, successor is children
	if ( x->right->left==NULL ) {
		temp = x;
		x = x->right;
		x->left = temp->left;
		x->left->parent = x;
		if (temp == root) {
			temp->parent = parent;
		}
		else if ( temp->parent->right == temp )
			temp->parent->right = x;
		else temp->parent->left = x;
		x->parent = temp->parent;
		free(temp);
		return;
	}
	
}

void inorder(struct node *x)
{
	if(x!=NULL) {
		inorder(x->left);
		printf("%d\n",x->key);
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

	inorder(root);
	printf("\nPlease enter the key to be searched: ");
	scanf("%d", &key);
	delete(key);/*
	if ( temp=search(root, key) )
		printf("Search key found: %d\n", temp->key);
	else
		printf("Key not found!\n");*/

	inorder(root);	
	return 0;
}
