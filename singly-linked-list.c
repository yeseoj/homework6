/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
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

	printf("[----- 2021041018  �忹�� -----]\n");

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
		default: /* �߸��� Ŀ�ǵ� �Է� �� ��� �޽��� ��� */
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;

	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	/* h == NULL�� ��� �ȳ� �޽��� ��� */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	}
	/* ��常ŭ�� �޸𸮸� �Ҵ��ϰ� key���� ���� �� headNode�� ���� */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = h->first;
	h->first = node;
	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;

	/* h == NULL�� ��� �ȳ� �޽��� ��� */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first�� ����Ű�� �� ���� ��� ù ��°�� ���� */
	else if (!h->first) {
		printf("��尡 �� ����Ʈ�� ù ��°�� ���Ե˴ϴ�.\n");
		node->link = h->first;
		h->first = node;
		return 0;
	}

	listNode *p = h->first;
	listNode *prev = h->first;

	if (p->key > key) {
		/* ù ��° ��� ���ʿ� ������ ��� */
		node->link = p;
		h->first = node;
	} /* �߰��� ������ ��� */
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

		/* ������ ���Ƶ� key���� ū ���� ���� ��� �������� ���� */
		printf("����Ʈ�� �������� ���Ե˴ϴ�.\n");
		node->link = p;		// �̶��� p == NULL
		prev->link = node;
	}

	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	/* h == NULL�� ��� �ȳ� �޽��� ��� */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first�� ����Ű�� �� ���� ��� ù ��°�� ���� */
	else if (!h->first) {
		printf("��尡 �� ����Ʈ�� ù ��°�� ���Ե˴ϴ�.\n");
		insertFirst(h, key);
		return 0;
	}

	listNode* findLast = h->first;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	/* ������ ������ �̵� */
	while(findLast->link)
		findLast = findLast->link;

	/* ������ ����� ���� ���� �߰� */
	node->link = findLast->link;
	findLast->link = node;

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	/* h == NULL�� ��� �ȳ� �޽��� ��� */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first�� ����Ű�� �� ���� ��� �ȳ� �޽��� ��� */
	else if (!h->first) {
		printf("��尡 ������ϴ�.\n");
		return 1;
	}
	/* ù ��° ����� link�� headNode�� ���� */
	listNode* firstNode = h->first;
	h->first = firstNode->link;
	/* ù ��° ��� �Ҵ� ���� */
	free(firstNode);

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	/* h == NULL�� ��� �ȳ� �޽��� ��� */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first�� ����Ű�� �� ���� ��� �ȳ� �޽��� ��� */
	else if (!h->first) {
		printf("��尡 ������ϴ�.\n");
		return 1;
	}

	listNode* p = h->first;
	listNode* trail = h->first;
	
	/* ���� ù ��° ����� Ű == key�� �� */
	if (p->key == key)
		deleteFirst(h);
	else { /* �� ���� ��� */
		while (p) {
			if (p->key == key) {
				/* �ش��ϴ� ����� ���� ��带 ���� ��忡 �����ϰ� ���� */
				trail->link = p->link;
				free(p);
				return 0;
			}
			trail = p;
			p = p->link;
		}

		/* ������ ���Ƶ� �ش��ϴ� ��尡 ���� ��� */
		printf("�ش� key�� ���� ��尡 �����ϴ�.\n");
	}

	return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	/* h == NULL�� ��� �ȳ� �޽��� ��� */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first�� ����Ű�� �� ���� ��� �ȳ� �޽��� ��� */
	else if (!h->first) {
		printf("��尡 ������ϴ�.\n");
		return 1;
	}

	listNode* findLast = h->first;
	listNode* trail = NULL;

	/* ������ ��� = ù ��° ����� �� first == NULL�� ����� ��� ���� */
	if (!findLast->link) {
		h->first = trail;
		free(findLast);
	} /* �� ���� ��� */
	else {
		/* ������ ����� ��ũ�� NULL�� �� ������ �̵� */
		while (findLast->link) {
			trail = findLast;
			findLast = findLast->link;
		}
		/* ���� ����� ��ũ�� NULL�� ����� ������ ��� ���� */
		trail->link = findLast->link;
		free(findLast);
	}

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	/* h == NULL�� ��� �ȳ� �޽��� ��� */
	if (!h) {
		printf("Please initialize list first.\n");
		return 1;
	} /* first�� ����Ű�� �� ���� ��� �ȳ� �޽��� ��� */
	else if (!h->first) {
		printf("��尡 ������ϴ�.\n");
		return 1;
	}

	listNode* p = h->first;
	listNode* middle = NULL;
	listNode* trail = NULL;
	 
	/* p == NULL�� �� ������ �۵� */
	while (p) {
		trail = middle;
		middle = p;
		p = p->link;
		middle->link = trail;
	}
	/* headNode�� �������� ����Ʈ�� ù ��° ��� ���� */
	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");
	/* h == NULL�� ��� �ȳ� �޽��� ��� */
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;
	/* p�� NULL�� �� ������ �̵��ϸ� ����� key�� ��� */
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

