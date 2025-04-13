#include <stdio.h>
#include <stdlib.h>

typedef struct  _btnode{
    int item;
    struct  _btnode *left;
    struct  _btnode *right;
    
}BTNode;

typedef struct _stackNode{ //포인터용입니다ㅏㅏㅏㅏㅏ 제발 기억해 제발ㄹㄹㄹㄹ류ㅠㅠㅠㅠㅠ
    BTNode *BTNode;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
    StackNode *top;
}Stack;


int identical(BTNode *tree1, BTNode *tree2);

BTNode* createBTNode(int item);

BTNode* createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;
    char e;
    BTNode *root1, *root2;

    root1 = NULL;
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("Please input your choice(1/2/3/0): ");
        if(scanf("%d", &c) > 0)

        {

            switch(c)
            {
            case 1:
                removeAll(&root1);
                printf("Creating tree1:\n");
                root1 = createTree();
                printf("The resulting tree1 is: ");
                printTree(root1);
                printf("\n");
                break;
            case 2:
                removeAll(&root2);
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);
                if(s){
                printf("Both trees are structurally identical.\n");
                }
                else{
                printf("Both trees are different.\n");
                }
                removeAll(&root1);
                removeAll(&root2);
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }
    return 0;
}


int identical(BTNode *tree1, BTNode *tree2){

    if (tree1 == NULL && tree2 == NULL)  
        return 1;

    if (tree1 == NULL || tree2 == NULL)  
        return 0;
    
    if(tree1->item != tree2->item)
        return 0;

    if (identical(tree1->left, tree2->left) == 0)
        return 0;

    if (identical(tree1->right, tree2->right) == 0)
        return 0;

    return 1;

}





BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;  //만들어낸 뉴노드의 주소값을 리턴턴

}

BTNode *createTree(){
    Stack stk;  //체크용 T and T and B
    BTNode *root, *temp;
    char s;
    int item;

    stk.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0){
        root = createBTNode(item);
        push(&stk,root);
    }

    else{
        scanf("%c",s);
    }

    while ((temp = pop(&stk)) != NULL) // while 돌때마다 temp 재정의
    {
        printf("Enter an integer value for the Left child of %d: ", temp->item);
        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stk,temp->right); //여기서 넥트스 생성됨
        if(temp->left != NULL)
            push(&stk,temp->left);  //여기서 넥트스 생성됨
    }
    return root;
}


void push( Stack *stk, BTNode *node){
    StackNode *temp;
    temp = malloc(sizeof(StackNode)); //동적할당됨(언전간 놓아줄 것)
    if(temp == NULL)
        return;
    temp->BTNode = node;
    if(stk->top == NULL){
        stk->top = temp;
        temp->next = NULL;
    }
    else{  // 이미 top이 존재할때 로직, 응용할 곳이 많을 거 같으니 주의 깊게 봐둘 것
        temp->next = stk->top;
        stk->top = temp;
    }
    return;
}


BTNode *pop( Stack *stk){
    BTNode *temp;
    StackNode *checker;
    
    temp = NULL;
    if (stk == NULL || stk->top == NULL)
        return temp;
    checker = stk->top;
    temp = checker->BTNode;
    stk->top = checker->next;
    free(checker);
    checker = NULL;
    return temp;

}



void printTree(BTNode *node){
    if(node == NULL) return;

    printTree(node->left);
    printf("%d", node->item);
    printTree(node->right);
}

void removeAll(BTNode **node){
    if(*node == NULL) return;

    removeAll(&((*node)->left));
    removeAll(&((*node)->right));
    free(*node);
    *node = NULL;

    return;


}