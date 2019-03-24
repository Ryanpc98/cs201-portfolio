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

typedef struct {
  int     tconst;
  char    ownershipType;   //phyiscal, digital
  //char    dateAquired;
} UserMovie;

char *userLogin();

Movie *readFromFile();

void printMovies(Movie *movieList);

int height(Movie *N);

int max(int a, int b);

Movie *rightRotate(Movie *y);

Movie *leftRotate(Movie *x);

int getBalance(Movie *N);

Movie *insert(Movie* node, Movie *newMovie);

void preOrder(Movie *root);

void searchPrint(int *tconstArray, Movie *movieList);

void printNextTen(int *tconstArray, Movie *movieList, int start);

int *titleSearch(Movie *movieList, char *searchTitle);

int *genreFilter(Movie *movieList, int *tconstArray, char genre);

int *yearFilter(Movie *movieList, int *tconstArray, int lower, int higher);

int *rtFilter(Movie *movieList, int *tconstArray, int lower, int higher);

void printGenre(Movie *movieList, char genre);

void printYear(Movie *movieList, int lower, int higher);

void printRt(Movie *movieList, int lower, int higher);

UserMovie *selectTitleToAdd(Movie *movieList, int *tconstArray, UserMovie *userArray);

UserMovie *selectTitleToRemove(Movie *movieList, UserMovie *userArray);

void userArrayPrint(UserMovie *tconstArray, Movie *movieList);
