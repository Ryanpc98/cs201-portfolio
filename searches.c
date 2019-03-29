#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

Movie *movieCopy(Movie *dest, Movie *src) {
  dest->tconst = src->tconst;
  dest->primaryTitle = src->primaryTitle;
  dest->originalTitle = src->originalTitle;
  dest->lowerTitle = src->lowerTitle;
  dest->isAdult = src->isAdult;
  dest->startYear = src->startYear;
  dest->runtime = src->runtime;
  dest->genres = src->genres;
  dest->height = 1;
  dest->left = NULL;
  dest->right = NULL;

  return dest;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Utility function used to print the results of a search */
void searchPrint(int *tconstArray, Movie *movieList) {
    int i = 0;
    int j = 0;
    while (tconstArray[i] != -2) {
      while (movieList[j].tconst != -1) {
        if (tconstArray[i] == movieList[j].tconst) {
          printf("%d: %s\n", i, movieList[j].primaryTitle);
          printf("         %s\n", movieList[j].originalTitle);
          break;
        }
        j++;
      }
      i++;
    }

  return;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Modified version of searchPrint used to print 10 movies */
void printNextTen(int *tconstArray, Movie *movieList, int start) {
    int i = start * 10;
    int j = 0;
    for (int a = 0; a < 10; a++) {
      if (tconstArray[i] != -2) {
        while (movieList[j].tconst != -1) {
          if (tconstArray[i] == movieList[j].tconst) {
            printf("%d: %s\n", i, movieList[j].primaryTitle);
            printf("         %s\n", movieList[j].originalTitle);
            break;
          }
          j++;
        }
        i++;
      }
    }
  return;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Searches the tree for the specified movie title */
  /* and returns a pointer to that movie */
Movie *titleSearch(Movie *masterTreeNode, Movie *searchMatches, char *searchTitle) {
  if (masterTreeNode == NULL) {
    return searchMatches;
  }

  int searchTitleLen = strlen(searchTitle);

  if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) < 0) {
    return titleSearch(masterTreeNode->left, searchMatches, searchTitle);
  }
  else if (strncmp(searchTitle, masterTreeNode->lowerTitle, searchTitleLen) > 0) {
    return titleSearch(masterTreeNode->right, searchMatches, searchTitle);
  }
  else {
    Movie *newMatch = malloc(sizeof(Movie));
    newMatch = movieCopy(newMatch, masterTreeNode);
    searchMatches = insert(searchMatches, newMatch);

    searchMatches = titleSearch(masterTreeNode->left, searchMatches, searchTitle);
    searchMatches = titleSearch(masterTreeNode->right, searchMatches, searchTitle);

    return searchMatches;
  }
  return NULL;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Filters the results of a search by genre */
//int *genreFilter(Movie *movieList, int *tconstArray, char genre) {
//}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Filters the results of a search by year */
//int *yearFilter(Movie *movieList, int *tconstArray, int lower, int higher) {
//}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Filters the results of a search by runtime */
//int *rtFilter(Movie *movieList, int *tconstArray, int lower, int higher) {
//}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Prints all movies of a certain genre */
//void printGenre(Movie *movieList, char genre) {
//}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Prints all movies released in a certain year */
//void printYear(Movie *movieList, int lower, int higher) {
//}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Prints all movies of a certain runtime */
//void printRt(Movie *movieList, int lower, int higher) {
//}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Not sure if I still need this, should probably delete it */
//Movie *findMovie(Movie *movieList, int tconst) {
//}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/
