#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10000

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

// void delete()

// void search()

void print(struct node *x)
{
	if((x->left)!=NULL)
		print(x->left);
	printf("%d\n",x->key);
	if((x->right)!=NULL)
		print(x->right);
}

int main()
{
	int i;
	int key;
	
//	printf("Enter 10 Keys : ");
	for (i = 0; i < LENGTH; i++) {
		scanf("%d", &key);
		insert(parent, &root, key);
	}

	print(root);
	
	return 0;
}
