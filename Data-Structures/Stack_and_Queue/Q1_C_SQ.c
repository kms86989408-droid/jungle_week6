//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
   CE1007/CZ1007 자료구조
Lab Test: Section C - Stack and Queue Questions
   Lab Test: 섹션 C - 스택과 큐 문제
Purpose: Implementing the required functions for Question 1
   목적: Question 1에 필요한 함수를 구현합니다. */


//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode (ListNode 정의는 변경하면 안 됩니다)

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList (LinkedList 정의는 변경하면 안 됩니다)


typedef struct _queue
{
	LinkedList ll;
} Queue;  // You should not change the definition of Queue (Queue 정의는 변경하면 안 됩니다)

///////////////////////// function prototypes / 함수 원형 ////////////////////////////////////

// You should not change the prototypes of these functions (이 함수들의 원형은 변경하면 안 됩니다)
void createQueueFromLinkedList(LinkedList *ll, Queue *q);
void removeOddValues(Queue *q);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() / 메인 함수 //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Queue q;

	c = 1;

	// Initialize the linked list as an empty linked list (연결 리스트를 빈 연결 리스트로 초기화)
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue (Queue 를 빈 큐로 초기화)
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: Insert an integer into the linked list: / 1: 연결 리스트에 정수 삽입\n");
	printf("2: Create the queue from the linked list: / 2: 연결 리스트로부터 큐 생성\n");
	printf("3: Remove odd numbers from the queue: / 3: 큐에서 홀수 제거\n");
	printf("0: Quit: / 0: 종료\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): / 메뉴를 선택하세요(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the List: / 리스트에 삽입할 정수를 입력하세요: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: / 결과 연결 리스트: ");
			printList(&ll);
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // You need to code this function (이 함수는 직접 구현해야 합니다)
			printf("The resulting queue is: / 결과 큐: ");
			printList(&(q.ll));
			break;
		case 3:
			removeOddValues(&q); // You need to code this function (이 함수는 직접 구현해야 합니다)
			printf("The resulting queue after removing odd integers is: / 홀수를 제거한 결과 큐: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown; / 알 수 없는 선택입니다.\n");
			break;
		}

	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////

void createQueueFromLinkedList(LinkedList *ll, Queue *q)
{
	/* add your code here (여기에 코드를 작성하세요) */
	removeAllItemsFromQueue(q);

	ListNode *temp = ll -> head;
	while (temp != NULL){
		enqueue(q, temp -> item); // 값을 큐에 넣기
		temp = temp -> next; // 다음 노드로 이동
	}
}

void removeOddValues(Queue *q)
{
	/* add your code here (여기에 코드를 작성하세요) */
	int count = q ->ll.size;
	int i, item;

	for (i = 0; i < count; i++){
		item = dequeue(q);
		if (item % 2 == 0){
			enqueue(q, item);
		}
		
	}

}

//////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item) {
	insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q) {
	int item;

	if (!isEmptyQueue(q)) {
		item = ((q->ll).head)->item;
		removeNode(&(q->ll), 0);
		return item;
	}
	return -1;
}

int isEmptyQueue(Queue *q) {
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

void removeAllItemsFromQueue(Queue *q)
{
	int count, i;
	if (q == NULL)
		return;
	count = q->ll.size;

	for (i = 0; i < count; i++)
		dequeue(q);
}


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty / 비어 있음");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer (리스트가 비어 있거나 첫 노드를 삽입하는 경우 head 포인터를 갱신해야 함)
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position (목표 위치의 이전 노드와 해당 위치 노드를 찾음)
	// Create a new node and reconnect the links (새 노드를 만들고 링크를 다시 연결함)
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1 (제거할 수 있는 최대 인덱스는 size-1)
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer (첫 노드를 제거하는 경우 head 포인터를 갱신해야 함)
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position (목표 위치의 이전 노드와 다음 노드를 찾음)
	// Free the target node and reconnect the links (대상 노드를 해제하고 링크를 다시 연결함)
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
