//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
   CE1007/CZ1007 자료구조
Lab Test: Section E - Binary Trees Questions
   Lab Test: 섹션 E - 이진 트리 문제
Purpose: Implementing the required functions for Question 5
   목적: Question 5에 필요한 함수를 구현합니다. */


//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode (BTNode 정의는 변경하면 안 됩니다)

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;


///////////////////////// function prototypes / 함수 원형 ////////////////////////////////////

// You should not change the prototypes of these functions (이 함수들의 원형은 변경하면 안 됩니다)
void mirrorTree(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stack, BTNode *node);
BTNode* pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() / 메인 함수 /////////////////////////////////////////////

int main()
{
    char e;
    int c;
    BTNode *root;

    c = 1;
    root = NULL;


    printf("1: Create a binary tree. / 1: 이진 트리 생성\n");
    printf("2: Mirror the binary tree. / 2: 이진 트리를 미러 형태로 변환\n");
    printf("0: Quit; / 0: 종료\n");


    while(c != 0)
    {
        printf("Please input your choice(1/2/0): / 메뉴를 선택하세요(1/2/0): ");
        if( scanf("%d",&c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: / 결과 이진 트리: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                mirrorTree(root);
                printf("Mirror binary tree is: / 미러 변환된 이진 트리: ");
                printTree(root);
                printf("\n");
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown; / 알 수 없는 선택입니다.\n");
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

//////////////////////////////////////////////////////////////////////////////////

void mirrorTree(BTNode *node)
{
	/* add your code here (여기에 코드를 작성하세요) */
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


BTNode *createTree()
{
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL. / 이진 트리에 추가할 정수를 입력하세요. 문자를 입력하면 NULL로 처리됩니다.\n");
    printf("Enter an integer value for the root: / 루트 값을 입력하세요: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stack,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stack)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: / 왼쪽 자식 값을 입력하세요: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: / 오른쪽 자식 값을 입력하세요: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stack,temp->right);
        if(temp->left != NULL)
            push(&stack,temp->left);
    }
    return root;
}

void push( Stack *stack, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stack->top == NULL)
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

BTNode* pop(Stack *stack)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stack->top;
    if(top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if(*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
