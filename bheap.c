#include <stdio.h>
#include <stdlib.h>

struct node* createNode(int);
struct node* insertNode(struct node **);
struct node* findPlace(struct node **, struct node **);
void inorder(struct node *);
void swap(struct node **, struct node **);
void remov(struct node **, struct node **);
int extractNode(struct node **);
void setDirection(struct node **);
void checkHeap(struct node **);

struct node
{
  int data;
  int direction;
  struct node *left;
  struct node *right;
  struct node *parent;
};

struct node *root, *par;

int main()
{
  int i;
  struct node *n, *t;

  root = NULL;
  n = createNode(20);
  par = insertNode(&n);
  //printf("%d\n", n -> data);
  
  n = createNode(21);
  par = insertNode(&n);
  //t = n -> left; //n contain the root here, this will no be the case later on
  //printf("%d\n", t -> direction);
  n = createNode(22);
  n = insertNode(&n);

  inorder(root);
  printf("\n");
  n = createNode(23);
  par = insertNode(&n);

  inorder(root);
  printf("\n");
  n = createNode(24);
  par = insertNode(&n);
  
  inorder(root);
  printf("\n");

n = createNode(25);
  par = insertNode(&n);
  
  inorder(root);
  printf("\n");

n = createNode(26);
  par = insertNode(&n);
  
  inorder(root);
  printf("\n");  

n = createNode(27);
  par = insertNode(&n);
  
  inorder(root);
  printf("\n");  
  
  printf("ext: %d\n", extractNode(&par));
  inorder(root);
  printf("\n");
printf("ext: %d\n", extractNode(&par));
  inorder(root);
  printf("\n");
printf("ext: %d\n", extractNode(&par));
  inorder(root);
  printf("\n");
  printf("ext: %d\n", extractNode(&par));
  inorder(root);
  printf("\n");
   printf("ext: %d\n", extractNode(&par));
  inorder(root);
  printf("\n");
  printf("ext: %d\n", extractNode(&par));
  inorder(root);
  printf("\n");
printf("ext: %d\n", extractNode(&par));
  inorder(root);
  printf("\n");
 printf("ext: %d\n", extractNode(&par));
  inorder(root);
  printf("\n");
  
  return(0);
}

struct node* createNode(int data)
{
  struct node *node;
  node = (struct node*)malloc(sizeof(struct node));

  node -> data = data;
  node -> direction = -1;
  node -> left = NULL;
  node -> right = NULL;
  node -> parent = NULL;

  return node;
}

struct node* insertNode(struct node **n)
{
  struct node *temp, *hold;
  hold = *n;
  
  if(root == NULL)
    {
      root = *n;
      root -> direction = 0;
      root -> parent = NULL;
      return root;
    }
  else
    {
      temp = findPlace(&root, n);//returns the parent node
      //here the insertion point inverts because the returned node has its direction set in findPlace
      
    }

  return temp;
}

struct node* findPlace(struct node **n, struct node **insert)
{
  struct node *temp, *current;
  current = *n;
    
  if(current -> direction == -1)
    {
      if((*insert) -> data == -9999)
	return current;

      current -> direction = 1;
      current -> left = *insert;//new insertion - Saturday
      (*insert) -> parent = current;//new insertion - Sunday - added to support deletion
      swap(n, insert);

      return current;
    }

  // This case will be true only for the element left to root
  if(current -> direction == 0 && current -> left == NULL)
    { 
      if((*insert) -> data == -9999)
	return current;

      current -> direction = 1;
      current -> left = *insert;//new insertion - Saturday
      (*insert) -> parent = current;//new insertion - Sunday
      swap(n, insert);
      
      return current;
    }
  else if(current -> direction == 1 && current -> right == NULL)
    {
      if((*insert) -> data == -9999)
	return current;
 
      current -> direction = 0;
      current -> right = *insert;//new insertion - Saturday
      (*insert) -> parent = current;//new insertion - Sunday
      swap(n, insert);

      return current;
    }
  else if(current -> direction == 0 && current -> left != NULL)
    {
      swap(&current, insert);

      temp = findPlace(&(current -> left), insert);
      if(current -> left -> direction == 0 && current -> right -> direction == -1)
	current -> direction = 1;
    }
  else if(current -> direction == 1 && current -> right != NULL)
    {
      swap(&current, insert);
      temp = findPlace(&(current -> right), insert);
      if(current -> left -> direction == current -> right -> direction)
	current -> direction = 0;
    }
  else
    {
      printf("Error in code\n");
    }

