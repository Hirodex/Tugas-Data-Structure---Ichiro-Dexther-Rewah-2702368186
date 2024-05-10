#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *next;
};
struct node *head=NULL;
int size=0;
struct node *create(int data)
{
	struct node *newnode=(struct node*)malloc(sizeof(struct node));
	newnode->data=data;
	newnode->next=NULL;
	size++;
	return newnode;
}
struct node *push_head(struct node *root, int data)
{
	if (head==NULL)
	{
		head=create(data);
	}
	else
	{
		struct node *temp=head;
		while (temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=create(data);
	}
	return head;
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
struct node *deletion(struct node **head,int data)
{
	if (data==(*head)->data)
	{
		struct node *temp=*head;
		printf("---- Successfully deleted %d from the list ----\n",data);
		*head=(*head)->next;
		size--;
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
	push_head(head,40);
	push_head(head,50);
	push_head(head,60);
	push_mid(head,100);
	print(head);
	deletion(&head,10);
	print(head);
	search(head,20);
}
