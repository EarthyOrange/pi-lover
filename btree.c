#include <stdio.h>
#include <stdlib.h>

struct node
{
  int data;
  struct node *left;
  struct node *right;
};

typedef struct node node;

node* createNode(int);
node* insert(node *, int);
void inorder(node *);
int maxDepth(node *);
int minValue(node *);
void printPostorder(node *);
int hasPathSum(node *, int);
void printPaths(node *, int *, int);
void mirror(node *);
void doubleTree(node *);
int sameTree(node *, node *);
int isBST(node *);
node* treeList(node *);
node* appendL(node*, node*);
node* appendR(node*, node*);

int main()
{
  node *root = NULL, *rootb = NULL, *rooth = NULL, *temp;
  int sum = 25, *a, l = 0;
  a = (int *)malloc(sizeof(int));

  root = insert(root, 10);
  root = insert(root, 7);
  root = insert(root, 6);
  root = insert(root, 8);
  root = insert(root, 13);
  root = insert(root, 15);
  root = insert(root, 11);

  printf("Part2: Size: \t%d\n", size(root, 0));
  printf("Part3: Depth: \t%d\n", maxDepth(root));
  printf("Part4: Min: \t%d\n", minValue(root));
  printf("Part5: Post: \t");printPostorder(root);printf("\n");
  printf("Part6: Path Sum: %d %s\n", sum, hasPathSum(root, sum)?"True":"False");
  printf("Part7: Leaf Paths");printPaths(root, a, l);
  printf("\n");
  inorder(root);printf("\n");
  printf("Part8: Mirror: ");mirror(root);inorder(root);printf("\n");

  rootb = insert(rootb, 10);
  rootb = insert(rootb, 7);
  rootb = insert(rootb, 6);
  rootb = insert(rootb, 8);
  rootb = insert(rootb, 13);
  rootb = insert(rootb, 15);
  rootb = insert(rootb, 11);

  printf("Part9: doubleTree: ");doubleTree(rootb);inorder(rootb);printf("\n");
  printf("Part10: sameTree: %s\n", sameTree(root, root)?"True":"False");
  mirror(root);
  printf("Part11: isBST: %s\n", isBST(root)?"True":"False");
  printf("Part12: Tree list: ");
  rooth = treeList(root);
  temp = rooth -> left;
  printf("%d ", rooth -> data);
  while(temp != rooth)
    {
      printf("%d ", temp -> data);
      temp = temp -> left;
    }
  printf("\n");

  return(0);
}

node* createNode(int data)
{
  node *n;
  n = (node *)malloc(sizeof(node));
  n -> data = data;
  n -> right = NULL;
  n -> left = NULL;

  return(n);
}

node* insert(node *n, int data)
{
  if(n == NULL)
    {
      return(createNode(data));
    }

  else
    {
      if(data > n -> data)
        n -> right = insert(n -> right, data);
      else
	n -> left = insert(n -> left, data);

      return(n);
    }
}

int size(node *n, int count)
{
  if(n == NULL)
    return(count);
  else
    {
      count = size(n -> left, count);
      count = size(n -> right, count);
      return(++count);
    }
}

void inorder(node *n)
{
  if(n == NULL)
    return;
  else
    {
      inorder(n -> left);
      printf("%d ", n -> data);
      inorder(n -> right);
    }
}

int maxDepth(node *n)
{
  int l, r;

  if(n == NULL)
    return(0);

  else
    return ((l = maxDepth(n -> left)) >= (r = maxDepth(n -> right))?++l:++r);
}

int minValue(node *n)
{
  int retval;

  if(n == NULL)
    return(0);

  if((retval = minValue(n -> left)) == 0)
    {
      retval = n -> data;
      return retval;
    }
}

void printPostorder(node *n)
{
  if(n == NULL)
    return;
  else
    {
      printPostorder(n -> left);
      printPostorder(n -> right);
      printf("%d ", n -> data);
    }
}

