#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Allows the user to select a title from search to add to their list */
UserMovie *selectTitleToAdd(Movie *masterTreeNode) {
  char tempChar;
  char *userTitle = malloc(196 * sizeof(char));
  UserMovie *newUserMovie = malloc(sizeof(UserMovie));

  printf("Enter the title of the movie you wish to add to your list or\n");
  printf("!back to go back\n");
  int i = 0;
  scanf("%c", &tempChar);
  while (tempChar != '\n') {
    userTitle[i] = tolower(tempChar);
    i++;
    if (i >= 195) {
      /* clear out the rest of input */
      clearIn();
    }
    scanf("%c", &tempChar);
  }
  userTitle[i] = '\0';

  if (!strcmp(userTitle, "!back")) {
    //do something else
    printf("back\n");
    return NULL;
  }

  else {
    userTitle = removeArticles(userTitle);

    Movie *movieChoice;
    movieChoice = NULL;
    movieChoice = malloc(sizeof(Movie));
    movieChoice = titleSearchExact(masterTreeNode, movieChoice, userTitle);

    while (movieChoice == NULL) {
      printf("Enter the title of the movie you wish to add to your list or\n");
      printf("!back to go back\n");
      i = 0;
      scanf("%c", &tempChar);
      while (tempChar != '\n') {
        userTitle[i] = tempChar;
        i++;
        if (i >= 195) {
          /* clear out the rest of input */
          clearIn();
        }
        scanf("%c", &tempChar);
        userTitle[i] = tolower(tempChar);
      }
      userTitle[i] = '\0';

      if (!strcmp(userTitle, "!back")) {
        //do something else
        printf("back\n");
        return NULL;
      }
      else {
        movieChoice = titleSearchExact(masterTreeNode, movieChoice, userTitle);
      }
    }
    newUserMovie->tconst = movieChoice->tconst;
    newUserMovie->title = movieChoice->primaryTitle;
    newUserMovie->lowerTitle = movieChoice->lowerTitle;
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
    if (isdigit(tempDate[0]) && isdigit(tempDate[1])) {
      newUserMovie->mAquired = (10 *(tempDate[0] - '0')) + (tempDate[1] - '0');
      if (isdigit(tempDate[3]) && isdigit(tempDate[4])) {
        newUserMovie->dAquired = (10 * (tempDate[3] - '0')) + (tempDate[4] - '0');
        if (isdigit(tempDate[6]) && isdigit(tempDate[7]) && isdigit(tempDate[8]) && isdigit(tempDate[9])) {
          newUserMovie->yAquired = (1000 * (tempDate[6] - '0')) + (100 * (tempDate[7] - '0'))
                + (10 * (tempDate[8] - '0')) + (tempDate[9] - '0');
        }
      }
      return newUserMovie;
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
      if (isdigit(tempDate[0]) && isdigit(tempDate[1])) {
        newUserMovie->mAquired = (10 *(tempDate[0] - '0')) + (tempDate[1] - '0');
        if (isdigit(tempDate[3]) && isdigit(tempDate[4])) {
          newUserMovie->dAquired = (10 * (tempDate[3] - '0')) + (tempDate[4] - '0');
          if (isdigit(tempDate[6]) && isdigit(tempDate[7]) && isdigit(tempDate[8]) && isdigit(tempDate[9])) {
            newUserMovie->yAquired = (1000 * (tempDate[6] - '0')) + (100 * (tempDate[7] - '0'))
                  + (10 * (tempDate[8] - '0')) + (tempDate[9] - '0');
          }
        }
        return newUserMovie;
      }
      clearIn();
    }
  }

  return NULL;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Allows the user to select a title from their list to remove */
UserMovie *selectTitleToRemove(UserMovie *userRoot) {
  char tempChar;
  char *userTitle = malloc(196 * sizeof(char));

  printf("Enter the title of the movie you wish to remove from your list or\n");
  printf("!back to go back\n");
  int i = 0;
  scanf("%c", &tempChar);
  while (tempChar != '\n') {
    userTitle[i] = tolower(tempChar);
    i++;
    if (i >= 195) {
      /* clear out the rest of input */
      clearIn();
    }
    scanf("%c", &tempChar);
  }
  userTitle[i] = '\0';

  if (!strcmp(userTitle, "!back")) {
    //do something else
    printf("back\n");
    return NULL;
  }

  else {
    userTitle = removeArticles(userTitle);

    UserMovie *movieChoice;
    movieChoice = NULL;
    movieChoice = malloc(sizeof(UserMovie));
    movieChoice = titleSearchExactUser(userRoot, movieChoice, userTitle);

    while (movieChoice == NULL) {
      printf("Enter the title of the movie you wish to remove from your list or\n");
      printf("!back to go back\n");
      i = 0;
      scanf("%c", &tempChar);
      while (tempChar != '\n') {
        userTitle[i] = tempChar;
        i++;
        if (i >= 195) {
          /* clear out the rest of input */
          clearIn();
        }
        scanf("%c", &tempChar);
        userTitle[i] = tolower(tempChar);
      }
      userTitle[i] = '\0';

      if (!strcmp(userTitle, "!back")) {
        //do something else
        printf("back\n");
        return NULL;
      }
      else {
        userTitle = removeArticles(userTitle);

        movieChoice = titleSearchExactUser(userRoot, movieChoice, userTitle);
      }
    }
    return movieChoice;
  }
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

UserMovie *selectTitleToModify() {
  char tempChar;
  char *userTitle = malloc(196 * sizeof(char));

  printf("Enter the title of the movie you wish to modify or\n");
  printf("!back to go back\n");
  int i = 0;
  scanf("%c", &tempChar);
  while (tempChar != '\n') {
    userTitle[i] = tolower(tempChar);
    i++;
    if (i >= 195) {
      /* clear out the rest of input */
      clearIn();
    }
    scanf("%c", &tempChar);
  }
  userTitle[i] = '\0';

  if (!strcmp(userTitle, "!back")) {
    //do something else
    printf("back\n");
    return NULL;
  }

  else {
    userTitle = removeArticles(userTitle);

    UserMovie *movieChoice;
    movieChoice = NULL;
    movieChoice = malloc(sizeof(UserMovie));
    movieChoice = titleSearchExactUser(userRoot, movieChoice, userTitle);

    while (movieChoice == NULL) {
      printf("Enter the title of the movie you wish to modify or\n");
      printf("!back to go back\n");
      i = 0;
      scanf("%c", &tempChar);
      while (tempChar != '\n') {
        userTitle[i] = tempChar;
        i++;
        if (i >= 195) {
          /* clear out the rest of input */
          clearIn();
        }
        scanf("%c", &tempChar);
        userTitle[i] = tolower(tempChar);
      }
      userTitle[i] = '\0';

      if (!strcmp(userTitle, "!back")) {
        //do something else
        printf("back\n");
        return NULL;
      }
      else {
        userTitle = removeArticles(userTitle);

        movieChoice = titleSearchExactUser(userRoot, movieChoice, userTitle);
      }
    }
    return movieChoice;
  }
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void saveFile(FILE *fp, UserMovie *root) {
  if(root != NULL) {
    fprintf(fp, "tt%.7d	%s	%d	%c	%.2d	%.2d	%.4d\n", root->tconst, root->title,
            root->startYear, root->ownershipType, root->mAquired,
            root->dAquired, root->yAquired);
    saveFile(fp, root->left);
    saveFile(fp, root->right);
  }
}
