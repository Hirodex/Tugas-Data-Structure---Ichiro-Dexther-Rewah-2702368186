#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *left;
	struct node *right;
	int height;
};
int max(int a, int b)
{
	return (a>b)?a:b;
}
int getheight(struct node *check)
{
	if (check==NULL)
		return 0;
	return check->height;
}

int balancefactor (struct node *root)
{
	if (root==NULL)
		return 0;
	return getheight(root->left)-getheight(root->right);
}
struct node *rotateleft(struct node *root)
{
	struct node *temp=root->right;
	struct node *temp2=temp->left;
	temp->left=root;
	root->right=temp2;
	
	root->height=max(getheight(root->right),getheight(root->left))+1;
	temp->height=max(getheight(temp->right),getheight(temp->left))+1;
	return temp;
}
struct node *rotateright(struct node *root)
{
	struct node *temp=root->left;// SPAMMMMMMMMMMMMMMMMMM TUGASSSSSSSS
	struct node *temp2=temp ->right;
	temp->right=root;
	root->left=temp2;	
	root->height=max(getheight(root->right),getheight(root->left))+1;
	temp->height=max(getheight(temp->right),getheight(temp->left))+1;
	return temp;	
}
struct node *create(int data)
{
	struct node *newnode=(struct node*)malloc(sizeof(struct node));
	newnode->left=NULL;
	newnode->data=data;
	newnode->right=NULL;
	newnode->height=1;
	return newnode;
}
struct node *insert(struct node *root,int data)
{
	if (root==NULL)
		return create(data);
	if (data<root->data)
		root->left=insert(root->left,data);
	else if (data>root->data)
		root->right=insert(root->right,data);

	root->height=max(getheight(root->left),getheight(root->right))+1;
	int bf=balancefactor(root); 
	if (bf<-1 && data>root->right->data)
		return rotateleft(root);
	else if (bf>1 && data<root->left->data)
		return rotateright(root);
	else if (bf<-1 && data<root->right->data)
	{
		root->right=rotateright(root->right);
		return rotateleft(root);
	}
	else if (bf>1 && data > root->left->data)
	{
		root->left=rotateleft(root->left);
		return rotateright(root);
	}
	return root;
}
struct node *deletion (struct node *root, int data)
{
	if (root==NULL)
	return NULL;
	else if (data<root->data)
	root->left=deletion(root->left,data);
	else if (data>root->data)
	root->right=deletion(root->right,data);
	else
	{
		if (root->right==NULL && root->left==NULL)
		{
			printf("---- Deleted %d from the list ----\n",data);
			free(root);
			root=NULL;
		}
		else if (root->right!=NULL && root->left==NULL)
		{
			printf("---- Deleted %d from the list ----\n",data);
			struct node *temp = root->right;
			*root=*temp;
			free(temp);
		}
		else if (root->right==NULL && root->left!=NULL)
		{
			printf("---- Deleted %d from the list ----\n",data);
			struct node *temp = root->left;
			*root=*temp;
			free(temp);
		}
		else
		{
			struct node *temp=root->left;
			while (temp->right!=NULL)
			{
				temp=temp->right;
			}
			root->data=temp->data;
			root->left=deletion(root->left,temp->data);
			
		}
	
	}
	if (root==NULL)
	return root;
	root->height=max(getheight(root->left),getheight(root->right))+1;
	int bf=balancefactor(root);	
	if (bf<-1 && data>root->right->data)
		return rotateright(root);
	else if (bf>1 && data<root->left->data)
		return rotateleft(root);
	else if (bf<-1 && data<root->right->data)
	{
		root->right=rotateleft(root->right);
		return rotateright(root);
	}
	else if (bf>1 && data > root->left->data)
	{
		root->left=rotateright(root->left);
		return rotateleft(root);
	}
	return root;
}
struct node *search (struct node *root, int data)
{
	if (root==NULL)
	{
		return NULL;
	}
	else if (data<root->data)
	{
		root->left=search(root->left,data);
	}
	else if (data>root->data)
	{
		root->right=search(root->right,data);
	}
	else
	{
		return root;
	}
}
void preorder(struct node *root)
{
	if (root!=NULL)
	{
		printf(" %d      %d\n",root->data,root->height);	
		preorder(root->left);
		preorder(root->right);
	}
}
int main()
{
	struct node *root=NULL;
	root=insert(root,30);
	root=insert(root,22);
	root=insert(root,18);
	root=insert(root,15);
	root=insert(root,12);
	printf("Data : Height \n");
	preorder(root);
	deletion(root,12);
	printf("Data : Height \n");
	preorder(root);
	struct node* find;
	find=search(root,12);
	if (find==NULL)
	{
		printf("---- !Data not found! ----\n");
	}
	else
	{
		printf("---- Data found ----\n");
	}
	return 0;
}
