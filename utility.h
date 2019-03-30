
// Main movie data typede
  //Contains all available information
typedef struct _movie {
  int     tconst;
  char    *primaryTitle;
  char    *originalTitle;
  char    *lowerTitle;
  int     isAdult;
  int     startYear;
  int     runtime;
  char    *genres;      //abbreviating genres as chars
  int     height;
  struct _movie   *left;
  struct _movie   *right;
} Movie;

// Data type for storing movies a user selects
  // Contains information needed to locate identify movie
  // And information that is unique for every user
typedef struct _usermovie {
  int     tconst;
  char    *title;
  char    *lowerTitle;
  int     startYear;
  char    ownershipType;   //phyiscal, digital
  char    mAquired;
  char    dAquired;
  int     yAquired;
  int     height;
  struct _usermovie *left;
  struct _usermovie *right;
} UserMovie;


/* startup.c */
/* Contains functions that run automatically when the program is launched */
/* As well as some other utility functions used throughout */

char *getUserFilename();

void userLogin(char *userFilename);

Movie *readImdbFile();

UserMovie *readUserFile(char *filename);

char *strLower(char *dest, char *src);

Movie *movieCopy(Movie *dest, Movie *src);

void clearIn();

char *removeArticles(char *str);

/* avl.c */
/* Contains all the borrowed code */
  /* Specifically the code for managing the avl tree */

int height(Movie *N);
int heightUser(UserMovie *N);

int max(int a, int b);

Movie *rightRotate(Movie *y);
UserMovie *rightRotateUser(UserMovie *y);

Movie *leftRotate(Movie *x);
UserMovie *leftRotateUser(UserMovie *x);

int getBalance(Movie *N);
int getBalanceUser(UserMovie *N);


Movie *insert(Movie* node, Movie *newMovie);
UserMovie* insertUser(UserMovie* currMovie, UserMovie *newMovie);

UserMovie * minValueNode(UserMovie* node);

UserMovie* deleteNode(UserMovie* root, char *lowerTitle);

void preOrder(Movie *root);
void preOrderUser(UserMovie *root);


/* searches.c */
/* Contains all functions relevant to the searching and filtering of data */

void searchPrint(int *tconstArray, Movie *movieList);

void printNextTen(int *tconstArray, Movie *movieList, int start);

Movie *titleSearchAll(Movie *masterTreeNode, Movie *searchMatches, char *searchTitle);

Movie *titleSearchExact(Movie *masterTreeNode, Movie *searchMatch, char *searchTitle);

Movie *genreFilter(Movie *root, Movie *resultTree, char genre);

Movie *yearFilter(Movie *root, Movie *resultTree, int low, int high);

Movie *rtFilter(Movie *root, Movie *resultTree, int low, int high);

void printGenre(Movie *movieList, char genre);

void printYear(Movie *movieList, int lower, int higher);

void printRt(Movie *movieList, int lower, int higher);

/* user.c */
/* Contains all functions used to manage user information */

UserMovie *selectTitleToAdd(Movie *masterTreeNode);

//UserMovie *selectTitleToRemove(Movie *movieList, UserMovie *userArray);

void selectMovie();

void saveFile(FILE *fp, UserMovie *root);
