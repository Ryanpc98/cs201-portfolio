#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"


/******************************************************************************/
/*                                                                            */
/******************************************************************************/
/* Gets filename as input from user */
/* Ensures that filename is valid length */
char *getUserFilename() {
  char userName[100];
  for (int i = 0; i < 100; i++) {
    userName[i] = '\0';
  }
  char tempChar = 0;
  int i = 0;
  scanf("%c", &tempChar);
  while (tempChar != '\n') {
    userName[i] = tempChar;
    i++;
    if (i >= 95) {
      printf("Username too long\n");
      printf("Username being truncated at ");
      printf("...");
      for (int j = 3; j > 0; j--) {
        printf("%c", userName[i - j]);
      }
      printf("\n\n");
      break;
    }
    scanf("%c", &tempChar);
  }

  char *userFilename = malloc((strlen(userName) + 1) * sizeof(char));
  strcpy(userFilename, userName);
  strcat(userFilename, ".log");
  return userFilename;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Determines if user already exists or not */
/* Prompts the user about whether or not they exist or not but
   this function does not actually modify any of the text files */
int userLogin(char *userFilename) {
  char choice;

  /* Open File */
  FILE *fp;
  fp = fopen(userFilename, "r");

  if (fp == NULL) {
   printf("No matching file found\n\n");
   printf("Create a new one? (y/n): ");
   scanf("%c", &choice);
   clearIn();

   while (choice != 'y' && choice != 'n') {
     printf("Please enter y for yes or n for no: ");
     scanf("%c", &choice);
     clearIn();
   }

   if (choice == 'y') {
     fclose(fp);
     return 1;
   }
   else if (choice == 'n') {
     fclose(fp);
     return -1;
   }
 }

 else {
   printf("\nAre you looking for an existing list? (y/n): ");
   scanf("%c", &choice);
   clearIn();

   while (choice != 'y' && choice != 'n') {
     printf("\nPlease enter y for yes or n for no: ");
     scanf("%c", &choice);
     clearIn();
   }

   if (choice == 'y') {
     fclose(fp);
     return 1;
   }
   else if (choice == 'n') {
     printf("\nPlease try a different username\n");
     fclose(fp);
     return -1;
   }
 }
 return -2;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Reads in all relevant information about each movie into memory */
Movie *readImdbFile() {

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

  printf("\n\nLoading IMDB Movie Data...\n");
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

      /* Set lowerTitle */
      newMovie->lowerTitle = malloc((varPos + 8) * sizeof(char));
      newMovie->lowerTitle = strLower(newMovie->lowerTitle, newMovie->primaryTitle);
      strcat(newMovie->lowerTitle, tempTconst);
      newMovie->lowerTitle = removeArticles(newMovie->lowerTitle);

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

      /* Fair warning, this part is kind of long and crazy */
      /* genre_conversions.txt may help a little bit with this
         since it shows all the genres */
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
  printf("Successfully Loaded %d Movies\n", numMovies);
  fclose(fp);

  return root;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Works similarly to readImdbFile() but for the UserMovie information */
UserMovie *readUserFile(char *filename) {
  FILE *fp;
  fp = fopen(filename, "r");

  if (fp == NULL) {
   return NULL;
  }

  int numMovies = 0;
  char currLine[500];
  char tempPrimaryTitle[200];
  char tempTconst[8];
  char tempYear[5];
  int linePos = 0;
  int varPos = 0;
  UserMovie *root = malloc(sizeof(UserMovie));
  root = NULL;

  printf("\n\nLoading User Movie Data...\n");
  while (!feof(fp)) {
    fgets(currLine, 500, fp);

   UserMovie *newMovie = malloc(sizeof(UserMovie));

    /*  Find tconst */
    for (int i = 2; i < 9; i++) {
      tempTconst[i - 2] = currLine[i];
    }
    tempTconst[7] = '\0';
    newMovie->tconst = atoi(tempTconst);

    /*  Find title */
    linePos = 10;
    varPos = 0;
    while (currLine[linePos] != '	' && varPos < 200) {
      tempPrimaryTitle[varPos] = currLine[linePos];
      linePos++;
      varPos++;
    }
    tempPrimaryTitle[varPos] = '\0';
    newMovie->title = malloc((varPos + 1) * sizeof(char));
    strcpy(newMovie->title, tempPrimaryTitle);

    /* find lowerTitle */
    newMovie->lowerTitle = malloc((varPos + 10) * sizeof(char));
    newMovie->lowerTitle = strLower(newMovie->lowerTitle, newMovie->title);
    newMovie->lowerTitle = removeArticles(newMovie->lowerTitle);
    int titleLen = strlen(newMovie->lowerTitle);

    /* find startYear */
    linePos++;
    if (currLine[linePos] == '0') {
      newMovie->startYear = 0;
      linePos++;
    }
    else {
      for (varPos = 0; varPos < 4; varPos++) {
        tempYear[varPos] = currLine[linePos];
        linePos++;
      }
      tempYear[varPos] = '\0';
      newMovie->startYear = atoi(tempYear);
    }

    /* find ownershipType */
    linePos++;
    newMovie->ownershipType = currLine[linePos];

    int yearStart = 0;

    /* find mAquired */
    linePos += 2;
    yearStart = linePos;
    newMovie->mAquired = (10 * (currLine[linePos] -'0')) + (currLine[linePos + 1] - '0');

    /* find dAquired */
    linePos += 3;
    newMovie->dAquired = (10 * (currLine[linePos] -'0')) + (currLine[linePos + 1] - '0');

    /* find yAquired */
    linePos += 3;
    newMovie->yAquired = (1000 * (currLine[linePos] -'0')) + (100 * (currLine[linePos + 1] - '0')) +
        (10 * (currLine[linePos + 2] - '0')) + (currLine[linePos + 3] - '0');

    int j = 0;
    for (int i = 0; i < 10; i++) {
      if (i != 2 && i != 5) {
        newMovie->lowerTitle[j + titleLen] = currLine[yearStart + i];
        j++;
      }
    }
    newMovie->lowerTitle[titleLen + 8] = newMovie->ownershipType;
    newMovie->lowerTitle[titleLen + 9] = '\0';

    newMovie->left = NULL;
    newMovie->right = NULL;
    newMovie->height = 1;

    root = insertUser(root, newMovie);
    numMovies++;
  }

  printf("Successfully Loaded %d Movies\n", numMovies - 1);
  fclose(fp);

  return root;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Converts all chars in a str to lowercase */
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

/* Copies a Movie */
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

/* Copies an UserMovie */
UserMovie *movieCopyUser(UserMovie *dest, UserMovie *src) {
  dest->tconst = src->tconst;
  dest->title = src->title;
  dest->lowerTitle = src->lowerTitle;
  dest->startYear = src->startYear;
  dest->ownershipType = src->ownershipType;
  dest->mAquired = src->mAquired;
  dest->dAquired = src->dAquired;
  dest->yAquired = src->yAquired;
  dest->height = 1;
  dest->left = NULL;
  dest->right = NULL;

  return dest;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Clears out all junk input after a char is read in */
void clearIn() {
  char tempChar = 0;
  scanf("%c", &tempChar);
  while (tempChar != '\n') {
    scanf("%c", &tempChar);
  }
  return;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Removes "the" and "a" from the beginning of strings */
char *removeArticles(char *str) {
  if (str[0] == 'T' || str[0] == 't') {
    if (str[1] == 'H' || str[1] == 'h') {
      if (str[2] == 'E' || str[2] == 'e') {
        if (str[3] == ' ') {
          int len = strlen(str);
          for (int i = 0; i < len - 4; i++) {
            str[i] = str[i + 4];
          }
          for (int i = 0; i < 5; i++) {
            str[len - i] =  '\0';
          }
          return str;
        }
      }
    }
  }
  else if (str[0] == 'A' || str[0] == 'a') {
    if (str[1] == ' ') {
      int len = strlen(str);
      for (int i = 0; i < len - 2; i++) {
        str[i] = str[i + 2];
      }
      for (int i = 0; i < 3; i++) {
        str[len - i] =  '\0';
      }
      return str;
    }
  }
  return str;
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

/* Takes a string and converts it to the corresponding char */
/* User genre_conversions.txt for reference if this is confusing */
char encodeGenre(char *genre) {
  genre = strLower(genre, genre);
  int i = 0;
  while (1) {
    /* A */
    if (genre[i] == 'a') {
      i++;
      if (genre[i] == 'c') { //Action
        return 'a';
      }
      else if (genre[i] == 'd') {
        i++;
        if (genre[i] == 'v') { //Adventure
          return 'b';
          i++;
        }
        else if (genre[i] == 'u') { //Adult
          return 'c';
          i++;
        }
        else {
          printf("genre error at %s \n", genre);
          break;
        }
      }
      else if (genre[i] == 'n') { //Animation
        return 'd';
        i++;
      }
      else {
        printf("genre error at %s \n", genre);
        break;
      }
    }
    /* B */
    else if (genre[i] == 'b') { //Biography
      return 'e';
      i++;
    }
    /* C */
    else if (genre[i] == 'c') {
      i++;
      if (genre[i] == 'o') { //Comedy
        return 'f';
        i++;
      }
      else if (genre[i] == 'r') { //Crime
        return 'g';
        i++;
      }
      else {
        printf("genre error at %s \n", genre);
        break;
      }
    }
    /* D */
    else if (genre[i] == 'd') {
      i++;
      if (genre[i] == 'o') { //Documentary
        return 'h';
        i++;
      }
      else if (genre[i] == 'r') { //Drama
        return 'i';
        i++;
      }
      else {
        printf("genre error at %s \n", genre);
        break;
      }
    }
    /* F */
    else if (genre[i] == 'g') {
      i++;
      if (genre[i] == 'a') {
        i++;
        if (genre[i] == 'm') { //Family
          return 'j';
          i++;
        }
        else if (genre[i] == 'n') { //Fantasy
          return 'k';
          i++;
        }
        else {
          printf("genre error at %s \n", genre);
          break;
        }
      }
      else if (genre[i] == 'i') { //Film-Noir
        return 'l';
        i++;
      }
      else {
        printf("genre error at %s \n", genre);
        break;
      }
    }
    /* G */
    else if (genre[i] == 'g') { //Game-Show
      return 'm';
      i++;
    }
    /* H */
    else if (genre[i] == 'h') {
      i++;
      if (genre[i] == 'i') { //History
        return 'n';
        i++;
      }
      else if (genre[i] == 'o') { //Horror
        return 'o';
        i++;
      }
      else {
        printf("genre error at %s \n", genre);
        break;
      }
    }
    /* M */
    else if (genre[i] == 'm') {
      i++;
      if (genre[i] == 'u') {
        if (!isalpha(genre[i])) { //Music
          return 'p';
          i++;
        }
        else if (genre[i] == 'a') { //Musical
          return 'q';
          i++;
        }
        else {
          printf("genre error at %s \n", genre);
          break;
        }
      }
      else if (genre[i] == 'y') { //Mystery
        return 'r';
        i++;
      }
      else {
        printf("genre error at %s \n", genre);
        break;
      }
    }
    /* N */
    else if (genre[i] == 'n') { //News
      return 's';
      i++;
    }
    /* R */
    else if (genre[i] == 'r') {
      i++;
      if (genre[i] == 'o') { //Romance
        return 't';
        i++;
      }
      else if (genre[i] == 'e') { //Reality-TV
        return 'u';
        i++;
      }
    }
    /* S */
    else if (genre[i] == 's') {
      i++;
      if (genre[i] == 'c') { //Sci Fi
        return 'v';
        i++;
      }
      else if (genre[i] == 'h') { //Short
        return 'w';
        i++;
      }
      else if (genre[i] == 'p') { //Sport
        return 'x';
        i++;
      }
      else if (genre[i] == 'u') { //Superhero
        return 'y';
        i++;
      }
      else {
        printf("genre error at %s \n", genre);
        break;
      }
    }
    /* T */
    else if (genre[i] == 't') {
      i++;
      if (genre[i] == 'a') { //Talk-Show
        return 'z';
        i++;
      }
      else if (genre[i] == 'h') { //Thriller
        return 'A';
        i++;
      }
    }
    /* W */
    else if (genre[i] == 'w') {
      i++;
      if (genre[i] == 'a') { //War
        return 'B';
        i++;
      }
      else if (genre[i] == 'e') { //Western
        return 'C';
        i++;
      }
      else {
        printf("genre error at %s \n", genre);
        break;
      }
    }
    else {
      printf("genre error at %s \n", genre);
      break;
    }
  }
  return '0';
}
