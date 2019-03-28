#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Allows the user to select a title from search to add to their list */
UserMovie *selectTitleToAdd(Movie *movieList, int *tconstArray, UserMovie *userArray) {
  int userNum;
  char ownType;
  UserMovie newUserMovie;

  printf("Enter the number of the movie to add to the list: ");
  scanf("%d", &userNum);

  newUserMovie.tconst = tconstArray[userNum];

  printf("Do you own this movie phyiscally or digitally?: \n");
  printf("(p for phyiscal or d for digital)\n");
  scanf("%c", &ownType);
  newUserMovie.ownershipType = ownType;
  while (ownType != 'p' && ownType != 'd') {
    printf("Error, please try again: \n");
    printf("(p for phyiscal or d for digital)\n");
    scanf("%c", &ownType);
    newUserMovie.ownershipType = ownType;
  }

  int i = 0;

  while (userArray[i].tconst != -2) {
    if (userArray[i].tconst == newUserMovie.tconst) {
      printf("%d already exists in file\n", newUserMovie.tconst);
      return userArray;
    }
    i++;
  }

  userArray[i] = newUserMovie;

  return userArray;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Allows the user to select a title from their list to remove */
UserMovie *selectTitleToRemove(Movie *movieList, UserMovie *userArray) {
  int userNum;

  printf("Enter the number of the movie to remove from the list: ");
  scanf("%d", &userNum);

  int i = userNum;

  while (userArray[i].tconst != -2) {
    userArray[i] = userArray[i + 1];
    i++;
  }

  return userArray;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Prints out a users list of movies */
void userArrayPrint(UserMovie *tconstArray, Movie *movieList) {
    int i = 0;
    int j = 0;
    while (tconstArray[i].tconst != -2) {
      j = 0;
      while (movieList[j].tconst != -1) {
        if (tconstArray[i].tconst == movieList[j].tconst) {
          printf("%d: %s\n", i, movieList[j].primaryTitle);
          printf("   %s\n", movieList[j].originalTitle);
          if (tconstArray[i].ownershipType == 'p') {
            printf("   phyiscal\n");
          }
          if (tconstArray[i].ownershipType == 'd') {
            printf("   digital\n");
          }
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

void saveFile(FILE *fp, UserMovie *root) {
  if(root != NULL) {
    fprintf(fp, "%d//%s//%c//%s", root->tconst, root->title,
                              root->ownershipType, root->dateAquired);
    saveFile(fp, root->left);
    saveFile(fp, root->right);
  }
}
