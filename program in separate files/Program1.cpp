/*
    Title:          Program1.cpp
    Author:         Austin Monk
    Date:           09/18/2023
    Section:        CSC 1310-001
*/

/* The driver need only call the VideoGameLibrary header as all other libraries
   are nested within it. */
#include "VideoGameLibrary.h"
using namespace std;

/* Function to encapsulate the menu. */
void showMenu();

int main() {
    /* Initialize an integer for the maximum number of games, a userChoice
       variable and a boolean for the switch, and an array of chars for
       the fstream to be called. */
    int maxGames, userChoice = -1;
    bool quit = false;
    char filename[100];

    cout << "How many video games can your library hold? ";
    cin  >> maxGames;

    /* Intitialize the library object after the maxGames variable is set to
       avoid undefined behavior. */
    videoGameLibrary library(maxGames);

    while(!quit) {
        cout << endl;
        showMenu();
        cin  >> userChoice;
        switch(userChoice) {
            case 1:
                /* Load video games from a file. */
                cout << "\nWhat is the name of the file? (example.txt): ";
                cin.ignore();
                cin.getline(filename, sizeof(filename));
                cout << endl;
                library.loadVideoGamesFromFile(filename);
                break;
            case 2:
                /* Save video games from a file. */
                library.saveToFile(filename);
                break;
            case 3:
                /* Add a video game. */
                library.addVideoGameToArray();
                break;
            case 4:
                /* Remove a video game. */
                library.removeVideoGameFromArray();
                break;
            case 5:
                /* Display all video games. */
                library.displayVideoGames();
                break;
            case 6:
                /* Remove all video games and quit. */
                library.~videoGameLibrary();
                quit = true;
                break;
            default:
                /* User input error. */
                cout << "That is not a valid choice.\n" << endl;
                break;
        }
    }
    cout << "\nGOODBYE!\n" << endl;
    return 0;
};

void showMenu() {
    cout << "What would you like to do?\n";
    cout << "\t1. Load video games from a file\n";
    cout << "\t2. Save video games to a file\n";
    cout << "\t3. Add a video game\n";
    cout << "\t4. Remove a video game\n";
    cout << "\t5. Display all video games\n";
    cout << "\t6. Remove ALL video games from ";
    cout << "this library and END PROGRAM\n";
    cout << "CHOOSE 1-6: ";
};