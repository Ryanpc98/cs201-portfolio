#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utility.h"

int main(void) {
  time_t before = time(NULL);

  char *userFilename = malloc(100 * sizeof(char));
  for (int i = 0; i < 100; i++) {
    userFilename[i] = '\0';
  }

  //userFilename = userLogin();

  Movie *movieList;
  movieList = createTconstList();

  int *titleSearchArray;
  int *genreSearchArray;
  titleSearchArray = titleSearch(movieList, "subhuman");
  genreSearchArray = genreFilter(movieList, titleSearchArray, 'o');
  searchPrint(titleSearchArray, movieList);

  printf("next ten\n");

  //printNextTen(titleSearchArray, movieList, 2);

  UserMovie *userArray = malloc(100 * sizeof(UserMovie));
  for (int i = 0; i < 100; i++) {
    userArray[i].tconst = -2;
  }
  /*userArray = selectTitleToAdd(movieList, titleSearchArray, userArray);
  userArrayPrint(userArray, movieList);
  userArray = selectTitleToAdd(movieList, titleSearchArray, userArray);
  userArrayPrint(userArray, movieList);
  userArray = selectTitleToAdd(movieList, titleSearchArray, userArray);
  userArrayPrint(userArray, movieList);

  userArray = selectTitleToRemove(movieList, userArray);
  userArrayPrint(userArray, movieList);*/

  free(userArray);

  time_t diff = time(NULL) - before;
  printf("Time taken: %ld s\n", diff);

  return 0;
}
