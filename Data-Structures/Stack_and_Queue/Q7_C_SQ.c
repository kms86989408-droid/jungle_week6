//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
   CE1007/CZ1007 자료구조
Lab Test: Section C - Stack and Queue Questions
   Lab Test: 섹션 C - 스택과 큐 문제
Purpose: Implementing the required functions for Question 7
   목적: Question 7에 필요한 함수를 구현합니다. */


//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000

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


typedef struct stack
{
	LinkedList ll;
} Stack; // You should not change the definition of stack (stack 정의는 변경하면 안 됩니다)

///////////////////////// function prototypes / 함수 원형 ////////////////////////////////////

// You should not change the prototypes of these functions (이 함수들의 원형은 변경하면 안 됩니다)
int balanced(char *expression);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() / 메인 함수 //////////////////////////////////////////////

int main()
{
	char ch, str[256];
	int c, i;
	c = 1;

	LinkedList ll;
	Stack s;

	// Initialize the linked list as an empty linked list (연결 리스트를 빈 연결 리스트로 초기화)
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack (스택을 빈 스택으로 초기화)
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Enter a string: / 1: 문자열 입력\n");
	printf("2: Check whether expressions comprised of the characters ()[]{} is balanced: / 2: ()[]{} 로 이루어진 식이 균형 잡혔는지 확인\n");
	printf("0: Quit: / 0: 종료\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): / 메뉴를 선택하세요(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Enter expressions without spaces to check whether it is balanced or not: / 공백 없이 식을 입력하세요: ");
			scanf("%s", str);
			break;
        case 2:
            if(balanced(str))
                printf("not balanced! / 균형 잡히지 않았습니다!\n");
            else
                printf("balanced! / 균형 잡혔습니다!\n");
			break;
		case 0:
			break;
		default:
			printf("Choice unknown; / 알 수 없는 선택입니다.\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////
int balanced(char *expression)
{
/* add your code here (여기에 코드를 작성하세요) */
Stack s;
s.ll.head = NULL;
s.ll.size = 0;

int i = 0;
while (expression[i] != '\0'){
	char ch = expression[i];

	if (ch == '(' || ch == '[' || ch =='{'){
		push(&s, ch);
	} 
	else{
		if (isEmptyStack(&s)) return 1;
		if ((ch == ')' && peek(&s) != '(') ||
			(ch ==']' && peek(&s) != '[')||
			(ch == '}' && peek(&s) != '{'))
			return 1;
		else
		pop(&s);
	}
	i++;	
}
if (isEmptyStack(&s))
return 0;
else
return 1;
}

////////////////////////////////////////////////////////////

void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
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

/////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int peek(Stack *s){
    if(isEmptyStack(s))
        return MIN_INT;
    else
        return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
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
