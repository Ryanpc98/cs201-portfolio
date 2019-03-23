// C program to insert a node in AVL tree
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Code for AVL tree from:
  //https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to get the height of the tree
int height(Movie *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
Movie* newNode(char *title)
{
    Movie* node = (Movie*) malloc(sizeof(Movie));
    node->primaryTitle = title;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
Movie *rightRotate(Movie *y)
{
    Movie *x = y->left;
    Movie *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
Movie *leftRotate(Movie *x)
{
    Movie *y = x->right;
    Movie *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// Get Balance factor of node N
int getBalance(Movie *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
Movie* insert(Movie* node, char *title) {
  int titLen =  strlen(title);
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(title));

    if (strncmp(title, node->primaryTitle, titLen) < 0)
        node->left  = insert(node->left, title);
    else if (strncmp(title, node->primaryTitle, titLen) > 0)
        node->right = insert(node->right, title);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && strncmp(title, node->left->primaryTitle, titLen) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strncmp(title, node->right->primaryTitle, titLen) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strncmp(title, node->right->primaryTitle, titLen) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strncmp(title, node->right->primaryTitle, titLen) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(Movie *root)
{
    if(root != NULL)
    {
        printf("%d ", root->primaryTitle);
        preOrder(root->left);
        preOrder(root->right);
    }
}
