#include<stdio.h>
#include<stdlib.h>

struct node {
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

void display(struct node *head, struct node *tail){
	if(head == NULL || tail == NULL){
		return;
	}

	printf ("[begin]->");

	do{
		printf("[%d]<->", head -> data);
		head = head -> next;
	}while(head != tail -> next);

	printf ("[end]\n");
}

int length(struct node *head, struct node *tail){
	int count = 0;

	if (head == NULL || tail == NULL)
	{
		return 0;
	}

	do
	{
		head = head -> next;
		count++;
	}while(head != tail -> next);

	return count;
}

void insertFirst(struct node **head, struct node **tail, int data){
	struct node *newn = createNode(data);

	if (*head == NULL || *tail == NULL)
	{
		(*head) = newn;
		(*tail) = newn;
	}else{
		newn -> next = (*head);
		(*head) -> prev = newn;
		(*head) = newn;
	}

	(*head) -> prev = (*tail);
	(*tail) -> next = (*head);
}

void insertLast(struct node **head, struct node **tail , int data){
	struct node *newn = createNode(data);

	if (*head == NULL || *tail == NULL)
	{
		(*head) = newn;
		(*tail) = newn;
	}else{
		newn -> prev = (*tail);
		(*tail) -> next = newn;
		(*tail) = newn;
	}

	(*tail) -> next = (*head);
	(*head) -> prev = (*tail);
}

void deleteFirst(struct node **head, struct node **tail){
	if (*head == NULL || *tail == NULL)
	{
		printf("List is empty\n");
		return;
	}else if ((*head) -> next == (*head))
	{
		free(*head);
		(*head) = NULL;
		(*tail) = NULL;
	}else{
		struct node *temp = *head;

		(*head) = (*head) -> next;
		(*head) -> prev = (*tail);
		(*tail) -> next = (*head);

		free(temp);
	}
}

void deleteLast(struct node **head, struct node **tail){
	if (*head == NULL || *tail == NULL)
	{
		printf("List is empty\n");
		return;
	}else if ((*head) -> next == (*head))
	{
		free(*head);
		(*head) = NULL;
		(*tail) = NULL;
	}else{
		struct node *temp = *tail;

		(*tail) = (*tail) -> prev;
		(*tail) -> next = (*head);
		(*head) -> prev = (*tail);	

		free(temp);
	}
}

int main(int argc, char const *argv[])
{
	struct node *first = NULL;
	struct node *last = NULL;

	insertFirst(&first, &last, 30);
	insertFirst(&first, &last, 20);
	insertFirst(&first, &last, 10);
	display(first, last);

	insertLast(&first, &last, 40);
	insertLast(&first, &last, 50);
	insertLast(&first, &last, 60);
	display(first, last);

	deleteFirst(&first, &last);
	deleteFirst(&first, &last);
	display(first, last);


	deleteLast(&first, &last);
	deleteLast(&first, &last);
	display(first, last);

	printf("List length : %d", length(first, last));

	return 0;
}
