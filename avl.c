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

int heightUser(UserMovie *N) {
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

UserMovie *rightRotateUser(UserMovie *y) {
  UserMovie *x = y->left;
  UserMovie *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max(heightUser(y->left), heightUser(y->right))+1;
  x->height = max(heightUser(x->left), heightUser(x->right))+1;

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

UserMovie *leftRotateUser(UserMovie *x) {
  UserMovie *y = x->right;
  UserMovie *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  //  Update heights
  x->height = max(heightUser(x->left), heightUser(x->right))+1;
  y->height = max(heightUser(y->left), heightUser(y->right))+1;

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

int getBalanceUser(UserMovie *N) {
  if (N == NULL)
    return 0;
  return heightUser(N->left) - heightUser(N->right);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// Recursive function to insert a lowerTitle in the subtree rooted
// with node and returns the new root of the subtree.
Movie* insert(Movie* currMovie, Movie *newMovie) {
  /* 1.  Perform the normal BST insertion */
  if (currMovie == NULL)
      return newMovie;

  if (strcmp(newMovie->lowerTitle, currMovie->lowerTitle) < 0) {
    currMovie->left  = insert(currMovie->left, newMovie);
  }
  else if (strcmp(newMovie->lowerTitle, currMovie->lowerTitle) > 0) {
    currMovie->right = insert(currMovie->right, newMovie);
  }
  else {
    return currMovie;
  }

  /* 2. Update height of this ancestor currMovie */
  currMovie->height = 1 + max(height(currMovie->left), height(currMovie->right));

  /* 3. Get the balance factor of this ancestor
        currMovie to check whether this currMovie became
        unbalanced */
  int balance = getBalance(currMovie);

  // If this currMovie becomes unbalanced, then
  // there are 4 cases

  // Left Left Case
  if (balance > 1 && strcmp(newMovie->lowerTitle, currMovie->left->lowerTitle) < 0) {
    return rightRotate(currMovie);
  }

  // Right Right Case
  if (balance < -1 && strcmp(newMovie->lowerTitle, currMovie->right->lowerTitle) > 0) {
    return leftRotate(currMovie);
  }

  // Left Right Case
  if (balance > 1 && strcmp(newMovie->lowerTitle, currMovie->left->lowerTitle) > 0) {
    currMovie->left =  leftRotate(currMovie->left);
    return rightRotate(currMovie);
  }

  // Right Left Case
  if (balance < -1 && strcmp(newMovie->lowerTitle, currMovie->right->lowerTitle) < 0) {
    currMovie->right = rightRotate(currMovie->right);
    return leftRotate(currMovie);
  }

  /* return the (unchanged) currMovie pointer */
  return currMovie;
}

UserMovie* insertUser(UserMovie* currMovie, UserMovie *newMovie) {
  /* 1.  Perform the normal BST insertion */
  if (currMovie == NULL)
      return newMovie;

  if (strcmp(newMovie->lowerTitle, currMovie->lowerTitle) < 0) {
    currMovie->left  = insertUser(currMovie->left, newMovie);
  }
  else if (strcmp(newMovie->lowerTitle, currMovie->lowerTitle) > 0) {
    currMovie->right = insertUser(currMovie->right, newMovie);
  }
  else {
    return currMovie;
  }

  /* 2. Update height of this ancestor currMovie */
  currMovie->height = 1 + max(heightUser(currMovie->left), heightUser(currMovie->right));

  /* 3. Get the balance factor of this ancestor
        currMovie to check whether this currMovie became
        unbalanced */
  int balance = getBalanceUser(currMovie);

  // If this currMovie becomes unbalanced, then
  // there are 4 cases

  // Left Left Case
  if (balance > 1 && strcmp(newMovie->lowerTitle, currMovie->left->lowerTitle) < 0) {
    return rightRotateUser(currMovie);
  }

  // Right Right Case
  if (balance < -1 && strcmp(newMovie->lowerTitle, currMovie->right->lowerTitle) > 0) {
    return leftRotateUser(currMovie);
  }

  // Left Right Case
  if (balance > 1 && strcmp(newMovie->lowerTitle, currMovie->left->lowerTitle) > 0) {
    currMovie->left =  leftRotateUser(currMovie->left);
    return rightRotateUser(currMovie);
  }

  // Right Left Case
  if (balance < -1 && strcmp(newMovie->lowerTitle, currMovie->right->lowerTitle) < 0) {
    currMovie->right = rightRotateUser(currMovie->right);
    return leftRotateUser(currMovie);
  }

  /* return the (unchanged) currMovie pointer */
  return currMovie;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

UserMovie * minValueNode(UserMovie* node) {
  UserMovie* current = node;

  /* loop down to find the leftmost leaf */
  while (current->left != NULL) {
    current = current->left;
  }

    return current;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

UserMovie* deleteNode(UserMovie* root, char *lowerTitle) {
  // STEP 1: PERFORM STANDARD BST DELETE

  if (root == NULL) {
    return root;
  }

  // If the lowerTitle to be deleted is smaller than the
  // root's lowerTitle, then it lies in left subtree
  if (strcmp(lowerTitle, root->lowerTitle) < 0) {
    root->left = deleteNode(root->left, lowerTitle);
  }

  // If the lowerTitle to be deleted is greater than the
  // root's lowerTitle, then it lies in right subtree
  else if(strcmp(lowerTitle, root->lowerTitle) > 0) {
    root->right = deleteNode(root->right, lowerTitle);
  }

  // if lowerTitle is same as root's lowerTitle, then This is
  // the node to be deleted
  else {
    // node with only one child or no child
    if((root->left == NULL) || (root->right == NULL)){
      UserMovie *temp = root->left ? root->left : root->right;

      // No child case
      if (temp == NULL) {
        temp = root;
        root = NULL;
      }
      else { // One child case
        *root = *temp; // Copy the contents of
      }                // the non-empty child
      free(temp);
    }
    else {
      // node with two children: Get the inorder
      // successor (smallest in the right subtree)
      UserMovie* temp = minValueNode(root->right);

      // Copy the inorder successor's data to this node
      root->lowerTitle = temp->lowerTitle;

      // Delete the inorder successor
      root->right = deleteNode(root->right, temp->lowerTitle);
    }
  }

  // If the tree had only one node then return
  if (root == NULL) {
    return root;
  }

  // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
  root->height = 1 + max(heightUser(root->left), heightUser(root->right));

  // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
  // check whether this node became unbalanced)
  int balance = getBalanceUser(root);

  // If this node becomes unbalanced, then there are 4 cases

  // Left Left Case
  if (balance > 1 && getBalanceUser(root->left) >= 0) {
    return rightRotateUser(root);
  }

  // Left Right Case
  if (balance > 1 && getBalanceUser(root->left) < 0) {
    root->left =  leftRotateUser(root->left);
    return rightRotateUser(root);
  }

  // Right Right Case
  if (balance < -1 && getBalanceUser(root->right) <= 0) {
    return leftRotateUser(root);
  }

  // Right Left Case
  if (balance < -1 && getBalanceUser(root->right) > 0) {
    root->right = rightRotateUser(root->right);
    return leftRotateUser(root);
  }

  return root;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

// A utility function to print preorder traversal
// of the tree.
void preOrder(Movie *root) {
  if(root != NULL) {
    printf("%s(%d) - %s\n", root->primaryTitle, root->startYear, root->genres);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void preOrderUser(UserMovie *root) {
  if(root != NULL) {
    printf("%s(%d)\n", root->title, root->startYear);
    if (root->ownershipType == 'p') {
      printf("     Owned phyiscally\n");
    }
    else {
      printf("     Owned digitally\n");
    }
    printf("     Aquired: %.2d/%.2d/%.4d\n", root->mAquired, root->dAquired, root->yAquired);
    preOrderUser(root->left);
    preOrderUser(root->right);
  }
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/
