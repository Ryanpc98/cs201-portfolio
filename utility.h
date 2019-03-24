
// Main movie data typede
  //Contains all available information
typedef struct _movie {
  int     tconst;
  char    primaryTitle[300];
  char    originalTitle[300];
  int     isAdult;
  int     startYear;
  int     runtime;
  char    genres[10];      //abbreviating genres as chars
  int     height;
  struct _movie   *left;
  struct _movie   *right;
} Movie;

// Data type for storing movies a user selects
  // Contains information needed to locate identify movie
  // And information that is unique for every user
typedef struct {
  char    title[300];
  char    ownershipType;   //phyiscal, digital
  //char    dateAquired;
} UserMovie;


/* startup.c */
/* Contains functions that run automatically when the program is launched */

char *userLogin();

Movie *readFromFile();

/* avl.c */
/* Contains all the borrowed code */
  /* Specifically the code for managing the avl tree */

int height(Movie *N);

int max(int a, int b);

Movie *rightRotate(Movie *y);

Movie *leftRotate(Movie *x);

int getBalance(Movie *N);

Movie *insert(Movie* node, Movie *newMovie);

void preOrder(Movie *root);

/* searches.c */
/* Contains all functions relevant to the searching and filtering of data */

void searchPrint(int *tconstArray, Movie *movieList);

void printNextTen(int *tconstArray, Movie *movieList, int start);

int *titleSearch(Movie *movieList, char *searchTitle);

int *genreFilter(Movie *movieList, int *tconstArray, char genre);

int *yearFilter(Movie *movieList, int *tconstArray, int lower, int higher);

int *rtFilter(Movie *movieList, int *tconstArray, int lower, int higher);

void printGenre(Movie *movieList, char genre);

void printYear(Movie *movieList, int lower, int higher);

void printRt(Movie *movieList, int lower, int higher);

/* user.c */
/* Contains all functions used to manage user information */

UserMovie *selectTitleToAdd(Movie *movieList, int *tconstArray, UserMovie *userArray);

UserMovie *selectTitleToRemove(Movie *movieList, UserMovie *userArray);

void userArrayPrint(UserMovie *tconstArray, Movie *movieList);
