# cs201-portfolio     version 1.0    03/31/2019
****************************************************************************
## CONTACT INFO:
  Ryan Carrigan
  rpcarrigan@crimson.ua.edu
  Ryanpc98 on GitHub

****************************************************************************
## GETTING STARTED:

  Go to: [HERE](https://datasets.imdbws.com/)
  and download the title.basics.tsv.gz file

  One the file is downloaded, ensure that the title.basics.tsv file is in
  the same directory as your program

  After this, open up your terminal window and type "make" and hit enter

  Once all this is done, you're all set to run the program by hitting
  "./imdb"
****************************************************************************
## BASIC TIPS:

### When presented with a screen like this:

  *0: Indiana Jones and the Temple of Doom(1984)
       Owned digitally
       Aquired: 07/01/7722
  *1: Avengers: Age of Ultron(2015)
       Owned digitally
       Aquired: 12/12/1234
       .
       .
       .
  *8: RoboCop 4(1994)
       Owned digitally
       Aquired: 04/20/1969
  *9: Star Trek World Tour(1998)
       Owned digitally
       Aquired: 12/12/3456

    Enter the number or a movie to select it, press 'n' to print next 10, or press 'q' to quit:*

  Make sure that you don't pass up the movie you want or you'll have to go all the way back around.


### Be sure to take advantage of these options:

  *1: Filter Results by Genre
   2: Filter Results by Release Year
   3: Filter Results by Runtime*

   They can save you a lot of trouble by narrowing down the pages of movies you have to sift through.


### Be sure to read output messages carefully:

   *Are you looking for an existing list? (y/n):*

   *(Please enter in mm/dd/yyyy format)*

   *Enter a range of years to search by in the format (xxxx,yyyy)
   With xxxx being the lower of the two years
   If you want to search for a single year, enter the same year twice*

   Many contain important questions or formatting guidelines and ignoring what they say can either cause unexpected behavior or cause you to have to re-input information.

### Duplicates are allowed in the user list to an extent:

   *Error, duplicate entry in user list
   Returning to menu*

   You can have the same movie in the user list as many times as you want, but they just cannot match exactly.
    i.e. They cannot have the same ownershipType and dateAquired
****************************************************************************
## BORROWED CODE
  * [AVL TREE](https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
    * Used to create basic data structure used for storing movies
    * Many of the methods are duplicated for both Movie and UserMovie types
  * [DELETE](https://www.geeksforgeeks.org/avl-tree-set-2-deletion/)
    * Added ability to delete from the data structure
  * [MORRIS TRAVERSAL](https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/)
    * Needed this traversal to be able to print out a number infront of the movies for users to user to select a movie
    * Created two different versions of the traversal
      * First one just printed the numbers infront of the movies and allowed users to enter a corresponding number
      * Second one took that number and iterated through the tree to find which movie the user was referencing
****************************************************************************
## TUTORIAL:

  YouTube [link](https://youtu.be/yh3VjFnj5-Y)
****************************************************************************
### SECRET TIP:
  ```
  Pressing '$' on the main menu outputs all the user movies with their lowerTitle instead of primaryTitle
  I'm not sure why anyone would want to use that except for debugging, but now you know
  ```
