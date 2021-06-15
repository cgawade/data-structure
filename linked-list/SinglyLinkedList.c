#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *next;
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
	struct node *newn = (struct node *)malloc(sizeof(struct node));
	newn -> data = data;
	newn -> next = NULL;
	return newn;
}

int length(struct node *head){
	int counter = 0;

	while(head != NULL){
		head = head -> next;
		counter++;
	}

	return counter;
}

void display(struct node *head){
	while(head != NULL){
		printf("%d->", head -> data);
		head = head -> next;
	}
	printf("NULL\n");
}

void insertFirst(struct node **head, int data){
	struct node *newn = createNode(data);

	if ((*head) == NULL)
	{
		(*head) = newn;
	}else{
		newn -> next = (*head);
		(*head) = newn;
	}
}

void insertLast(struct node **head, int data){
	struct node *newn = createNode(data);

	if((*head) == NULL){
		(*head) = newn;
	}else{
		struct node *temp = *head;

		while(temp -> next != NULL){
			temp = temp -> next;
		}
		temp -> next = newn;
	}
}

void insertAtPos(struct node **head, int data, int pos){
	int count = length(*head);

	if ((pos < 1) || (pos > count+1))
	{
		printf("Invalid position\n");
		return;
	}else if (pos == 1)
	{
		insertFirst(head, data);
	}else if (pos == (count+1))
	{
		insertLast(head, data);
	}else
	{
		struct node *newn = createNode(data);
		struct node *temp = *head;
		int i;

		for(i = 0; i < pos-2; i++){
			temp = temp -> next;
		}
		newn -> next = temp -> next;
		temp -> next = newn;
	}
	
		
}

void deleteFirst(struct node **head){

	if ((*head) == NULL){
		printf("Empty List\n");
	}else if ((*head) -> next == NULL){
		free(*head);
		(*head) = NULL;
	}else{
		struct node *temp = *head;
		(*head) = (*head) -> next;
		free(temp);
	}
}

void deleteLast(struct node **head){
	if(*head == NULL){
		printf("Empty list\n");
	}else if((*head) -> next == NULL){
		free(*head);
		(*head) = NULL;
	}else{
		struct node *temp = *head;
		while(temp -> next -> next != NULL){
			temp = temp -> next;
		}
		free(temp -> next);
		temp -> next = NULL;
	}
}

void deleteAtPos(struct node **head, int pos){
	int count = length(*head);

	if ((pos < 1) || (pos > count+1))
	{
		printf("Invalid position\n");
		return;
	}else if (pos == 1)
	{
		deleteFirst(head);
	}else if (pos == count)
	{
		deleteLast(head);
	}else{
		struct node *temp = *head;
		struct node *temp1 = *head;

		for (int i = 0; i < pos-2; ++i)
		{
			temp = temp -> next;
		}

		temp1 = temp -> next;
		temp -> next = temp1 -> next;
		free(temp1);
	}
}

int main(int argc, char const *argv[])
{
	struct node *first = NULL;

	insertFirst(&first, 30);
	insertFirst(&first, 20); 
	insertFirst(&first, 10);
	display(first);

	insertLast(&first, 40);
	insertLast(&first, 50);
	insertLast(&first, 60);
	insertLast(&first, 70);
	display(first);


	deleteFirst(&first);
	deleteFirst(&first);
	deleteFirst(&first);
	display(first);


	deleteLast(&first);
	deleteLast(&first);
	display(first);


	insertAtPos(&first, 80, 1);
	insertAtPos(&first, 90, 4);
	insertAtPos(&first, 100, 3);

	display(first);

	deleteAtPos(&first, 1);
	deleteAtPos(&first, 4);
	deleteAtPos(&first, 2);
	display(first);


	return 0;
}