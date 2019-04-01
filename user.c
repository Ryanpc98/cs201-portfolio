#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Allows the user to select a title from search to add to their list */
UserMovie *selectTitleToAdd(UserMovie *newUserMovie, Movie *movieChoice) {
  char tempChar;
  newUserMovie = malloc(sizeof(UserMovie));
  newUserMovie->tconst = movieChoice->tconst;

  newUserMovie->title = malloc((strlen(movieChoice->primaryTitle) + 1) * sizeof(char));
  newUserMovie->title = movieChoice->primaryTitle;

  newUserMovie->lowerTitle = malloc((strlen(newUserMovie->title) + 10) * sizeof(char));
  newUserMovie->lowerTitle = strLower(newUserMovie->lowerTitle, movieChoice->primaryTitle);
  newUserMovie->lowerTitle = removeArticles(newUserMovie->lowerTitle);
  int titleLen = strlen(newUserMovie->lowerTitle);

  newUserMovie->startYear = movieChoice->startYear;

  newUserMovie->height = 1;
  newUserMovie->left = NULL;
  newUserMovie->right = NULL;

  printf("Do you own this movie phyiscally or digitally?: \n");
  printf("(p for phyiscal or d for digital)\n");
  scanf("%c", &tempChar);
  clearIn();
  while (tempChar != 'p' && tempChar != 'd') {
    printf("Error, please try again: \n");
    printf("(p for phyiscal or d for digital)\n");
    scanf("%c", &tempChar);
    clearIn();
  }
  newUserMovie->ownershipType = tempChar;

  char tempDate[10];
  printf("When did you purchase this movie?: \n");
  printf("(Please enter in mm/dd/yyyy format)\n");
  for (int i = 0; i < 10; i++) {
    scanf("%c", &tempChar);
    tempDate[i] = tempChar;
  }
  clearIn();
  if (isdigit(tempDate[0]) && isdigit(tempDate[1])) {
    newUserMovie->mAquired = (10 *(tempDate[0] - '0')) + (tempDate[1] - '0');
    if (isdigit(tempDate[3]) && isdigit(tempDate[4])) {
      newUserMovie->dAquired = (10 * (tempDate[3] - '0')) + (tempDate[4] - '0');
      if (isdigit(tempDate[6]) && isdigit(tempDate[7]) && isdigit(tempDate[8]) && isdigit(tempDate[9])) {
        newUserMovie->yAquired = (1000 * (tempDate[6] - '0')) + (100 * (tempDate[7] - '0')) + (10 * (tempDate[8] - '0')) + (tempDate[9] - '0');
        int j = 0;
        for (int i = 0; i < 10; i++) {
          if (i != 2 && i != 5) {
            newUserMovie->lowerTitle[j + titleLen] = tempDate[i];
            j++;
          }
        }
        newUserMovie->lowerTitle[titleLen + 8] = newUserMovie->ownershipType;
        newUserMovie->lowerTitle[titleLen + 9] = '\0';
        return newUserMovie;
      }
    }
  }
  clearIn();
  while(1) {
    printf("Invalid date, please try again\n");
    printf("When did you purchase this movie?: \n");
    printf("(Please enter in mm/dd/yyyy format)\n");
    for (int i = 0; i < 10; i++) {
      scanf("%c", &tempChar);
      tempDate[i] = tempChar;
    }
    clearIn();
    if (isdigit(tempDate[0]) && isdigit(tempDate[1])) {
      newUserMovie->mAquired = (10 *(tempDate[0] - '0')) + (tempDate[1] - '0');
      if (isdigit(tempDate[3]) && isdigit(tempDate[4])) {
        newUserMovie->dAquired = (10 * (tempDate[3] - '0')) + (tempDate[4] - '0');
        if (isdigit(tempDate[6]) && isdigit(tempDate[7]) && isdigit(tempDate[8]) && isdigit(tempDate[9])) {
          newUserMovie->yAquired = (1000 * (tempDate[6] - '0')) + (100 * (tempDate[7] - '0')) + (10 * (tempDate[8] - '0')) + (tempDate[9] - '0');
          int j = 0;
          for (int i = 0; i < 10; i++) {
            if (i != 2 && i != 5) {
              newUserMovie->lowerTitle[j + strlen(newUserMovie->title)] = tempDate[i];
              j++;
            }
          }
          newUserMovie->lowerTitle[titleLen + 8] = newUserMovie->ownershipType;
          newUserMovie->lowerTitle[titleLen + 9] = '\0';
          return newUserMovie;
        }
      }
    }
  }
  return NULL;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Saves UserRoot's info to fp */
void saveFile(FILE *fp, UserMovie *root) {
  if(root != NULL) {
    fprintf(fp, "tt%.7d	%s	%d	%c	%.2d	%.2d	%.4d\n", root->tconst, root->title,
            root->startYear, root->ownershipType, root->mAquired,
            root->dAquired, root->yAquired);
    saveFile(fp, root->left);
    saveFile(fp, root->right);
  }
}
