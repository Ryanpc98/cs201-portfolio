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
  int nodeTitleLen = strlen(masterTreeNode->lowerTitle);

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
int *genreFilter(Movie *movieList, int *tconstArray, char genre) {
  static int filteredArray[1000000];

  for (int i = 0; i < 1000000; i++) {
    filteredArray[i] = -2;
  }

  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;

  while (tconstArray[a] != -2) {
    while (movieList[b].tconst != -1) {
      if (tconstArray[a] == movieList[b].tconst) {
        c = 0;
        while (movieList[b].genres[c] != '0') {
          if (movieList[b].genres[c] == genre) {
            filteredArray[d] = tconstArray[a];
            d++;
            break;
          }
          c++;
        }
        break;
      }
      b++;
    }
    a++;
  }

  printf("numGenreMatches: %d\n", d);

  return filteredArray;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Filters the results of a search by year */
int *yearFilter(Movie *movieList, int *tconstArray, int lower, int higher) {
  static int filteredArray[1000000];

  for (int i = 0; i < 1000000; i++) {
    filteredArray[i] = -2;
  }

  int a = 0;
  int b = 0;
  int c = 0;

  while (tconstArray[a] != -2) {
    //printf("%d, %d, %d\n", a, b, c);
    b = 0;
    while (movieList[b].tconst != -1) {
      if (tconstArray[a] == movieList[b].tconst) {
        printf("%d: %s\n", movieList[b].startYear, movieList[b].primaryTitle);
        if (movieList[b].startYear >= lower && movieList[b].startYear <= higher) {
          filteredArray[c] = movieList[b].tconst;
          c++;
          break;
        }
      }
      b++;
    }
    a++;
  }

  printf("numYearMatches: %d\n", c);

  return filteredArray;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Filters the results of a search by runtime */
int *rtFilter(Movie *movieList, int *tconstArray, int lower, int higher) {
  static int filteredArray[1000000];

  for (int i = 0; i < 1000000; i++) {
    filteredArray[i] = -2;
  }

  int a = 0;
  int b = 0;
  int c = 0;

  while (tconstArray[a] != -2) {
    //printf("%d, %d, %d\n", a, b, c);
    b = 0;
    while (movieList[b].tconst != -1) {
      if (tconstArray[a] == movieList[b].tconst) {
        printf("%d: %s\n", movieList[b].runtime, movieList[b].primaryTitle);
        if (movieList[b].runtime >= lower && movieList[b].runtime <= higher) {
          filteredArray[c] = movieList[b].tconst;
          c++;
          break;
        }
      }
      b++;
    }
    a++;
  }

  printf("numRtMatches: %d\n", c);

  return filteredArray;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Prints all movies of a certain genre */
void printGenre(Movie *movieList, char genre) {

  int i = 0;
  int j = 0;
  int numPrints = 0;

  while (movieList[i].tconst != -1) {
    j = 0;
    while (movieList[i].genres[j] != '0') {
      if (movieList[i].genres[j] == genre) {
        printf("%s\n", movieList[i].primaryTitle);
        numPrints++;
        break;
      }
      j++;
    }
    i++;
  }

  printf("numGenrePrints: %d\n", numPrints);

  return;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Prints all movies released in a certain year */
void printYear(Movie *movieList, int lower, int higher) {

  int i = 0;
  int numPrints = 0;

  while (movieList[i].tconst != -1) {
    if (movieList[i].startYear >= lower && movieList[i].startYear <= higher) {
      printf("%s\n", movieList[i].primaryTitle);
      numPrints++;
    }
    i++;
  }

  printf("numYearPrints: %d\n", numPrints);

  return;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Prints all movies of a certain runtime */
void printRt(Movie *movieList, int lower, int higher) {

  int i = 0;
  int numPrints = 0;

  while (movieList[i].tconst != -1) {
    if (movieList[i].runtime >= lower && movieList[i].runtime <= higher) {
      printf("%s\n", movieList[i].primaryTitle);
      numPrints++;
    }
    i++;
  }

  printf("numRtPrints: %d\n", numPrints);

  return;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Not sure if I still need this, should probably delete it */
Movie *findMovie(Movie *movieList, int tconst) {
  int i = 0;

  while (movieList[i].tconst != -1) {
    if (movieList[i].tconst == tconst) {
      return &movieList[i];
    }
    i++;
  }

  return NULL;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/
