#include <stdio.h>
#include <stdlib.h>

enum {
	MAX = 100
};

typedef struct node node;

struct node {
	int flag;
	int val;
	int op;
	node *left, *right;
};

node* nstack[MAX];
int ntop = -1;

short is_stack_empty()
{
	return (ntop==-1);
}

void push(node* key)
{
	if (ntop < MAX-1)
		nstack[++ntop] = key;
	else printf("\nStack overflow!");
}

node * pop()
{
	if (is_stack_empty())
		printf("\nStack underflow!");
	else return nstack[ntop--];
}

node * gettoken();
node * createtree();
void maketree(node *);
void inorder(node *);
void postorder(node *);

int pf[MAX];

int main()
{
	FILE *fp;
	int ch;
	int stack[MAX], top=-1;
	int i=0;
	
	stack[++top] = '(';
	fp = fopen("infix", "r");
	
	while ( (ch=getc(fp)) != '\n' ) {
		if ( ch >= 'a' && ch <= 'z' ) {
			pf[i++] = ch;
		}
		else if ( ch == '(' )
			stack[++top] = ch;
		else if ( ch == ')' ) {
			while ( stack[top]!='(' )
						pf[i++] = stack[top--];
			if (stack[top]=='(')
				top--;
		}
		else {
			switch (ch) {
				case '*':
				case '/':
					while ( stack[top]!='(' && stack[top]!='+' && stack[top]!='-' )
						pf[i++] = stack[top--];
					stack[++top] = ch;
					break;
				case '+':
				case '-':
					while ( stack[top]!='(' )
						pf[i++] = stack[top--];
					stack[++top] = ch;
					break;
				default:
					printf("\nInvalid expression!");
			}
		}
	}
	
	// For the last ')'
	while ( stack[top]!='(' )
		pf[i++] = stack[top--];
	if (stack[top]=='(')
		top--;

	pf[i]=0;
	fclose(fp);
	printf("The postfix expression is: ");
	for(i=0; pf[i]!=0; i++)
		printf("%c", pf[i]);
	printf("\n");
	
	node* tree = createtree();
	printf("Inorder: ");
	inorder(tree);
	printf("\n");
	printf("Postorder: ");
	postorder(tree);
	printf("\n");
	
	return 0;
}

node * gettoken() {
	static int count=0;
	node *temp;
	if (pf[count] == 0)
		return NULL;
	temp = malloc(sizeof(node));
	if ( pf[count] >= 'a' && pf[count] <= 'z' ) {
		temp->flag = 0;
		temp->val = pf[count];
	}
	else {
		temp->flag = 1;
		temp->op = pf[count];		
	}
	temp->left = NULL;
	temp->right = NULL;
	count++;
	return temp;
}

node * createtree() {
	node *t;
	while ( (t=gettoken()) != NULL ) {
		if ( !(t->flag) )
			push(t);
		else maketree(t);
	}
	t = pop();
	if (!is_stack_empty()) printf("Error!\n");
	else return t;
}

void maketree(node *t) {
	node *p, *q;
	if ( (p = pop()) == NULL ) printf("Error!\n");
	if ( (q = pop()) == NULL ) printf("Error!\n");
	t->left = q;
	t->right = p;
	push(t);
}

void inorder(node *t) {
	if (t!=NULL) {
		if (t->flag)
			printf("(");
		inorder(t->left);
		if (t->flag)
			printf("%c", t->op);
		else
			printf("%c", t->val);
		inorder(t->right);
		if (t->flag)
			printf(")");
	}
}

void postorder(node *t) {
	if (t!=NULL) {
		postorder(t->left);
		postorder(t->right);
		if (t->flag)
			printf("%c", t->op);
		else
			printf("%c", t->val);
	}
}
