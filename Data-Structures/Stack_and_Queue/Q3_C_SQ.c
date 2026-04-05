//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
   CE1007/CZ1007 자료구조
Lab Test: Section C - Stack and Queue Questions
   Lab Test: 섹션 C - 스택과 큐 문제
Purpose: Implementing the required functions for Question 3
   목적: Question 3에 필요한 함수를 구현합니다. */


//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////   linked list / 연결 리스트 /////////////////////////////////

typedef struct _listnode{
   int item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
   ListNode *tail;
} LinkedList;

////////////////////////////////// stack / 스택 //////////////////////////////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

////////////////////////// function prototypes / 함수 원형 ////////////////////////////////////

// You should not change the prototypes of these functions (이 함수들의 원형은 변경하면 안 됩니다)
int isStackPairwiseConsecutive(Stack *s);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int c, value;

    Stack s;

    s.ll.head=NULL;
	s.ll.size =0;
	s.ll.tail =NULL;

    c =1;

    printf("1: Insert an integer into the stack: / 1: 스택에 정수 삽입\n");
    printf("2: Check the stack is pairwise consecutive: / 2: 스택이 pairwise consecutive 인지 확인\n");
    printf("0: Quit: / 0: 종료\n");

    while (c != 0)
	{
		printf("Please input your choice(1/2/0): / 메뉴를 선택하세요(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the stack: / 스택에 삽입할 정수를 입력하세요: ");
			scanf("%d", &value);
			push(&s, value);
			printf("The stack is: / 스택 상태: ");
            printList(&(s.ll));
			break;
		case 2:
            if(isStackPairwiseConsecutive(&s))
            {
                printf("The stack is pairwise consecutive. / 스택의 각 쌍은 연속된 값입니다.\n");
            }
            else{
                printf("The stack is not pairwise consecutive. / 스택의 각 쌍이 연속된 값이 아닙니다.\n");
            }
            removeAllItems(&(s.ll));
            break;
		case 0:
			removeAllItems(&(s.ll));
			break;
		default:
			printf("Choice unknown; / 알 수 없는 선택입니다.\n");
			break;
		}
	}

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////

int isStackPairwiseConsecutive(Stack *s)
{
  /* add your code here (여기에 코드를 작성하세요) */
  int a, b;
  int result = 1;
  Stack temp;

  temp.ll.head = NULL;
  temp.ll.tail = NULL;
  temp.ll.size = 0;

  if (s->ll.size % 2 == 1) {
    return 0;
  }

  while (!isEmptyStack(s)) {
    a = pop(s);
    b = pop(s);

    push(&temp, a);
    push(&temp, b);

    if (abs(a - b) != 1) {
      result = 0;
      break;
    }
  }

  while (!isEmptyStack(&temp)) {
    push(s, pop(&temp));
  }

  return result;
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   int item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
}

//////////////////////////////////////////////////////////////////////////////////

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
