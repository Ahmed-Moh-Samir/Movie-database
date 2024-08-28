#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

#define MAX 100

typedef struct movie {
    string title;
    unsigned short year;
    unsigned short rating;
};

typedef struct movieDatabase {
    movie movies[MAX];
    unsigned int count = 0;
};

int menu();
string printMovie(movie m);
void showMovies(movieDatabase& db);
void addMovie(movieDatabase& db, string title, unsigned short year, unsigned short rating);
void loadDatabase(movieDatabase& db);
unsigned int findMovie(movieDatabase& db, string key);
unsigned int findMovieMaxRating(movieDatabase& db);
void updateMovie(movieDatabase& db, string key, string title, unsigned short year, unsigned short rating);
void findMoviesByYear(movieDatabase& db, unsigned short year);
void deleteMovie(movieDatabase& db, string key);
void sortMovies(movieDatabase& db);
int compare(const void* a, const void* b);


bool validateInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}


int main()
{
    movieDatabase db;

    string key;
    string title;
    unsigned short year;
    unsigned short rating;


    //addMovie(db,"snow white",2004,13);

    int choice = -1;
    while ((choice = menu()) != 10)
    {
        switch (choice)
        {
        case 1:
            showMovies(db);
            break;

        case 2:
            cout << "Enter movie title to search: ";
            cin.ignore();  // Clear the newline character from the previous input
            getline(cin, key);
            if (validateInput()) {
                int pos = findMovie(db, key);
                if (pos != -1)
                {
                    cout << "Position of " << key << " is " << pos << endl;
                }
                else
                {
                    cout << "Movie not found." << endl;
                }
            }
            else
            {
                cout << "Invalid input. Please enter a valid movie title." << endl;
                cout << endl;
            }
            break;

        case 3:
            cout << "Enter new movie data {title year rating}: ";
            cin >> title >> year >> rating;
            if (validateInput()) {
                addMovie(db, title, year, rating);
            }
            else {
                cout << "Invalid input. Please enter a valid title, year, and rating." << endl;
            }
            break;

        case 4:
            cout << "Enter movie to delete: ";
            cin >> key;
            if (validateInput()) {
                deleteMovie(db, key);
            }
            else {
                cout << "Invalid input. Please enter a valid movie title." << endl;
            }
            break;

        case 5:
            cout << "Enter movie to update: ";
            cin >> key;
            cout << "Enter new movie data {title year rating}: ";
            cin >> title >> year >> rating;
            if (validateInput()) {
                updateMovie(db, key, title, year, rating);
            }
            else {
                cout << "Invalid input. Please enter a valid title, year, and rating." << endl;
            }
            break;

        case 6:
            cout << printMovie(db.movies[findMovieMaxRating(db)]) << endl;
            break;

        case 7:
            cout << "Enter year to search: ";
            cin >> year;
            if (validateInput()) {
                findMoviesByYear(db, year);
            }
            else {
                cout << "Invalid input. Please enter a valid year." << endl;
            }
            break;

        case 8:
            sortMovies(db);
            break;

        case 9:
            loadDatabase(db);
            break;

        default:
            cout << "\n\n!!!Invalid Choice!!!\n\n" << endl;
        }
    }
}

int menu() {
    cout << "+------------------------+" << endl;
    cout << "|        Main Menu       |" << endl;
    cout << "+------------------------+" << endl;
    cout << endl << endl;

    cout << "1. Show List of Movies" << endl;
    cout << "2. Search for a Movie" << endl;
    cout << "3. Add a Movie" << endl;
    cout << "4. Delete a Movie" << endl;
    cout << "5. Update a Movie" << endl;
    cout << "6. Find movie with max rating" << endl;
    cout << "7. Find movies of year" << endl;
    cout << "8. Sort movies by rating" << endl;
    cout << "9. Load Movies from File" << endl;
    cout << "10. Exit" << endl << endl;

    cout << "Enter choice: ";

    int choice = -1;
    while (true) {
        if (cin >> choice) {
            break;  // Valid integer input, exit the loop.
        }
        else {
            cin.clear();  // Clear the failure state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard the invalid input.
            cout << "Invalid input. Please enter a valid choice: ";
        }
    }

    return choice;
}

