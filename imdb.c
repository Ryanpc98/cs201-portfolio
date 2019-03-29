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

  //userFilename = userLogin();

  time_t before = time(NULL); /* start time */

  Movie *masterRoot = malloc(sizeof(Movie));
  masterRoot = readFromFile();
  //preOrder(masterRoot);

  //UserMovie *userRoot;

  Movie *searchRoot = malloc(sizeof(Movie));
  searchRoot = NULL;
  //searchRoot = titleSearch(masterRoot, searchRoot, "stardust");
  //preOrder(searchRoot);
  //searchRoot = NULL;
  searchRoot = titleSearch(masterRoot, searchRoot, "dragon's realm");
  preOrder(searchRoot);


  //FILE *fp;
  //fp = fopen(userFilename, "w");
  //saveFile(fp, userRoot);
  //fclose(fp);

  time_t diff = time(NULL) - before;
  printf("\n\nTime taken: %ld s\n", diff); /* end time */

  return 0;
}
