#include<stdio.h>
#include<stdlib.h>

struct node{
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
	struct node *newn = (struct node *)xcalloc(1, sizeof(struct node));
	newn -> data = data;
	newn -> next = NULL;
	return newn;
}

void display(struct node *head){
	struct node *temp = head;

	if (head == NULL)
	{
		return;
	}

	while(temp -> next != head){
		printf("%d->", temp -> data);
		temp = temp -> next;
	}
	printf("%d->NULL\n",temp -> data);
}

int length(struct node *head){
	int count = 0;
	struct node *temp = head;

	if(head == NULL)
		return 0;

	do{
		count++;
		temp = temp -> next;
	}while(temp != (head));

	return count;
}

void insertFirst(struct node **head, int data){
	struct node *newn = createNode(data);

	if ((*head) == NULL)
	{
		(*head) = newn;
		(*head) -> next = (*head);
	}else{
		struct node *temp = *head;

		while(temp -> next != (*head)){
			temp = temp -> next;
		}

		newn -> next = (*head);
		temp -> next = newn;
		(*head) = newn;
	}
}

void insertLast(struct node **head, int data){
	struct node *newn = createNode(data);

	if (*head == NULL)
	{
		insertFirst(head, data);
	}else{
		struct node *temp = *head;

		while(temp -> next != (*head)){
			temp = temp -> next;
		}
		newn -> next = (*head);
		temp -> next = newn;
	}
}

void insertAtPos(struct node **head, int data, int pos){
	int count = length(*head);

	if (pos < 0 || pos > count+1)
	{
		return;
	}else if (pos == 1)
	{
		insertFirst(head, data);
	}else if (pos == count+1)
	{
		insertLast(head, data);
	}else{
		struct node *temp = *head;
		struct node *newn = createNode(data);

		for (int i = 0; i < count-2; ++i)
		{
			temp = temp -> next;	
		}

		newn -> next = temp -> next;
		temp -> next = newn;
	}
}

void deleteFirst(struct node **head){
	if (*head == NULL)
	{
		return;
	}else if((*head) -> next == (*head)){
		free(*head);
		(*head) = NULL;
	}else{
		struct node *temp = *head;
		struct node *temp1 = *head;

		while(temp -> next != (*head))
			temp = temp -> next;

		(*head) = (*head) -> next;
		temp -> next = (*head);
		free(temp1);
	}
}

void deleteLast(struct node **head){
	if (*head == NULL)
	{
		return;
	}else if((*head) -> next == (*head)){
		free(*head);
		(*head) = NULL;
	}else{
		struct node *temp = *head;
		struct node *temp1 = *head;

		while(temp -> next -> next != (*head))
			temp = temp -> next;

		temp1 = temp -> next;
		temp -> next = (*head);
		free(temp1);
	}
}

void deleteAtPos(struct node **head, int pos){
	int count = length(*head);

	if (pos < 1 || pos > count +1)
	{
		printf("Invalid position");
		return;
	}else if (pos ==1)
	{
		deleteFirst(head);
	}else if (pos == count + 1)
	{
		deleteLast(head);
	}else{
		struct node *temp = *head;
		struct node *temp1 = *head;

		for (int i = 0; i < pos - 2; ++i)
		{
			temp = temp -> next;	
		}

		temp1 = temp -> next;
		temp -> next = temp -> next -> next;
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
	display(first);

	deleteFirst(&first);
	deleteFirst(&first);
	display(first);


	deleteLast(&first);
	deleteLast(&first);
	display(first);

	insertAtPos(&first, 70, 1);
	insertAtPos(&first, 80, 3);
	insertAtPos(&first, 90, 5);
	display(first);

	deleteAtPos(&first, 3);
	display(first);

	return 0;
}