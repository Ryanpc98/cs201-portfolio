#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"


/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Determines if user already exists or not */
/* If they do exist is opens their .log file */
/* If not, it creates a new one */
char *userLogin() {
  char *userFilename = malloc(100 * sizeof(char));
  for (int i = 0; i < 100; i++) {
    userFilename[i] = '\0';
  }

  char choice;

  printf("Please enter your username: \n");
  scanf("%s", userFilename);
  userFilename = strcat(userFilename, ".log");
  printf(".log added\n");
  printf("filename: %s\n", userFilename);

  /* Open File */
  FILE *fp;
  fp = fopen(userFilename, "r");

  if (fp == NULL) {
   printf("No matching file found\n\n");
   printf("Create a new one? (y/n): ");
   scanf("%c", &choice);

   while (choice != 'y' && choice != 'n') {
     printf("Please enter y for yes or n for no: ");
     scanf("%c", &choice);
   }

   if (choice == 'y') {
     return userFilename;
   }
   else if (choice == 'n') {
     fclose(fp);
     return userLogin();
   }
 }

 else {
   printf("User found\n");
   printf("Are you looking for an existing list? (y/n): ");
   scanf("%c", &choice);

   while (choice != 'y' && choice != 'n') {
     printf("Please enter y for yes or n for no: ");
     scanf("%c", &choice);
   }

   if (choice == 'y') {
     return userFilename;
   }
   else if (choice == 'n') {
     printf("Please try a different username\n");
     return userLogin();
   }
 }

 return NULL;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Reads in all relevant information about each movie into memory */

#pragma GCC diagnostic error "-Wframe-larger-than="

Movie *readFromFile() {

  FILE *fp;
  fp = fopen("title.basics.tsv", "r");

  if (fp == NULL) {
   printf("%s\n", "Error in opening imdb file");
   return(NULL);
  }

  char tempPrimaryTitle[201];
  char tempOriginalTitle[201];
  char tempTconst[8];
  char tempYear[5];
  char tempRuntime[4];
  char tempGenres[29];  //29 is the number of genres, and thus max possible number
  char currLine[500];
  int numMovies = 0;
  Movie *root = NULL;

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
      tempTconst[7] = '\0';
      newMovie->tconst = atoi(tempTconst);

      /*  Find primaryTitle */
      linePos = 16;
      varPos = 0;
      while (currLine[linePos] != '	' && varPos < 200) {
        tempPrimaryTitle[varPos] = currLine[linePos];
        linePos++;
        varPos++;
      }
      if (varPos == 200) {
        for (int i = 196; i < 199; i++) {
          tempPrimaryTitle[196] = '.';
        }
        while (currLine[linePos] != '	') {
          linePos++;
        }
      }
      tempPrimaryTitle[varPos] = '\0';
      newMovie->primaryTitle = malloc((varPos + 1) * sizeof(char));
      strcpy(newMovie->primaryTitle, tempPrimaryTitle);

      /* Find originalTitle */
      linePos++;
      varPos = 0;
      while (currLine[linePos] != '	' && varPos < 200) {
        tempOriginalTitle[varPos] = currLine[linePos];
        linePos++;
        varPos++;
      }
      if (varPos == 200) {
        for (int i = 196; i < 199; i++) {
          tempOriginalTitle[196] = '.';
        }
        while (currLine[linePos] != '	') {
          linePos++;
        }
      }
      tempOriginalTitle[varPos] = '\0';
      newMovie->originalTitle = malloc((varPos + 1) * sizeof(char));
      strcpy(newMovie->originalTitle, tempOriginalTitle);

      /* Set lowerTitle */
      newMovie->lowerTitle = malloc((varPos + 8) * sizeof(char));
      newMovie->lowerTitle = strLower(newMovie->lowerTitle, newMovie->primaryTitle);
      strcat(newMovie->lowerTitle, tempTconst);

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
          tempGenres[varPos] = '0';
          linePos += 2;
        }
        /* A */
        else if (currLine[linePos] == 'A') {
          linePos++;
          if (currLine[linePos] == 'c') { //Action
            tempGenres[varPos] = 'a';
            varPos++;
            linePos += 5;
          }
          else if (currLine[linePos] == 'd') {
            linePos++;
            if (currLine[linePos] == 'v') { //Adventure
              tempGenres[varPos] = 'b';
              varPos++;
              linePos += 7;
            }
            else if (currLine[linePos] == 'u') { //Adult
              tempGenres[varPos] = 'c';
              varPos++;
              linePos += 3;
            }
            else {
              printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
              break;
            }
          }
          else if (currLine[linePos] == 'n') { //Animation
            tempGenres[varPos] = 'd';
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
          tempGenres[varPos] = 'e';
          varPos++;
          linePos += 9;
        }
        /* C */
        else if (currLine[linePos] == 'C') {
          linePos++;
          if (currLine[linePos] == 'o') { //Comedy
            tempGenres[varPos] = 'f';
            varPos++;
            linePos += 5;
          }
          else if (currLine[linePos] == 'r') { //Crime
            tempGenres[varPos] = 'g';
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
            tempGenres[varPos] = 'h';
            varPos++;
            linePos += 10;
          }
          else if (currLine[linePos] == 'r') { //Drama
            tempGenres[varPos] = 'i';
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
              tempGenres[varPos] = 'j';
              varPos++;
              linePos += 4;
            }
            else if (currLine[linePos] == 'n') { //Fantasy
              tempGenres[varPos] = 'k';
              varPos++;
              linePos += 5;
            }
            else {
              printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
              break;
            }
          }
          else if (currLine[linePos] == 'i') { //Film-Noir
            tempGenres[varPos] = 'l';
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
          tempGenres[varPos] = 'm';
          varPos++;
          linePos += 9;
        }
        /* H */
        else if (currLine[linePos] == 'H') {
          linePos++;
          if (currLine[linePos] == 'i') { //History
            tempGenres[varPos] = 'n';
            varPos++;
            linePos += 6;
          }
          else if (currLine[linePos] == 'o') { //Horror
            tempGenres[varPos] = 'o';
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
              tempGenres[varPos] = 'p';
              varPos++;
              linePos += 0;
            }
            else if (currLine[linePos] == 'a') { //Musical
              tempGenres[varPos] = 'q';
              varPos++;
              linePos += 2;
            }
            else {
              printf("genre error at %c (%d)\n", currLine[linePos], newMovie->tconst);
              break;
            }
          }
          else if (currLine[linePos] == 'y') { //Mystery
            tempGenres[varPos] = 'r';
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
          tempGenres[varPos] = 's';
          varPos++;
          linePos += 4;
        }
        /* R */
        else if (currLine[linePos] == 'R') {
          linePos++;
          if (currLine[linePos] == 'o') { //Romance
            tempGenres[varPos] = 't';
            varPos++;
            linePos += 6;
          }
          else if (currLine[linePos] == 'e') { //Reality-TV
            tempGenres[varPos] = 'u';
            varPos++;
            linePos += 9;
          }
        }
        /* S */
        else if (currLine[linePos] == 'S') {
          linePos++;
          if (currLine[linePos] == 'c') { //Sci Fi
            tempGenres[varPos] = 'v';
            varPos++;
            linePos += 5;
          }
          else if (currLine[linePos] == 'h') { //Short
            tempGenres[varPos] = 'w';
            varPos++;
            linePos += 4;
          }
          else if (currLine[linePos] == 'p') { //Sport
            tempGenres[varPos] = 'x';
            varPos++;
            linePos += 4;
          }
          else if (currLine[linePos] == 'u') { //Superhero
            tempGenres[varPos] = 'y';
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
            tempGenres[varPos] = 'z';
            varPos++;
            linePos += 8;
          }
          else if (currLine[linePos] == 'h') { //Thriller
            tempGenres[varPos] = 'A';
            varPos++;
            linePos += 7;
          }
        }
        /* W */
        else if (currLine[linePos] == 'W') {
          linePos++;
          if (currLine[linePos] == 'a') { //War
            tempGenres[varPos] = 'B';
            varPos++;
            linePos += 2;
          }
          else if (currLine[linePos] == 'e') { //Western
            tempGenres[varPos] = 'C';
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
      tempGenres[varPos] = '\0';
      newMovie->genres = malloc(varPos * sizeof(char));
      strcpy(newMovie->genres, tempGenres);

      newMovie->left = NULL;
      newMovie->right = NULL;
      newMovie->height = 1;

      root = insert(root, newMovie);
      numMovies++;
    }
  }
  printf("\nSuccessfully Loaded %d Movies\n\n", numMovies);
  fclose(fp);

  return root;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

char *strLower(char *dest, char *src) {
  int len = strlen(src);

  for (int i = 0; i < len; i++) {
    dest[i] = tolower(src[i]);
  }
  dest[len] = '\0';

  return dest;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/
