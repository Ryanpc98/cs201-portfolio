typedef struct {
  int     tconst;
  //char    titleType;     //abbreviating title types as chars
  char  primaryTitle[300];
  char  originalTitle[300];
  int    isAdult;
  int     startYear;
  //int     endYear;
  int     runtime;
  char  genres[10];      //abbreviating genres as chars
  //char  *directors;
  //char  *writers;
} Movie;

typedef struct {
  int tconst;
  //char viewStatus;    //wishlist, viewed
  char ownershipType;   //phyiscal, digital
} UserMovie;

char *userLogin();

Movie *readFromFile();

void printMovies(Movie *movieList);

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
