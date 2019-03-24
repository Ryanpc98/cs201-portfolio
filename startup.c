#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"


/******************************************************************************/
/*                                                                            */
/******************************************************************************/

char *userLogin() {
  char *userFilename = malloc(100 * sizeof(char));
  for (int i = 0; i < 100; i++) {
    userFilename[i] = '\0';
  }
  char *userName = malloc(93 * sizeof(char));
  for (int i = 0; i < 94; i++) {
    userName[i] = '\0';
  }
  char *buffer = malloc(100 * sizeof(char));
  for (int i = 0; i < 94; i++) {
    buffer[i] = '\0';
  }
  char existUser;
  int choice;

  printf("Are you an existing user(y/n)? \n");
  scanf("%c", &existUser);
  while (existUser != 'y' && existUser != 'n') {
    printf("Error, please try again: \n");
    printf("(y for yes or n for no)\n");
    scanf("%c", &existUser);
  }

  printf("Please enter your username: \n");
  scanf("%s", userName);
  userFilename = strcat(userName, ".log");
  printf(".log added\n");

  /* Open File */
  FILE *fp;
  fp = fopen("userList.txt", "r");

  if (fp == NULL) {
   printf("%s\n", "Error in opening file");
   return NULL;
  }

  /* Check if User Exists */
  while (!feof(fp)) {
    fscanf(fp, "%s", buffer);
    printf("buffer: %s\n", buffer);
    if (!strcmp(buffer, userFilename)) {
      printf("match found\n");
      if (existUser == 'y') { //if filename already exists and user is existing
        free(userName);
        free(buffer);
        return userFilename;
      }
      else { //if filename already exists and user is not existing
        printf("Username already taken, please enter a different one: \n");
        scanf("%s\n", userName);
        userFilename = strcat(userName, ".log");
        rewind(fp);
      }
    }
    else { //if filename does not exist and user is existing
      if (existUser == 'y') {
        printf("Username not found, would you like to: \n");
        printf("  1: Enter a new name\n");
        printf("  2: Create a new user\n");
        scanf("%d", &choice);
        if (choice == 1) {
          printf("Please enter your username: \n");
          scanf("%s\n", userName);
          userFilename = strcat(userName, ".log");
        }
        else {
          free(userName);
          free(buffer);
          return userFilename;
        }
      }
      else { //if filename does not exist and user is not existing
        free(userName);
        free(buffer);
        return userFilename;
      }
    }
  }
  free(userName);
  free(buffer);
  return userFilename;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

Movie *readFromFile() {

  FILE *fp;
  fp = fopen("title.basics.tsv", "r");
  //fp = fopen("first.5k.txt", "r");

  if (fp == NULL) {
   printf("%s\n", "Error in opening file");
   return(NULL);
  }

  char tempTconst[8];
  char tempYear[5];
  char tempRuntime[4];
  char currLine[500];
  int numMovies;
  Movie *root;

  printf("Loading Movie Data...\n");
  while (!feof(fp)) {
    fgets(currLine, 500, fp);

    if (currLine[0] != 't' || currLine[1] != 't') {
      continue;
    }

    if (currLine[10] == 'm') {
      Movie *newMovie = malloc(sizeof(Movie));

      int linePos = 0;
      int varPos = 0;

      /*  Find tconst */
      for (int i = 2; i < 9; i++) {
        tempTconst[i - 2] = currLine[i];
      }
      newMovie->tconst = atoi(tempTconst);

      /*  Find primaryTitle */
      linePos = 16;
      varPos = 0;
      while (currLine[linePos] != '	') {
        newMovie->primaryTitle[varPos] = currLine[linePos];
        linePos++;
        varPos++;
      }
      newMovie->primaryTitle[varPos] = '\0';
      
      /* Find originalTitle */
      linePos++;
      varPos = 0;
      while (currLine[linePos] != '	') {
        newMovie->originalTitle[varPos] = currLine[linePos];
        linePos++;
        varPos++;
      }
      newMovie->originalTitle[varPos] = '\0';

      /* Find isAdult */
      linePos++;
      newMovie->isAdult = atoi(&currLine[linePos]);

      /* Find startYear */
      linePos += 2;
      if (currLine[linePos] == '\\') {
        newMovie->startYear = 0;
        linePos += 2;
      }
      else {
        for (varPos = 0; varPos < 4; varPos++) {
          tempYear[varPos] = currLine[linePos];
          linePos++;
        }
        tempYear[varPos] = '\0';
        newMovie->startYear = atoi(tempYear);
      }

      /* Find runtime */
      linePos += 4;               //skips endYear
      varPos = 0;
      if (currLine[linePos] == '\\') {    //finds null runtimes
        newMovie->runtime = 0;
        linePos += 2;
      }
      else {
        while (isalnum(currLine[linePos])) {
          tempRuntime[varPos] = currLine[linePos];
          linePos++;
          varPos++;
        }
        tempRuntime[varPos] = '\0';
        newMovie->runtime = atoi(tempRuntime);
      }

      /* Find genres */
      varPos = 0;
      while (currLine[linePos] != '\n') {
        linePos++;
        /* \N */
        if (currLine[linePos] == '\\') {
          newMovie->genres[varPos] = '0';
          linePos += 2;
        }
        /* A */
        else if (currLine[linePos] == 'A') {
          linePos++;
          if (currLine[linePos] == 'c') { //Action
            newMovie->genres[varPos] = 'a';
            varPos++;
            linePos += 5;
          }
          else if (currLine[linePos] == 'd') {
            linePos++;
            if (currLine[linePos] == 'v') { //Adventure
              newMovie->genres[varPos] = 'b';
              varPos++;
              linePos += 7;
            }
            else if (currLine[linePos] == 'u') { //Adult
              newMovie->genres[varPos] = 'c';
              varPos++;
              linePos += 3;
            }
            else {
              printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
              break;
            }
          }
          else if (currLine[linePos] == 'n') { //Animation
            newMovie->genres[varPos] = 'd';
            varPos++;
            linePos += 8;
          }
          else {
            printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
            break;
          }
        }
        /* B */
        else if (currLine[linePos] == 'B') { //Biography
          newMovie->genres[varPos] = 'e';
          varPos++;
          linePos += 9;
        }
        /* C */
        else if (currLine[linePos] == 'C') {
          linePos++;
          if (currLine[linePos] == 'o') { //Comedy
            newMovie->genres[varPos] = 'f';
            varPos++;
            linePos += 5;
          }
          else if (currLine[linePos] == 'r') { //Crime
            newMovie->genres[varPos] = 'g';
            varPos++;
            linePos += 4;
          }
          else {
            printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
            break;
          }
        }
        /* D */
        else if (currLine[linePos] == 'D') {
          linePos++;
          if (currLine[linePos] == 'o') { //Documentary
            newMovie->genres[varPos] = 'h';
            varPos++;
            linePos += 10;
          }
          else if (currLine[linePos] == 'r') { //Drama
            newMovie->genres[varPos] = 'i';
            varPos++;
            linePos += 4;
          }
          else {
            printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
            break;
          }
        }
        /* F */
        else if (currLine[linePos] == 'F') {
          linePos++;
          if (currLine[linePos] == 'a') {
            linePos++;
            if (currLine[linePos] == 'm') { //Family
              newMovie->genres[varPos] = 'j';
              varPos++;
              linePos += 4;
            }
            else if (currLine[linePos] == 'n') { //Fantasy
              newMovie->genres[varPos] = 'k';
              varPos++;
              linePos += 5;
            }
            else {
              printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
              break;
            }
          }
          else if (currLine[linePos] == 'i') { //Film-Noir
            newMovie->genres[varPos] = 'l';
            varPos++;
            linePos += 8;
          }
          else {
            printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
            break;
          }
        }
        /* G */
        else if (currLine[linePos] == 'G') { //Game-Show
          newMovie->genres[varPos] = 'm';
          varPos++;
          linePos += 9;
        }
        /* H */
        else if (currLine[linePos] == 'H') {
          linePos++;
          if (currLine[linePos] == 'i') { //History
            newMovie->genres[varPos] = 'n';
            varPos++;
            linePos += 6;
          }
          else if (currLine[linePos] == 'o') { //Horror
            newMovie->genres[varPos] = 'o';
            varPos++;
            linePos += 5;
          }
          else {
            printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
            break;
          }
        }
        /* M */
        else if (currLine[linePos] == 'M') {
          linePos++;
          if (currLine[linePos] == 'u') {
            linePos += 4;
            if (!isalpha(currLine[linePos])) { //Music
              newMovie->genres[varPos] = 'p';
              varPos++;
              linePos += 0;
            }
            else if (currLine[linePos] == 'a') { //Musical
              newMovie->genres[varPos] = 'q';
              varPos++;
              linePos += 2;
            }
            else {
              printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
              break;
            }
          }
          else if (currLine[linePos] == 'y') { //Mystery
            newMovie->genres[varPos] = 'r';
            varPos++;
            linePos += 6;
          }
          else {
            printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
            break;
          }
        }
        /* N */
        else if (currLine[linePos] == 'N') { //News
          newMovie->genres[varPos] = 's';
          varPos++;
          linePos += 4;
        }
        /* R */
        else if (currLine[linePos] == 'R') {
          linePos++;
          if (currLine[linePos] == 'o') { //Romance
            newMovie->genres[varPos] = 't';
            varPos++;
            linePos += 6;
          }
          else if (currLine[linePos] == 'e') { //Reality-TV
            newMovie->genres[varPos] = 'u';
            varPos++;
            linePos += 9;
          }
        }
        /* S */
        else if (currLine[linePos] == 'S') {
          linePos++;
          if (currLine[linePos] == 'c') { //Sci Fi
            newMovie->genres[varPos] = 'v';
            varPos++;
            linePos += 5;
          }
          else if (currLine[linePos] == 'h') { //Short
            newMovie->genres[varPos] = 'w';
            varPos++;
            linePos += 4;
          }
          else if (currLine[linePos] == 'p') { //Sport
            newMovie->genres[varPos] = 'x';
            varPos++;
            linePos += 4;
          }
          else if (currLine[linePos] == 'u') { //Superhero
            newMovie->genres[varPos] = 'y';
            varPos++;
            linePos += 8;
          }
          else {
            printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
            break;
          }
        }
        /* T */
        else if (currLine[linePos] == 'T') {
          linePos++;
          if (currLine[linePos] == 'a') { //Talk-Show
            newMovie->genres[varPos] = 'z';
            varPos++;
            linePos += 8;
          }
          else if (currLine[linePos] == 'h') { //Thriller
            newMovie->genres[varPos] = 'A';
            varPos++;
            linePos += 7;
          }
        }
        /* W */
        else if (currLine[linePos] == 'W') {
          linePos++;
          if (currLine[linePos] == 'a') { //War
            newMovie->genres[varPos] = 'B';
            varPos++;
            linePos += 2;
          }
          else if (currLine[linePos] == 'e') { //Western
            newMovie->genres[varPos] = 'C';
            varPos++;
            linePos += 6;
          }
          else {
            printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
            break;
          }
        }
        else {
          printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
          break;
        }
      }
      newMovie->genres[varPos] = '\0';

      //printf("%s\n", newMovie->primaryTitle);
      //preOrder(root);

      newMovie->left = NULL;
      newMovie->right = NULL;
      newMovie->height = 1;

      root = insert(root, newMovie);
      //printf("root: %s\n", root->primaryTitle);
      //preOrder(root);
      //printf("\n\n");
      numMovies++;
    }
  }
  printf("\nMovie Data Successfully Loaded\n");
  printf("\nnum movies: %d\n", numMovies);
  fclose(fp);

  return root;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/
