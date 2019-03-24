// C program to insert a node in AVL tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

//Code for AVL tree from:
  //https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to get the height of the tree
int height(Movie *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to get maximum of two integers
int max(int a, int b) {
  return (a > b)? a : b;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
Movie *rightRotate(Movie *y) {
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
Movie *leftRotate(Movie *x) {
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
int getBalance(Movie *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
Movie* insert(Movie* currMovie, Movie *newMovie) {
  int titlen = strlen(newMovie->primaryTitle);
  /* 1.  Perform the normal BST insertion */
  if (currMovie == NULL)
      return newMovie;

  if (strncmp(newMovie->primaryTitle, currMovie->primaryTitle, titlen) < 0) {
    currMovie->left  = insert(currMovie->left, newMovie);
  }
  else if (strncmp(newMovie->primaryTitle, currMovie->primaryTitle, titlen) > 0) {
    currMovie->right = insert(currMovie->right, newMovie);
  }
  else // Equal keys are not allowed in BST
    return currMovie;

  /* 2. Update height of this ancestor currMovie */
  currMovie->height = 1 + max(height(currMovie->left), height(currMovie->right));

  /* 3. Get the balance factor of this ancestor
        currMovie to check whether this currMovie became
        unbalanced */
  int balance = getBalance(currMovie);

  // If this currMovie becomes unbalanced, then
  // there are 4 cases

  // Left Left Case
  if (balance > 1 && strncmp(newMovie->primaryTitle, currMovie->left->primaryTitle, titlen) < 0) {
    return rightRotate(currMovie);
  }

  // Right Right Case
  if (balance < -1 && strncmp(newMovie->primaryTitle, currMovie->right->primaryTitle, titlen) > 0) {
    return leftRotate(currMovie);
  }

  // Left Right Case
  if (balance > 1 && strncmp(newMovie->primaryTitle, currMovie->left->primaryTitle, titlen) > 0) {
    currMovie->left =  leftRotate(currMovie->left);
    return rightRotate(currMovie);
  }

  // Right Left Case
  if (balance < -1 && strncmp(newMovie->primaryTitle, currMovie->right->primaryTitle, titlen) < 0) {
    currMovie->right = rightRotate(currMovie->right);
    return leftRotate(currMovie);
  }

  /* return the (unchanged) currMovie pointer */
  return currMovie;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(Movie *root) {
  if(root != NULL) {
    printf("|%s| ", root->primaryTitle);
    preOrder(root->left);
    preOrder(root->right);
  }
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/