  return temp;
}

void inorder(struct node *n)
{
  if(n != NULL)
    {
      inorder(n -> left);
      printf("%d %d   ", n -> direction, n -> data);
      inorder(n -> right);
    }
}

void swap(struct node **n, struct node **t)
{
  struct node *current, *new;
  current = *n;
  new = *t;
  int tp;
  
  if(current -> data < new -> data)
    {
      tp = current -> data; 
      current -> data = new -> data;
      new -> data = tp;
    }

  return;
}
      
int extractNode(struct node **p)
{
  int retval;

  if(root == NULL)
    return -1;

  else if(root -> left == NULL && root -> right == NULL)
    {
      retval = root -> data;
      root -> direction = 0;
      free(root);
      root = NULL;
    }

  else
    {
      retval = root -> data;
      remov(&root, p);
      checkHeap(&root);
    }

  return retval;
}

void remov(struct node **n, struct node **p)//removes the last inserted node only, updates the direction of immediate parent and sets new place for parent
{
  struct node *current, *delp;
  delp = *p;

  if(delp -> direction == 0)
    {
      delp -> direction = 1;
      root -> data = delp -> right -> data;
      free(delp -> right);
      delp -> right = NULL;
      
      setDirection(&delp);
    }
  else if(delp -> direction == 1)
    {
      delp -> direction = -1;
      if(delp == root && delp -> right == NULL)
      	delp -> direction = 0;

      root -> data = delp -> left -> data;
      free(delp -> left);
      delp -> left = NULL;

      setDirection(&delp);
      
      delp = delp -> parent;
      if(delp != NULL)
	{
	  if(delp == root && delp -> direction == 0)
	    {
	      par = delp;
	      return;    
	    }
	  
	  if(delp -> direction == 0 && delp -> parent -> left == delp && delp -> parent -> right -> direction == 0)
	    delp = delp -> parent -> right;
 
	  if(delp -> direction == 0 && delp -> parent -> right == delp && delp -> parent -> direction == 1)
	    delp = delp -> parent -> left -> right;
	  
	  if(delp -> direction == 1) 
	    delp = delp -> left;

	  par = delp;
	  printf("%d\n", delp -> data);
	}
      else
	return;
     }
  else
    printf("Error\n");

  return;
}

void setDirection(struct node **n)//supposed to update the direction all along the path; n is the parent of the removed node
{
  struct node *current = *n, *p;
  p = current -> parent;//for root this value will be NULL
  if(p == NULL)
    return;//more to be added

  if(current == p -> right)//if current node is left child of its parent
    {
      p -> direction = 1;
      setDirection(&p);
    }
  else if(current == p -> left)
    {
      p -> direction = 0;
      return;
    }
}

void checkHeap(struct node **p)
{
  struct node *n = *p;

  if(n -> left != NULL && n -> right != NULL)
    {

      if(n -> right -> data < n -> left -> data && n -> data < n -> left -> data)
	{
	  swap(&n, &(n -> left));
	  checkHeap(&(n -> left));
	}
      else if(n -> left -> data < n -> right -> data && n -> data < n -> right -> data)
	{
	  swap(&n, &(n -> right));
	  checkHeap(&(n -> right));
	}
      else if(n -> data > n -> left -> data)
	return;
      else if(n -> data > n -> right -> data)
	return;
    }
  else if(n -> left == NULL && n -> right != NULL && n -> data < n -> right -> data)
    {
      swap(&n, &(n -> right));
      checkHeap(&(n -> right));
    }
  else if(n -> left != NULL && n -> right == NULL && n -> data < n -> left -> data)
    {
      swap(&n, &(n -> left));
      checkHeap(&(n -> left));
    }
  else
    return;
}
