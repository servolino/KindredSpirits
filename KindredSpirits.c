// Sam Ervolino
// Credit to Dr. Sean Szumlanski for the header file.

#include "KindredSpirits.h"
#include <stdlib.h>

//not as smart as SmartArray, but maintains a great runtime for insertion by updating size while we put things into the array.
// Almost like a tail pointer for linked lists.
typedef struct cleverArray
{
//we will store the traversal of each binary tree in this array.
	 int *array;

	 int size;
} cleverArray;

//auxilary function prototypes
cleverArray *createCleverArray (int length);

int getSize(node *n);

cleverArray *killCleverArray(cleverArray *a);

node *newNode(int data);

cleverArray *put (int data, cleverArray *a);

cleverArray *pre(cleverArray *a, node *n);

cleverArray *post(cleverArray *a, node *n);



node *newNode(int data)
{
//copy of create_node from testcase01.c credit to Sean Szumlanski
	node *n = malloc(sizeof(node));

	n->data = data;
	n->left = n->right = NULL;

	return n;
}


int getSize(node *n)
{
	if(n == NULL)
		return 0;
	else
		return getSize(n->left) + getSize(n->right) + 1;
}

cleverArray *createCleverArray (int length)
{
	cleverArray *new = malloc(sizeof(cleverArray));
	new->array = malloc(sizeof(int) * length);
	new->size = 0;

	return new;
}

cleverArray *killCleverArray(cleverArray *a)
{
//free cleverArrays to avoid mem leaks
	if (a == NULL)
		return NULL;

	free(a->array);
	free(a);

	return NULL;
}

cleverArray *put (int data, cleverArray *a)
{
//inserts data into next open element.
	a->array[a->size] = data;
	a->size++;

	return a;
}

cleverArray *pre(cleverArray *a, node *n)
{
//stores values in preorder traversal
		a = put(n->data, a);
		if(n->left != NULL)
			pre(a, n->left);
		if(n->right!=NULL)
			pre(a, n->right);

	return a;
}

cleverArray *post(cleverArray *b, node *n)
{
//stores values in postorder traversal
		if(n->left != NULL)
			post(b, n->left);
		if(n->right != NULL)
			post(b, n->right);
		b = put(n->data, b);

	return b;
}

int isReflection(node *a, node *b)
{
	int result = 0;

//empty tree check
	if(a == NULL && b == NULL)
		return 1;
	else if (a == NULL && b != NULL)
		return 0;
	else if(a != NULL && b == NULL)
		return 0;

//contrast nodes
	if(a->data != b->data)
		return 0;

//compare nodes and their children
	else if (a->data == b->data)
	{
//compare left subtree of node a to right subtree of node b
		if(a->left != NULL && b->right != NULL)
			result = isReflection(a->left, b->right);
		else if(a->left == NULL && b->right == NULL)
			result = 1;
		else if(a->left == NULL && b->right != NULL)
			result = 0;
		else if(a->left != NULL && b->right == NULL)
			result = 0;

//compare right subtree of node a to left subtree of node b
		if(a->right != NULL && b->left != NULL)
			result = isReflection(a->right, b->left);
		else if (a->right == NULL && b->left == NULL)
			result = 1;
		else if (a->right == NULL && b->left != NULL)
			result = 0;
		else if(a->right != NULL && b->left == NULL)
			result = 0;

		return result;
	}

}

node *makeReflection(node *root)
{
	node *n;

//check if empty tree
	if(root == NULL)
	{
		n = NULL;
		return n;
	}

//make the reflection for each node of the original as long as it isn't NULL
	else
	{
		n = newNode(root->data);

		if(root->left != NULL)
			n->right = makeReflection(root->left);
		if(root->right != NULL)
			n->left = makeReflection(root->right);
	}

	return n;

}

int kindredSpirits(node *a, node *b)
{
	cleverArray *preTrav, *postTrav;
	cleverArray *c, *d;
	int size, i;

//empty tree checks
	if(a == NULL && b == NULL)
		return 1;
	else if(a == NULL && b != NULL)
		return 0;
	else if(a != NULL && b == NULL)
		return 0;

//c and d will store the pre and postorder traversals while they're happening. then 
	c = createCleverArray(getSize(a));
	d = createCleverArray(getSize(b));

//preTrav and postTrav will point to the result of the pre and post functions
	preTrav = pre(c, a);
	postTrav = post(d, b);

//if the first element of each traversal don't match, no need to check the rest.
//Instead we now run the second tree through pre and the first through post
	if(preTrav->array[0] != postTrav->array[0])
	{
		c->array = realloc(c->array, sizeof(int) * getSize(a));
		c->size = 0;
		d->array = realloc(d->array, sizeof(int) * getSize(b));
		d->size = 0;

		preTrav = pre(d, b);
		postTrav = post(c, a);
	}

	if(preTrav->size >= postTrav->size)
		size = preTrav->size;
	else if (postTrav->size > preTrav->size)
		size = postTrav->size;
	
//check every element
	for(i=0; i < size; i++)
		if(preTrav->array[i] != postTrav->array[i])
			return 0;

	killCleverArray(c);
	killCleverArray(d);
	return 1;
}

double difficultyRating(void)
{
	return 4.5;
}

double hoursSpent(void)
{
	return 15.5;
}