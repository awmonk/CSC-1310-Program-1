/*
    Title:          Program1.cpp
    Author:         Austin Monk
    Date:           09/18/2023
    Section:        CSC 1310-001
*/

#include "VideoGameLibrary.h"
using namespace std;

void showMenu();

int main()
{
    int maxGames, userChoice = -1;
    bool quit = false;
    char filename[100];

    cout << "How many video games can your library hold? ";
    cin >> maxGames;

    videoGameLibrary *library = new videoGameLibrary(maxGames);

    while (!quit)
    {
        cout << "\n";
        showMenu();
        cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            cout << "\nWhat is the name of the file? (example.txt): ";
            cin.ignore();

            cin.getline(filename, sizeof(filename));
            cout << endl;

            library->loadVideoGamesFromFile(filename);
            break;
        case 2:
            library->saveToFile(filename);
            break;
        case 3:
            library->addVideoGameToArray();
            break;
        case 4:
            library->removeVideoGameFromArray();
            break;
        case 5:
            library->displayVideoGames();
            break;
        case 6:
            cout << "\n";
            quit = true;
            break;
        default:
            cout << "That is not a valid choice.\n\n";
            break;
        }
    }

    delete library;
    return 0;
};

void showMenu()
{
    cout << "What would you like to do?\n\n";
    cout << "\t1. Load video games from a file\n";
    cout << "\t2. Save video games to a file\n";
    cout << "\t3. Add a video game\n";
    cout << "\t4. Remove a video game\n";
    cout << "\t5. Display all video games\n";
    cout << "\t6. Remove ALL video games from ";
    cout << "this library and END PROGRAM\n\n";
    cout << "CHOOSE 1-6: ";
};