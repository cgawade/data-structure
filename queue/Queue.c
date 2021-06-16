#include<stdio.h>
#include<stdlib.h>

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
	printf("[begin]<->");
	while(head != NULL)
	{
		printf("[%d]<->", head -> data);
		head = head -> next;
	}
	printf("[end]\n");
}


int size(struct node *head){
	int count = 0;

	if (head == NULL)
	{
		return count;
	}else{
		while(head != NULL){
			count++;
			head = head -> next;
		}
	}

	return count;
}


void enqueue(struct node **head, struct node **tail, int data){
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
}


void dequeue(struct node **head, struct node **tail){
	if (*head == NULL || *tail == NULL)
	{
		printf("List is empty\n");
		return;
	}else if((*head) -> next == NULL)
	{
		free(*head);
		(*head) = NULL;
		(*tail) = NULL;
	}else
	{
		struct node *temp = *tail;

		(*tail) = (*tail) -> prev;
		(*tail) -> next = NULL;
		free(temp);
	}
}


int main(int argc, char const *argv[])
{
	struct node *first = NULL;
	struct node *last = NULL;

	enqueue(&first, &last, 60);
	enqueue(&first, &last, 50);
	enqueue(&first, &last, 40);
	enqueue(&first, &last, 30);
	enqueue(&first, &last, 20);
	enqueue(&first, &last, 10);
	display(first);

	dequeue(&first, &last);
	dequeue(&first, &last);
	dequeue(&first, &last);
	display(first);


	printf("Queue size : %d", size(first));
	return 0;
}
