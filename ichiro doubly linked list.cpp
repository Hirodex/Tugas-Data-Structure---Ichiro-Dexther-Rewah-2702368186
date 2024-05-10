#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *next;
	struct node *prev;
};
struct node *head=NULL,*tail=NULL;
int size=0;
struct node *create(int data)
{
	struct node *newnode=(struct node*)malloc(sizeof(struct node));
	newnode->next=NULL;
	newnode->data=data;
	newnode->prev=NULL;
	size++;
	return newnode;
}
struct node *push_head(struct node *root, int data)
{
	if (head==NULL)
	{
		head=tail=create(data);
	}
	else
	{
		struct node *temp=create(data);
		temp->next=head;
		head=temp;
	}
}
struct node *push_mid(struct node *head, int data)
{
	struct node *temp=head;
	int count=(size%2==0)?(size/2)-1:((size+1)/2)-1;
	for (int i=0; i<count; i++)
	{
		temp=temp->next;
	}
	struct node *add=create(data);
	add->next=temp->next;
	temp->next=add;
	return head;
}
struct node *push_tail(struct node *head, int data)
{
	struct node *temp=create(data);
	temp->prev=tail;
	tail->next=temp;
	tail=temp;
	return head;
}
struct node *deletion(struct node **head,int data)
{
	if (data==(*head)->data)
	{
		struct node *temp=*head;
		*head=(*head)->next;
		size--;
		printf("---- Successfully deleted %d from the list ----\n",data);
		free(temp);
		return *head;
	}
	else
	{
		struct node *temp=*head;
		while (temp->next!=NULL && temp->next->data!=data)
		{
			temp=temp->next;
		}
		if (temp->next==NULL)
		{
			printf("---- !Data not found! ----\n");
			return *head;
		}
		struct node *temp2=temp->next;
		temp->next=temp2->next;
		size--;
		printf("---- Successfully deleted %d from the list ----\n",data);
		free(temp2);
		return *head;
	}
	
	return *head;
}
struct node *search(struct node *head, int data)
{
	struct node *temp = head;
	int traverse=1;
	while (temp->next!=NULL && temp->data!=data)
	{
		temp=temp->next;
		traverse++;
	}
	if (temp->data==data)
	{
		printf("---- %d found at node number %d ----\n",temp->data,traverse);
	}
	else
	{
		printf("---- !Data not found! ----\n");
	}
}
void print(struct node *head)
{
	struct node *temp=head;
	printf("Size: %d\n",size);
	printf("List: ");
	while (temp!=NULL)
	{
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("\n");
}
int main()
{
	push_head(head,10);
	push_head(head,20);
	push_head(head,30);
	push_tail(head,200);
	push_tail(head,400);
	push_tail(head,500);
	push_mid(head,1000);
	print(head);
	deletion(&head,1000);
	print(head);
	search(head,400);
}
