/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- 2021041018  장예서 -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default: /* 잘못된 커맨드 입력 시 경고 메시지 출력 */
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;

	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	/* h == NULL의 경우 안내 메시지 출력 */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	}
	/* 노드만큼의 메모리를 할당하고 key값을 넣은 후 headNode와 연결 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = h->first;
	h->first = node;
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;

	/* h == NULL의 경우 안내 메시지 출력 */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first가 가리키는 게 없는 경우 첫 번째로 삽입 */
	else if (!h->first) {
		printf("노드가 빈 리스트에 첫 번째로 삽입됩니다.\n");
		node->link = h->first;
		h->first = node;
		return 0;
	}

	listNode *p = h->first;
	listNode *prev = h->first;

	if (p->key > key) {
		/* 첫 번째 노드 앞쪽에 삽입할 경우 */
		node->link = p;
		h->first = node;
	} /* 중간에 삽입할 경우 */
	else {
		while (p) {
			if (p->key > node->key) {
				node->link = p;
				prev->link = node;
				return 0;
			}
			prev = p;
			p = p->link;
		}

		/* 끝까지 돌아도 key보다 큰 값이 없는 경우 마지막에 삽입 */
		printf("리스트의 마지막에 삽입됩니다.\n");
		node->link = p;		// 이때의 p == NULL
		prev->link = node;
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	/* h == NULL의 경우 안내 메시지 출력 */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first가 가리키는 게 없는 경우 첫 번째로 삽입 */
	else if (!h->first) {
		printf("노드가 빈 리스트에 첫 번째로 삽입됩니다.\n");
		insertFirst(h, key);
		return 0;
	}

	listNode* findLast = h->first;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	/* 마지막 노드까지 이동 */
	while(findLast->link)
		findLast = findLast->link;

	/* 마지막 노드의 다음 노드로 추가 */
	node->link = findLast->link;
	findLast->link = node;

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	/* h == NULL의 경우 안내 메시지 출력 */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first가 가리키는 게 없는 경우 안내 메시지 출력 */
	else if (!h->first) {
		printf("노드가 비었습니다.\n");
		return 1;
	}
	/* 첫 번째 노드의 link를 headNode와 연결 */
	listNode* firstNode = h->first;
	h->first = firstNode->link;
	/* 첫 번째 노드 할당 해제 */
	free(firstNode);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	/* h == NULL의 경우 안내 메시지 출력 */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first가 가리키는 게 없는 경우 안내 메시지 출력 */
	else if (!h->first) {
		printf("노드가 비었습니다.\n");
		return 1;
	}

	listNode* p = h->first;
	listNode* trail = h->first;
	
	/* 가장 첫 번째 노드의 키 == key일 때 */
	if (p->key == key)
		deleteFirst(h);
	else { /* 그 외의 경우 */
		while (p) {
			if (p->key == key) {
				/* 해당하는 노드의 다음 노드를 이전 노드에 연결하고 삭제 */
				trail->link = p->link;
				free(p);
				return 0;
			}
			trail = p;
			p = p->link;
		}

		/* 끝까지 돌아도 해당하는 노드가 없을 경우 */
		printf("해당 key를 가진 노드가 없습니다.\n");
	}

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	/* h == NULL의 경우 안내 메시지 출력 */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first가 가리키는 게 없는 경우 안내 메시지 출력 */
	else if (!h->first) {
		printf("노드가 비었습니다.\n");
		return 1;
	}

	listNode* findLast = h->first;
	listNode* trail = NULL;

	/* 마지막 노드 = 첫 번째 노드일 때 first == NULL로 만들고 노드 삭제 */
	if (!findLast->link) {
		h->first = trail;
		free(findLast);
	} /* 그 외의 경우 */
	else {
		/* 마지막 노드의 링크가 NULL이 될 때까지 이동 */
		while (findLast->link) {
			trail = findLast;
			findLast = findLast->link;
		}
		/* 이전 노드의 링크를 NULL로 만들고 마지막 노드 삭제 */
		trail->link = findLast->link;
		free(findLast);
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	/* h == NULL인 경우 안내 메시지 출력 */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first가 가리키는 게 없는 경우 안내 메시지 출력 */
	else if (!h->first) {
		printf("노드가 비었습니다.\n");
		return 1;
	}

	listNode* p = h->first;
	listNode* middle = NULL;
	listNode* trail = NULL;
	 
	/* p == NULL이 될 때까지 작동 */
	while (p) {
		trail = middle;
		middle = p;
		p = p->link;
		middle->link = trail;
	}
	/* headNode와 뒤집어진 리스트의 첫 번째 노드 연결 */
	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");
	/* h == NULL인 경우 안내 메시지 출력 */
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;
	/* p가 NULL이 될 때까지 이동하며 노드의 key값 출력 */
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

