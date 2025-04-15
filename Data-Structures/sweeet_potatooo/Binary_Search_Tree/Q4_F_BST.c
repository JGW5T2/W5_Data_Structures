//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS1(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
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
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS1(root); // You need to code this function
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

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS1(BSTNode *root)
{
	// 스택(**stack**)을 사용하여 이진 탐색 트리의 후위 순회(post-order traversal)를 출력하는 
	// 반복적 C 함수 `postOrderIterativeS1()`을 작성하세요.
	// **정수를 스택에 추가하거나 제거할 때는 반드시 `push()` 또는 `pop()` 연산만 사용해야 합니다.**
	// 또한, 함수 시작 시 **스택이 비어있지 않다면 먼저 스택을 비워야 합니다.**
	Stack s;
	s.top = NULL;

	BSTNode *current = root;
	BSTNode *lastVisited = NULL;

	while (current != NULL || !isEmpty(&s))
	{
			if (current != NULL)
			{
					// 현재 노드를 스택 s에 push한 후 왼쪽 자식으로 이동합니다.
					push(&s, current);
					current = current->left;
			}
			else
			{
					// 스택 s의 top에 있는 노드를 확인합니다.
					BSTNode *peekNode = peek(&s);
					// 만약 peek한 노드의 오른쪽 자식이 존재하고, 아직 방문하지 않았다면
					if (peekNode->right != NULL && lastVisited != peekNode->right)
					{
							// 오른쪽 서브트리를 처리하기 위해 current를 오른쪽 자식으로 설정합니다.
							current = peekNode->right;
					}
					else
					{
							// 오른쪽 자식이 없거나 이미 방문한 경우,
							// 스택 s에서 노드를 pop하여 출력한 후, 마지막 방문 노드로 저장합니다.
							printf("%d ", peekNode->item);
							lastVisited = pop(&s);
					}
			}
	}
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
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
