#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

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

 int *titleSearch(Movie *movieList, char *searchTitle) { /* complete rework */
  char tempSearchTitle[strlen(searchTitle)];

  for (int i = 0; i < strlen(searchTitle); i++) {
    tempSearchTitle[i] = tolower(searchTitle[i]);
  }
  tempSearchTitle[strlen(searchTitle)] = '\0';

  static int tconstArray[1000000];

  for (int i = 0; i < 1000000; i++) {
    tconstArray[i] = -2;
  }

  int arrayPos = 0;
  char tempPrimaryTitle[300];
  char tempOriginalTitle[300];

  int i = 0;
  while(movieList[i].tconst != -1) {

    /* Turning titles to lowercase */

    for (int j = 0; j < strlen(movieList[i].primaryTitle); j++) {
      tempPrimaryTitle[j] = tolower(movieList[i].primaryTitle[j]);
    }
    tempPrimaryTitle[strlen(movieList[i].primaryTitle)] = '\0';

    for (int k = 0; k < strlen(movieList[i].originalTitle); k++) {
      tempOriginalTitle[k] = tolower(movieList[i].originalTitle[k]);
    }
    tempOriginalTitle[strlen(movieList[i].originalTitle)] = '\0';

    /* Searching */

    if (strstr(tempPrimaryTitle, tempSearchTitle) != NULL) {
      tconstArray[arrayPos] = movieList[i].tconst;
      arrayPos++;
    }
    else if (strstr(tempOriginalTitle, tempSearchTitle) != NULL) {
      tconstArray[arrayPos] = movieList[i].tconst;
      arrayPos++;
    }
    i++;
  }
  printf("numMatches: %d\n", arrayPos);
  return tconstArray;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

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
