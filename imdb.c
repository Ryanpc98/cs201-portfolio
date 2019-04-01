#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"

int main(void) {
  char *userFilename = malloc(100 * sizeof(char));
  for (int i = 0; i < 100; i++) {
    userFilename[i] = '\0';
  }

  int loginStatus = 0;
  while (loginStatus != 1) {
    if (loginStatus == 0) {
      printf("Please enter a username: ");
    }
    else if (loginStatus == -1) {
      printf("Please enter a new username: ");
    }
    userFilename = getUserFilename();
    loginStatus = userLogin(userFilename);
  }

  Movie *masterRoot = malloc(sizeof(Movie));
  masterRoot = readImdbFile();

  UserMovie *userRoot = malloc(sizeof(UserMovie));
  userRoot = readUserFile(userFilename);

  char menuChoice = 'a';
  while (1) {
    printf("\n\n");
    printf("Please Select an Option Below:\n");
    printf("     1: Add Movie to List\n");
    printf("     2: Remove Movie from List\n");
    printf("     3: Modify Movie in List\n");
    printf("     4: Save Changes to File\n");
    printf("     5: Show Current Contents of List\n");
    printf("     6: Quit the Program\n");
    printf("     7: Save and Quit\n");
    scanf("%c", &menuChoice);
    clearIn();

    /* Add */
    if (menuChoice == '1') {
      char *searchTitle = malloc(196 * sizeof(char));
      char tempChar;
      Movie *searchMatches = malloc(sizeof(Movie));
      searchMatches = NULL;

      printf("Enter the title of a movie to search for: ");
      int i = 0;
      scanf("%c", &tempChar);
      while (tempChar != '\n') {
        searchTitle[i] = tolower(tempChar);
        i++;
        if (i >= 195) {
          clearIn();
          menuChoice = 'a';
          break;
        }
        scanf("%c", &tempChar);
      }
      searchTitle[i] = '\0';
      searchTitle = removeArticles(searchTitle);
      searchMatches = titleSearchAll(masterRoot, searchMatches, searchTitle);

      /* No Matches */
      if (searchMatches == NULL) {
        printf("\n\n");
        printf("No movies with given title found, returning to menu\n");
        menuChoice = 'a';
        continue;
      }

      /* Matche(s) Found */
      else {
        //UserMovie *movieToAdd = malloc(sizeof(UserMovie));
        UserMovie *movieToAdd;
        Movie *movieChoice = malloc(sizeof(Movie));
        movieToAdd = NULL;
        preOrder(searchMatches);

        menuChoice = 'a';
        while (menuChoice != '4') {
          printf("\n\n");
          printf("Please Select an Option Below or Press 0 to Return to Menu:\n");
          printf("     1: Filter Results by Genre\n");
          printf("     2: Filter Results by Release Year\n");
          printf("     3: Filter Results by Runtime\n");
          printf("     4: Select a Movie to Add\n");
          scanf("%c", &menuChoice);
          clearIn();
          while (menuChoice != '0' && menuChoice != '1' && menuChoice != '2' && menuChoice != '3' && menuChoice != '4') {
            printf("Error, please try again: \n");
            scanf("%c", &menuChoice);
            clearIn();
          }

          /* return */
          if (menuChoice == '0') {
            printf("\nReturning to Menu\n");
            menuChoice = 'a';
            break;
          }

          /* Filter by genre */
          if (menuChoice == '1') {
            char genreChoice;
            Movie *genreMatches = NULL;
            printf("Please Select A Genre to Filter By:\n");
            printf("a: Action\nb: Adventure\nc: Adult\nd: Animation\ne: Biography\nf: Comedy\ng: Crime\nh: Documentary\n");
            printf("i: Drama\nj: Family\nk: Fantasy\nl: Film-Noir\nm: Game-Show\nn: History\no: Horror\np: Music\nq: Musical\n");
            printf("r: Mystery\ns: News\nt: Romance\nu: Reality-TV\nv: Sci Fi\nw: Short\nx: Sport\ny: Superhero\nz: Talk-Show\n");
            printf("A: Thriller\nB: War\nC: Western\n");
            scanf("%c", &genreChoice);
            clearIn();

            genreMatches = genreFilter(searchMatches, genreMatches, genreChoice);
            searchMatches = genreMatches;
            free(genreMatches);
            printf("\n\n");
            preOrder(searchMatches);
            printf("\n\n");
            menuChoice = 'a';
          }

          /* Filter by year */
          else if (menuChoice == '2') {
            int lower = 1;
            int higher = 0;
            char tempDateChar;
            char tempLow[5];
            for (int i = 0; i < 5; i++) {
              tempLow[i] = '\0';
            }
            char tempHigh[4];
            for (int i = 0; i < 4; i++) {
              tempHigh[i] = '\0';
            }
            Movie *yearMatches = NULL;
            while(lower > higher) {
              printf("Enter a range of years to search by in the format (xxxx,yyyy)\n");
              printf("With xxxx being the lower of the two years\n");
              printf("If you want to search for a single year, enter the same year twice\n");
              for (int i = 0; i < 9; i++) {
                scanf("%c", &tempDateChar);
                if (!isdigit(tempDateChar) && i != 4) {
                  printf("Error, invalid date(s)\n\n\n");
                  clearIn();
                  menuChoice = 'a';
                  break;
                }
                if (i < 4) {
                  tempLow[i] = tempDateChar;
                }
                else if (i > 4) {
                  tempHigh[i - 5] = tempDateChar;
                }
              }
              clearIn();
              lower = atoi(tempLow);
              higher = atoi(tempHigh);
            }
            yearMatches = yearFilter(searchMatches, yearMatches, lower, higher);
            searchMatches = yearMatches;
            free(yearMatches);
            printf("\n\n");
            preOrder(searchMatches);
            printf("\n\n");
            menuChoice = 'a';
          }

          /* Filter by rt */
          else if (menuChoice == '3') {
            int lower = 1;
            int higher = 0;
            char tempRTChar;
            char tempLow[4];
            for (int i = 0; i < 4; i++) {
              tempLow[i] = '\0';
            }
            char tempHigh[4];
            for (int i = 0; i < 4; i++) {
              tempHigh[i] = '\0';
            }
            Movie *rtMatches = NULL;
            while(lower > higher) {
              printf("Enter a range of runtimes (in minutes) to search by in the format (xxx,yyy)\n");
              printf("With xxx being the lower of the two runtimes\n");
              printf("If you want to search for a single runtime, enter the same value twice\n");
              for (int i = 0; i < 7; i++) {
                scanf("%c", &tempRTChar);
                if (!isdigit(tempRTChar) && i != 3) {
                  printf("Error, invalid runtimes(s)\n\n\n");
                  clearIn();
                  menuChoice = 'a';
                  break;
                }
                if (i < 3) {
                  tempLow[i] = tempRTChar;
                }
                else if (i > 3) {
                  tempHigh[i - 4] = tempRTChar;
                }
              }
              clearIn();
              lower = atoi(tempLow);
              higher = atoi(tempHigh);
            }
            rtMatches = rtFilter(searchMatches, rtMatches, lower, higher);
            searchMatches = rtMatches;
            free(rtMatches);
            printf("\n\n");
            preOrder(searchMatches);
            printf("\n\n");
            menuChoice = 'a';
          }

          /* Add Movie */
          else if (menuChoice == '4') {
            //movieToAdd = selectTitleToAdd(searchMatches);
            int key = MorrisTraversal(searchMatches);
            if (key == -1) {
              printf("\nReturning to Menu\n");
              menuChoice = 'a';
              continue;
            }
            else if (key == -2) {
              key = MorrisTraversal(searchMatches);
            }
            else if (key >= 0) {
              movieChoice = MorrisTraversalFind(searchMatches, key);
              movieToAdd = selectTitleToAdd(movieToAdd, movieChoice);

              UserMovie *existingMatch = malloc(sizeof(UserMovie));
              existingMatch = NULL;
              existingMatch = titleSearchExactUser(userRoot, existingMatch, movieToAdd->lowerTitle);

              /* check if movie exists already */
              /* Note, movie must match in title, date purchased and ownership type */
              if (existingMatch == NULL) {
                free(existingMatch);
                userRoot = insertUser(userRoot, movieToAdd);
              }
              else {
                free(existingMatch);
                printf("\n\nError, duplicate entry in user list\n");
                printf("Returning to menu\n\n");
                menuChoice = 'a';
                continue;
              }
            }
          }
        }
      }
      menuChoice = 'a';
      printf("\n\n");
    }

    /* Remove */
    if (menuChoice == '2') {
      UserMovie *movieToRemove = malloc(sizeof(UserMovie));
      movieToRemove = NULL;
      preOrderUser(userRoot);
      printf("\n\n");
      int key = MorrisTraversalUser(userRoot);
      if (key == -1) {
        printf("\nReturning to Menu\n");
        menuChoice = 'a';
        continue;
      }
      else if (key == -2) {
        key = MorrisTraversalUser(userRoot);
      }
      else if (key >= 0) {
        movieToRemove = MorrisTraversalFindUser(userRoot, key);
      }

      /* No Matches */
      if (movieToRemove == NULL) {
        printf("No movie with given title found, returning to menu\n");
        menuChoice = 'a';
        continue;
      }

      userRoot = deleteNode(userRoot, movieToRemove->lowerTitle);
      printf("\n\n");
    }

    /* Modify */
    if (menuChoice == '3') {
      UserMovie *movieToModify = malloc(sizeof(UserMovie));
      movieToModify = NULL;
      preOrderUser(userRoot);
      printf("\n\n");
      int key = MorrisTraversalUser(userRoot);
      if (key == -1) {
        printf("\nReturning to Menu\n");
        menuChoice = 'a';
        continue;
      }
      else if (key == -2) {
        key = MorrisTraversalUser(userRoot);
      }
      else if (key >= 0) {
        movieToModify = MorrisTraversalFindUser(userRoot, key);
      }

      /* No Matches */
      if (movieToModify == NULL) {
        printf("No movie with given title found, returning to menu\n");
        menuChoice = 'a';
        continue;
      }

      /* Menu to select attribute to modify */
      printf("%s\n", movieToModify->lowerTitle);
      printf("Select and Attribute to Modify or Press 0 to Quit: \n");
      printf("     1: Ownership Type\n");
      printf("     2: Date Purchased\n");
      scanf("%c", &menuChoice);
      clearIn();
      while (menuChoice != '0' && menuChoice != '1' && menuChoice != '2') {
        printf("Error, please try again: \n");
        scanf("%c", &menuChoice);
        clearIn();
      }

      /* Quit */
      if (menuChoice == '0') {
        printf("Returning to Menu\n");
        menuChoice = 'a';
        continue;
      }

      /* Modify Ownership type */
      else if (menuChoice == '1') {
        char tempOwn;
        printf("Please enter a new ownership type: \n");
        printf("(p for phyiscal or d for digital)\n");
        scanf("%c", &tempOwn);
        clearIn();
        while (tempOwn != 'p' && tempOwn != 'd') {
          printf("Error, please try again: \n");
          printf("(p for phyiscal or d for digital)\n");
          scanf("%c", &tempOwn);
          clearIn();
        }
        movieToModify->ownershipType = tempOwn;
      }

      /* Modify Date */
      else if (menuChoice == '2') {
        char tempDate[10];
        for (int i = 0; i < 10; i++) {
          tempDate[i] = '\0';
        }
        char tempChar;
        printf("Please enter a new date: \n");
        printf("(Please enter in mm/dd/yyyy format)\n");
        for (int i = 0; i < 10; i++) {
          scanf("%c", &tempChar);
          tempDate[i] = tempChar;
        }
        printf("%s\n", tempDate);
        if (isdigit(tempDate[0]) && isdigit(tempDate[1])) {
          movieToModify->mAquired = (10 *(tempDate[0] - '0')) + (tempDate[1] - '0');
          if (isdigit(tempDate[3]) && isdigit(tempDate[4])) {
            movieToModify->dAquired = (10 * (tempDate[3] - '0')) + (tempDate[4] - '0');
            if (isdigit(tempDate[6]) && isdigit(tempDate[7]) && isdigit(tempDate[8]) && isdigit(tempDate[9])) {
              movieToModify->yAquired = (1000 * (tempDate[6] - '0')) + (100 * (tempDate[7] - '0'))
                    + (10 * (tempDate[8] - '0')) + (tempDate[9] - '0');
              clearIn();
              menuChoice = 'a';
              continue;
            }
          }
        }
        while(1) {
          printf("Invalid date, please try again\n");
          printf("When did you purchase this movie?: \n");
          printf("(Please enter in mm/dd/yyyy format)\n");
          for (int i = 0; i < 10; i++) {
            scanf("%c", &tempChar);
            tempDate[i] = tempChar;
          }
          if (isdigit(tempDate[0]) && isdigit(tempDate[1])) {
            movieToModify->mAquired = (10 *(tempDate[0] - '0')) + (tempDate[1] - '0');
            if (isdigit(tempDate[3]) && isdigit(tempDate[4])) {
              movieToModify->dAquired = (10 * (tempDate[3] - '0')) + (tempDate[4] - '0');
              if (isdigit(tempDate[6]) && isdigit(tempDate[7]) && isdigit(tempDate[8]) && isdigit(tempDate[9])) {
                movieToModify->yAquired = (1000 * (tempDate[6] - '0')) + (100 * (tempDate[7] - '0'))
                      + (10 * (tempDate[8] - '0')) + (tempDate[9] - '0');
                clearIn();
                menuChoice = 'a';
                continue;
              }
            }
          }
        }
      }
      printf("\n\n");
    }

    /* Save Changes */
    if (menuChoice == '4') {
      FILE *fpS;
      fpS = fopen(userFilename, "w");
      saveFile(fpS, userRoot);
      fclose(fpS);

      printf("\n\nFile Saved Successfully\n");
      menuChoice = 'a';
    }

    /* Print List */
    if (menuChoice == '5') {
      printf("\n\n");
      preOrderUser(userRoot);
      printf("\n\n");
      menuChoice = 'a';
    }

    /* Quit w/out Saving */
    if (menuChoice == '6') {
      printf("Are you sure you want to quit?: (y/n) ");
      scanf("%c", &menuChoice);
      clearIn();
      while (menuChoice != 'y' && menuChoice != 'n') {
        printf("Please enter y for yes or n for no: ");
        scanf("%c", &menuChoice);
        clearIn();
      }
      if (menuChoice == 'n') {
        menuChoice = 'a';
        continue;
      }
      else if (menuChoice == 'y') {
        free(userFilename);
        deleteTree(masterRoot);
        deleteTreeUser(userRoot);

        return 0;
      }
    }

    /* Save and Quit */
    if (menuChoice == '7') {
      printf("Are you sure you want to quit?: (y/n) ");
      scanf("%c", &menuChoice);
      clearIn();
      while (menuChoice != 'y' && menuChoice != 'n') {
        printf("Please enter y for yes or n for no: ");
        scanf("%c", &menuChoice);
        clearIn();
      }
      if (menuChoice == 'n') {
        menuChoice = 'a';
        continue;
      }
      else if (menuChoice == 'y') {
        FILE *fp7;
        fp7 = fopen(userFilename, "w");
        saveFile(fp7, userRoot);
        fclose(fp7);

        printf("\n\nFile Saved Successfully\n");

        free(userFilename);
        deleteTree(masterRoot);
        deleteTreeUser(userRoot);

        return 0;
      }
    }

    /* print lower titles */
    if (menuChoice == '$') {
      printf("\n\n");
      preOrderUserLower(userRoot);
      printf("\n\n");
      menuChoice = 'a';
    }
  }

  return 0;
}
