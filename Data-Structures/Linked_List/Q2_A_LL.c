//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
   CE1007/CZ1007 자료구조
Lab Test: Section A - Linked List Questions
   Lab Test: 섹션 A - 연결 리스트 문제
Purpose: Implementing the required functions for Question 2
   목적: Question 2에 필요한 함수를 구현합니다. */


//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode (ListNode 정의는 변경하면 안 됩니다)

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList (LinkedList 정의는 변경하면 안 됩니다)


//////////////////////// function prototypes / 함수 원형 /////////////////////////////////////

// You should not change the prototype of this function (이 함수의 원형은 변경하면 안 됩니다)
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() / 메인 함수 //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	// Initialize the linked list 1 as an empty linked list (연결 리스트 1을 빈 연결 리스트로 초기화)
	ll1.head = NULL;
	ll1.size = 0;

	// Initialize the linked list 2 as an empty linked list (연결 리스트 2를 빈 연결 리스트로 초기화)
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1: / 1: 연결 리스트 1에 정수 삽입\n");
	printf("2: Insert an integer to the linked list 2: / 2: 연결 리스트 2에 정수 삽입\n");
	printf("3: Create the alternate merged linked list: / 3: 교차 병합된 연결 리스트 생성\n");
	printf("0: Quit: / 0: 종료\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): / 메뉴를 선택하세요(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: / 연결 리스트 1에 추가할 정수를 입력하세요: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: / 연결 리스트 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: / 연결 리스트 2에 추가할 정수를 입력하세요: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: / 연결 리스트 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are: / 주어진 연결 리스트들을 병합한 결과는 다음과 같습니다:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function (이 함수는 직접 구현해야 합니다)
			printf("The resulting linked list 1: / 결과 연결 리스트 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: / 결과 연결 리스트 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown; / 알 수 없는 선택입니다.\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
    ListNode *cur1 = ll1->head;
    ListNode *cur2 = ll2->head;

    while (cur1 != NULL && cur2 != NULL) {
        ListNode *next1 = cur1->next;
        ListNode *next2 = cur2->next;

        cur1->next = cur2;  // ll2 노드를 ll1 노드 뒤에 삽입
        cur2->next = next1; // ll2 노드 다음은 나머지 ll1

        ll1->size++;
        ll2->size--;

        cur1 = next1;
        cur2 = next2;
    }

    ll2->head = cur2; // 남은 ll2 노드들 (ll1이 먼저 끝난 경우)
}

///////////////////////////////////////////////////////////////////////////////////

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


ListNode *findNode(LinkedList *ll, int index){

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
