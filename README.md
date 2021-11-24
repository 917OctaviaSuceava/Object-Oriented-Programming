# Object-Oriented-Programming

-------- ASSIGNMENT 1 

Local Movie Database

So many movies, so little time. To make sure you do not miss any good movies, you absolutely need a software application to help you manage your films and create watch lists. 
The application can be used in two modes: administrator and user. When the application is started, it will offer the option to choose the mode.

Administrator mode: The application will have a database which holds all the movies. You must be able to update the database, meaning: 
add a new movie, delete a movie and update the information of a movie. Each Movie has a title, a genre, a year of release, a number of likes and a trailer.
The trailer is memorised as a link towards an online resource. The administrators will also have the option to see all the movies in the database.

User mode: A user can create a watch list with the movies that she wants to watch. The application will allow the user to:

- See the movies in the database having a given genre (if the genre is empty, see all the movies), one by one. When the user chooses this option, the data of the first movie (title, genre, year of release, number of likes) is displayed and the trailer is played in the browser.
- If the user likes the trailer, she can choose to add the movie to her watch list.
- If the trailer is not satisfactory, the user can choose not to add the movie to the watch list and to continue to the next. In this case, the information corresponding to the next movie is shown and the user is again offered the possibility to add it to the watch list. This can continue as long as the user wants, as when arriving to the end of the list of movies with the given genre, if the user chooses next, the application will again show the first movie.
- Delete a movie from the watch list, after the user watched the movie. When deleting a movie from the watch list, the user can also rate the movie (with a like), and in this case, the number of likes the movie has in the repository will be increased.
- See the watch list.

-------- ASSIGNMENT 2 

- Replace the templated DynamicVector with the STL vector. Use STL algorithms wherever possible in your application (e.g. in your filter function you could use copy_if, count_if). Replace all your for loops either with STL algorithms, or with C++11's ranged-based for loop.

- Store data in a text file. When the program starts, entities are read from the file. Modifications made during program execution are stored in the file. Implement this using the iostream library. Create insertion and extraction operators for your entities and use these when reading/writing to files or the console.

- Use exceptions to signal errors:
  > from the repository;
  > validation errors – validate your entities using Validator classes;
  > create your own exception classes.
  > validate program input.
  > store your movie watch list in a file. When the application starts, the user should choose the type of file between CSV or HTML. Depending on the type, the application will save the list in the correct format.

- Add a new command, allowing the user to see the movie watch list
- Create a UML class diagram for your entire application. For this, you can use any tool that you like.
