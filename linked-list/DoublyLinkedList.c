#include <stdio.h>
#include <stdlib.h>


struct node{
	int data;
	struct node *next;
	struct node *prev;
};

void *xcalloc(int nr_elements, int size_per_element){
	void *tmp;
	tmp = calloc(nr_elements, size_per_element);

	if (tmp == NULL)
	{
		fprintf(stderr, "calloc:fatal:out of memory\n");
		exit(1);
	}

	return tmp;
}

struct node * createNode(int data){
	struct node *newn = (struct node *)xcalloc(1, sizeof(struct node));
	newn -> data = data;
	newn -> next = NULL;
	newn -> prev = NULL;

	return newn;
}

void display(struct node *head){
	if(head == NULL){
		return;
	}

	printf ("[begin]->"); 
	while(head != NULL){
		printf("[%d]<->", head -> data);
		head = head -> next;
	}
	printf ("[end]\n");
}

int length(struct node *head){
	int count = 0;

	while(head != NULL)
	{
		head = head -> next;
		count++;
	}
	return count;
}

void insertFirst(struct node **head, struct node **tail, int data){
	struct node *newn = createNode(data);

	if (*head == NULL || *tail == NULL)
	{
		(*head) = newn;
		(*tail) = newn;
	} else
	{
		newn -> next = (*head);
		(*head) -> prev = newn;
		(*head) = newn;
	}
}

void insertLast(struct node **head, struct node **tail, int data){
	struct node *newn = createNode(data);

	if(*head == NULL || *tail == NULL){
		(*head) = newn;
		(*tail) = newn;
	}else{
		newn -> prev = (*tail);
		(*tail) -> next = newn;
		(*tail) = newn;
	}
}

void insertAtPos(struct node **head, struct node **tail, int data, int pos){
	int count = length(*head);

	if (pos < 1 || pos > count + 1)
	{
		printf("Invalid position\n");
		return;
	}else if (pos == 1)
	{
		insertFirst(head, tail, data);
	}else if (pos == count + 1)
	{
		insertLast(head, tail, data);
	}else{
		struct node *newn = createNode(data);
		struct node *temp = *head;

		for (int i = 0; i < pos - 2; ++i)
		{
			temp = temp -> next;	
		}

		newn -> next = temp -> next;
		temp -> next -> prev = newn;
		temp -> next = newn;
		newn -> prev = temp;
	}
}

void deleteFirst(struct node **head, struct node **tail){
	if(*head == NULL || *tail == NULL){
		printf("List is Empty \n");
		return;
	}else if (((*head) -> next == NULL) && ((*tail) -> prev == NULL))
	{
		free(*head);
		(*head) = NULL;
		(*tail) = NULL;
	} else 
	{
		struct node *temp = *head;
		(*head) -> next -> prev = NULL;
		(*head) = (*head) -> next; 
		free(temp);
	}
}

void deleteLast(struct node **head, struct node **tail){
	if(*head == NULL || *tail == NULL){
		printf("List is Empty \n");
		return;
	}else if (((*head) -> next == NULL) && ((*tail) -> prev == NULL))
	{
		free(*head);
		(*head) = NULL;
		(*tail) = NULL;
	}else{
		struct node *temp = *tail;

		(*tail) = (*tail) -> prev;
		(*tail) -> next = NULL;
		free(temp);

	}
}

void deleteAtPos(struct node **head, struct node **tail, int pos){
	int count = length(*head);

	if (pos < 1 || pos > count + 1)
	{
		printf("Invalid position\n");
		return;
	}else if (pos == 1)
	{
		deleteFirst(head, tail);
	}else if (pos == count)
	{
		deleteLast(head, tail);
	}else{
		struct node *temp = *head;
		struct node *temp1 = *head;

		for (int i = 0; i < pos -2; ++i)
		{
			temp = temp -> next;
		}

		temp1 = temp -> next;
		temp -> next = temp -> next -> next;
		temp -> next -> prev = temp;
		free(temp1);
	}
}


int main(int argc, char const *argv[])
{
	struct node *first = NULL;
	struct node *last = NULL;

	insertFirst(&first, &last, 30);
	insertFirst(&first, &last, 20);
	insertFirst(&first, &last, 10);
	display(first);

	insertLast(&first, &last, 40);
	insertLast(&first, &last, 50);
	insertLast(&first, &last, 60);
	display(first);

	deleteFirst(&first, &last);
	deleteFirst(&first, &last);
	display(first);

	deleteLast(&first, &last);
	deleteLast(&first, &last);
	display(first);

	insertAtPos(&first, &last, 70, 1);
	insertAtPos(&first, &last, 80, 4);
	insertAtPos(&first, &last, 90, 3);
	display(first);

	deleteAtPos(&first, &last, 1);
	deleteAtPos(&first, &last, 4);
	deleteAtPos(&first, &last, 2);
	display(first);

	return 0;
}