int hasPathSum(node *n, int sum)
{
  if(n == NULL && sum == 0)
    return(1);

  else if(n == NULL && sum != 0)
    return(0);
  
  else
    return(hasPathSum(n -> left, sum - n -> data) || hasPathSum(n -> right, sum - n -> data));
}

void printPaths(node *n, int *a, int l)
{
  if(n -> left == NULL && n -> right == NULL)
    {
      int i;
      a = realloc(a, ++l * sizeof(int));
      *(a + l - 1) = n -> data;

      printf("\n");
      
      for(i = 0;i < l;i++)
	printf("%d ", a[i]);

      return;
    }
  else
    {
      a = realloc(a, ++l * sizeof(int));
      *(a + l - 1) = n -> data;
      printPaths(n -> left, a, l);
      printPaths(n -> right, a, l);
    }
}

void mirror(node *n)
{
  node *t;

  if(n == NULL)
    return;

  else
    {
      t = n -> left;
      n -> left = n -> right;
      n -> right = t;
      mirror(n -> left);
      mirror(n -> right);
    }
}

void doubleTree(node *n)
{
  if(n == NULL)
    return;

  else
    {
      node *t;
      t = n -> left;
      n -> left = (node *)malloc(sizeof(node));
      n -> left -> data = n -> data;
      n -> left -> left  = t;

      doubleTree(t);
      doubleTree(n -> right);
    }
}

int sameTree(node *a, node *b)
{
  if(a == NULL && b == NULL)
    return(1);

  else if(a -> data == b -> data)
    return(1 && (sameTree(a -> left, b -> left) && sameTree(a -> right, b -> right)));

  else
    return(0);
}

int isBST(node *n)
{
  int r;

  if(n == NULL)
    return(1);

  else
    {
      r = isBST(n -> left);
      /*if(r * n -> data == 0 || r > n -> data)
	return(0);
      else 
	return(n -> data);

      r = isBST(n -> right);
      if(r * n -> data == 0 || r <= n -> data)
	return(0);
      else
      return(n -> data);*/
      return (r * n -> data == 0 || r > n -> data)?0:(n -> data);

      r = isBST(n -> right);
      return (r * n -> data == 0 || r <= n -> data)?0:(n -> data);

    }
}

node* appendL(node *l1, node *l2)
{
  if(l2 -> left == l2 && l2 -> right == l2)
    {
      l2 -> right = l1;
      l1 -> right = l2;
      l2 -> left = l1;
      l1 -> left = l2;
    }
  else
    {
      l2 -> left -> right = l1;
      l1 -> left = l2 -> left;
      l1 -> right = l2;
      l2 -> left = l1;
    }
   
  return(l2);
}

node* appendR(node *l1, node *l2)
{
  if(l2 -> right == l2 && l2 -> left == l2)
    {
      l1 -> left -> right = l2;
      l2 -> left = l1 -> left;
      l1 -> left = l2;
      l2 -> right = l1;
    }
  else
    {
      node *t, **te;
      l1 -> left -> right = l2;
      t = (l1 -> left);
      te = &t;
      l1 -> left = l2 -> left;
      l2 -> left = *te;
      l2 -> left -> right = l1;
      
    }
  return(l1);
}

node* treeList(node *n)
{
  node *temp;

  if(n -> right == NULL && n -> left == NULL)
    {
      n -> left = n;
      n -> right = n;
      return(n);
    }

  else if(n -> right == NULL && n -> left != NULL)
    {
      n = appendL(n, treeList(n -> left));
      return(n);
    }

  else if(n -> left == NULL && n -> right != NULL)
    {
      n = appendR(n, treeList(n -> right));
      return(n);
    }
  
  else
    {
      temp = n -> right;
      n = appendL(n, treeList(n -> left));
      n = appendR(n, treeList(temp));
      return(n);
    }
}

