#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Searches the tree for the specified movie title */
  /* and returns a pointer to that movie */
Movie *titleSearchAll(Movie *masterTreeNode, Movie *searchMatches, char *searchTitle) {
  if (masterTreeNode == NULL) {
    return searchMatches;
  }

  int searchTitleLen = strlen(searchTitle);

  if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) < 0) {
    return titleSearchAll(masterTreeNode->left, searchMatches, searchTitle);
  }
  else if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) > 0) {
    return titleSearchAll(masterTreeNode->right, searchMatches, searchTitle);
  }
  else {
    Movie *newMatch = malloc(sizeof(Movie));
    newMatch = movieCopy(newMatch, masterTreeNode);
    searchMatches = insert(searchMatches, newMatch);

    searchMatches = titleSearchAll(masterTreeNode->left, searchMatches, searchTitle);
    searchMatches = titleSearchAll(masterTreeNode->right, searchMatches, searchTitle);

    return searchMatches;
  }
  return NULL;
}

UserMovie *titleSearchAllUser(UserMovie *masterTreeNode, UserMovie *searchMatches, char *searchTitle) {
  if (masterTreeNode == NULL) {
    return searchMatches;
  }

  int searchTitleLen = strlen(searchTitle);

  if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) < 0) {
    return titleSearchAllUser(masterTreeNode->left, searchMatches, searchTitle);
  }
  else if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) > 0) {
    return titleSearchAllUser(masterTreeNode->right, searchMatches, searchTitle);
  }
  else {
    UserMovie *newMatch = malloc(sizeof(UserMovie));
    newMatch = movieCopyUser(newMatch, masterTreeNode);
    searchMatches = insertUser(searchMatches, newMatch);

    searchMatches = titleSearchAllUser(masterTreeNode->left, searchMatches, searchTitle);
    searchMatches = titleSearchAllUser(masterTreeNode->right, searchMatches, searchTitle);

    return searchMatches;
  }
  return NULL;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

Movie *titleSearchExact(Movie *masterTreeNode, Movie *searchMatch, char *searchTitle) {
  if (masterTreeNode == NULL) {
    return searchMatch;
  }
  int searchTitleLen = strlen(searchTitle);

  if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) < 0) {
    return titleSearchExact(masterTreeNode->left, searchMatch, searchTitle);
  }
  else if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) > 0) {
    return titleSearchExact(masterTreeNode->right, searchMatch, searchTitle);
  }
  else {
    searchMatch = movieCopy(searchMatch, masterTreeNode);
    return searchMatch;
  }
  return NULL;
}

UserMovie *titleSearchExactUser(UserMovie *masterTreeNode, UserMovie *searchMatch, char *searchTitle) {
  if (masterTreeNode == NULL) {
    return searchMatch;
  }
  int searchTitleLen = strlen(searchTitle);

  if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) < 0) {
    return titleSearchExactUser(masterTreeNode->left, searchMatch, searchTitle);
  }
  else if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) > 0) {
    return titleSearchExactUser(masterTreeNode->right, searchMatch, searchTitle);
  }
  else {
    searchMatch = masterTreeNode;
    return searchMatch;
  }
  return NULL;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Filters the results of a search by genre */
Movie *genreFilter(Movie *root, Movie *resultTree, char genre) {
  if(root != NULL) {
    if (strchr(root->genres, genre) != NULL) {
      Movie *newMatch = malloc(sizeof(Movie));
      newMatch = movieCopy(newMatch, root);
      resultTree = insert(resultTree, newMatch);
    }

    resultTree = genreFilter(root->left, resultTree, genre);
    resultTree =  genreFilter(root->right, resultTree, genre);
  }
  return resultTree;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Filters the results of a search by year */
Movie *yearFilter(Movie *root, Movie *resultTree, int low, int high) {
  if(root != NULL) {
    if ((root->startYear >= low) && (root->startYear <= high)) {
      Movie *newMatch = malloc(sizeof(Movie));
      newMatch = movieCopy(newMatch, root);
      resultTree = insert(resultTree, newMatch);
    }

    resultTree = yearFilter(root->left, resultTree, low, high);
    resultTree =  yearFilter(root->right, resultTree, low, high);
  }
  return resultTree;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Filters the results of a search by runtime */
Movie *rtFilter(Movie *root, Movie *resultTree, int low, int high) {
  if(root != NULL) {
    if ((root->runtime >= low) && (root->runtime <= high)) {
      Movie *newMatch = malloc(sizeof(Movie));
      newMatch = movieCopy(newMatch, root);
      resultTree = insert(resultTree, newMatch);
    }

    resultTree = rtFilter(root->left, resultTree, low, high);
    resultTree =  rtFilter(root->right, resultTree, low, high);
  }
  return resultTree;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/
