
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
   CE1007/CZ1007 자료구조
Lab Test: Section F - Binary Search Trees Questions
   Lab Test: 섹션 F - 이진 탐색 트리 문제
Purpose: Implementing the required functions for Question 1
   목적: Question 1에 필요한 함수를 구현합니다. */


//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode (BSTNode 정의는 변경하면 안 됩니다)

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // You should not change the definition of QueueNode (QueueNode 정의는 변경하면 안 됩니다)


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // You should not change the definition of queue (queue 정의는 변경하면 안 됩니다)

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions (이 함수들의 원형은 변경하면 안 됩니다)
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() / 메인 함수 /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// Initialize the Binary Search Tree as an empty Binary Search Tree (이진 탐색 트리를 빈 트리로 초기화)
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree; / 1: 이진 탐색 트리에 정수 삽입\n");
	printf("2: Print the level-order traversal of the binary search tree; / 2: 이진 탐색 트리의 레벨 순회 출력\n");
	printf("0: Quit; / 0: 종료\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): / 메뉴를 선택하세요(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: / 이진 탐색 트리에 삽입할 정수를 입력하세요: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: / 이진 탐색 트리의 레벨 순회 결과: ");
			levelOrderTraversal(root); // You need to code this function (이 함수는 직접 구현해야 합니다)
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown; / 알 수 없는 선택입니다.\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void levelOrderTraversal(BSTNode* root)
{
    /* add your code here (여기에 코드를 작성하세요) */
	Queue q;  // queue 선언
	q.head = NULL;    // 값 초기화
	q.tail = NULL;     // 값 초기화
	if (root == NULL){  // 트리 비어있을때 종료
		return; }
	// 루트 노드를 줄 맨 뒤에 배치함
	enqueue(&q.head, &q.tail, root);

    // 줄이 빌 때 까지 반복
    while (!isEmpty(q.head)) {
        // 줄 맨 앞값을 꺼내서 cur에 저장
        BSTNode *cur = dequeue(&q.head, &q.tail);
        // 꺼낸 노드의 숫자를 출력
        printf("%d", cur -> item);
        // 꺼낸 노드의 왼쪽 자식이 있다면 줄 뒤에 배치
        if(cur -> left != NULL){
			enqueue(&q.head, &q.tail, cur -> left);
		}
        // 꺼낸 노드의 오른쪽 자식이 있다면 줄 뒤에 배치
		if(cur -> right != NULL){
			enqueue(&q.head, &q.tail, cur -> right);
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

// enqueue node (노드를 enqueue)
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory (동적으로 메모리 할당)
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL (newPtr 가 NULL 이 아니면)
	if (newPtr != NULL) {
		newPtr->data = node;
		newPtr->nextPtr = NULL;

		// if queue is empty, insert at head (큐가 비어 있으면 head 에 삽입)
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else { // insert at tail (tail 에 삽입)
			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else {
		printf("Node not inserted / 노드가 삽입되지 않았습니다");
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;
	QueueNode *tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	free(tempPtr);

	return node;
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
