#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data; 
	struct node *next;
};

void * xcalloc(int nr_elements, int size_per_element){
	void * tmp = NULL;
	tmp = calloc(nr_elements, size_per_element);
	if (tmp == NULL)
	{
		fprintf(stderr, "error:calloc:out of memory\n");
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
	if (head == NULL)
	{
		printf("Stack is empty\n");
		return;
	}
	else
	{
		printf("[begin]->");
		while(head != NULL)
		{
			printf("[%d]->",head->data);
			head = head -> next;
		}
		printf("[end]\n");
	}
}

void push(struct node **head, int data){
	struct node *newn = createNode(data);
	if ((*head) == NULL)
	{
		(*head) = newn;
	}
	else
	{
		newn -> next = (*head);
		(*head) = newn;	
	}
}

int pop(struct node **head){
	int data = 0;
	if (*head == NULL)
	{
		printf("Stack is empty");
		return data;
	}
	else
	{
		struct node *tmp = *head;
		data = (*head) -> data;
		(*head) = (*head) -> next;
		free(tmp);
		return data;
	}
}

int peek(struct node **head){
	int data = 0;
	if (*head == NULL)
	{
		printf("Stack is empty");
		return data;
	}
	else
	{
		data = (*head) -> data;
		return data;
	}
}

int main(int argc, char const *argv[])
{
	struct node *first = NULL;
	int data;
	int topData;

	push(&first, 10);
	push(&first, 20);
	push(&first, 30);
	push(&first, 40);
	display(first);

	topData = peek(&first);
	topData = peek(&first);
	printf("Stack Top element : %d\n", topData);
	display(first);


	data = pop(&first);
	pop(&first);
	pop(&first);
	display(first);
	return 0;
}