string printMovie(movie m) {
    return m.title + '\t' + std::to_string(m.year) + "\t" + std::to_string(m.rating) + "\n";
}


void showMovies(movieDatabase& db) {
    //check if the database is empty
    if(db.movies == 0)
    {
        cout << "database is empty '\n";    //if it is, print an empty message

    }
    else
    {
        for(int i{0}; i < db.count; i++)
        {
            cout << printMovie(db.movies[i]);
        }
    }                                       
    //if not, print all the movies {Title tab Year tab Rating), one in every line

}

void addMovie(movieDatabase& db, string title, unsigned short year, unsigned short rating) {
    //check if the database is full
    if(db.count < MAX)              //if it is not, add the movie
    {
        db.movies[db.count].title = title;
        db.movies[db.count].year = year;
        db.movies[db.count].rating = rating;
    }
    else                    //else print that the Database is full
    { 
        cout << "DataBase is full \n";
    }
    
    db.count++;
    

    

}

void loadDatabase(movieDatabase& db) {
    ifstream file("movies.csv");

    if(!file.is_open())
    {
        cout << "Failed to open file";
    }
    
    string header;
    string title;
    string yearStr, ratingStr;
    unsigned short year, rating;
    //declare appropriate short variables to convert year and rating strings
    db.count =0;
    //reset the database counter
    getline(file, header);
    //read and skip the first line

    
        //read the title until the first comma
    while (getline(file, title, ','))
    {
        getline(file,yearStr, ',');
        getline(file, ratingStr);
    
    
    year =  static_cast<unsigned short>(stoi(yearStr));
    rating = static_cast<unsigned short>(stoi(ratingStr));

    //convert year and rating

    addMovie(db, title, year, rating);
    }


    file.close();

    cout << endl << "File loaded succesfully" << endl;
}

unsigned int findMovie(movieDatabase& db, string key) {
    //search for a movie with a title equal to the key
    for (unsigned int i{0}; i < db.count; i++)
    {
        if(db.movies[i].title == key)
        {
             return i;
        }
    }
    return -1;
}

unsigned int findMovieMaxRating(movieDatabase& db) {
    unsigned short maxRatingIndex = 0;
    for (int i = 1; i < db.count; i++)          //loops through movies
        if (db.movies[i].rating > db.movies[maxRatingIndex].rating) // if a movie with high rating is found update maxratingindex.
            maxRatingIndex = i;
    return maxRatingIndex;
}

void findMoviesByYear(movieDatabase& db, unsigned short year) 
{
    for (unsigned short i {0}; i < db.count; i++)
    {
        if (db.movies[i].year == year)
        {
            cout << printMovie(db.movies[i]);
        }
    }
}

void updateMovie(movieDatabase& db, string key, string newTitle, unsigned short newYear, unsigned short newRating) {
    //search for a movie with a title equ
    unsigned int pos = findMovie(db,key);
    if(pos != -1)
    {
        db.movies[pos].title = newTitle;
        db.movies[pos].year = newYear;
        db.movies[pos].rating = newRating;
    }
    else
     {
        cout << "Movie was not found \n" << key;
     }
    //if one is found, update its title, year and rating with the new data   

    //otherwise, print that the selected movie was not found


}

void deleteMovie(movieDatabase& db, string key) {

    int pos = findMovie(db, key);
    //find the position of the element you are trying to delete using findMovie
    if(pos == -1)
    {
        cout << "Movie was not found \n";
    }
    //check if the position is found
    else
    {
        db.movies[pos] = db.movies[db.count - 1];
        db.count --;
    }
    //if it is not found then print that the specific movie is not found (include the name of the movie)

    //if it is found then delete the movie from the database
    //it is important that the movie slot does not remain empty

}

int compare(const void* a, const void* b)
{
    //implement compare as it is required by quicksort
    return 0;
}

void sortMovies(movieDatabase& db) {
    //use quicksort (qsort) to sort the movie database

}