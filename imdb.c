#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utility.h"

int main(void) {

  //char *userFilename = malloc(100 * sizeof(char));
  //for (int i = 0; i < 100; i++) {
  //  userFilename[i] = '\0';
  //}

  //userFilename = getUserFilename();
  //userLogin(userFilename);

  time_t before = time(NULL); /* start time */

  Movie *masterRoot = malloc(sizeof(Movie));
  masterRoot = readImdbFile();

  UserMovie *userRoot = malloc(sizeof(UserMovie));
  userRoot = readUserFile("sample.log");
  preOrderUser(userRoot);
  printf("\n\n\n");

  UserMovie *asdf = selectTitleToAdd(masterRoot);
  userRoot = insertUser(userRoot, asdf);
  preOrderUser(userRoot);

  time_t diff = time(NULL) - before;
  printf("\nTime taken: %ld s\n", diff); /* end time */

  //free(userFilename);

  return 0;
}
