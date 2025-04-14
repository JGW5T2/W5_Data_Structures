#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024


typedef struct  _bstnode
{
	int item;
	struct  _bstnode *left;
	struct  _bstnode *right;
}BSTNode;

typedef struct _QueueNode
{
	BSTNode *node;
	struct _QueueNode *nextPtr;
	
}QueueNode;


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue;



void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);


int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}


void levelOrderTraversal(BSTNode* root)
{
	if (root == NULL)
        return;
		
	BSTNode *V = root;
    QueueNode *head = NULL, *tail = NULL;
	enqueue(&head,&tail, V);
	while (!isEmpty(head))
	{
		V = dequeue(&head,&tail);
		printf("%d", V->item);
		if(V->left != NULL){
			enqueue(&head,&tail,V->left);
		}
		if(V->right!=NULL){
			enqueue(&head,&tail,V->right);
		}
			
	}

	return;
	
}


void insertBSTNode(BSTNode **node, int value){

	if((*node) == NULL){
		*node = malloc(sizeof(BSTNode));

		if(*node != NULL){
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}

	}
	else{
		if((*node)->item > value)
			insertBSTNode(&((*node)->left),value);

		else if((*node)->item < value)
			insertBSTNode(&((*node)->right),value);

		return;

	}
}


void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node){

	QueueNode *newPtr = malloc(sizeof(QueueNode));

	if(newPtr != NULL){
		newPtr->node = node;
		newPtr->nextPtr = NULL;

		if(isEmpty(*headPtr))
			*headPtr = newPtr;
		else
			(*tailPtr)->nextPtr = newPtr;

		*tailPtr = newPtr; //중요
	}
	return;
}


BSTNode *dequeue(QueueNode **headPtr, QueueNode **tailPtr){
	BSTNode *temp = (*headPtr)->node;
	QueueNode *checker = *headPtr;
	*headPtr = checker->nextPtr;
	
	if (*headPtr == NULL)
		*tailPtr = NULL;
	free(checker);

	return temp;
}


int isEmpty(QueueNode *head)
{
	return head == NULL;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}