#ifndef VIDEOGAMELIBRARY_H
#define VIDEOGAMELIBRARY_H

#include "VideoGame.h"
using namespace std;

class videoGameLibrary
{
public:
    videoGameLibrary(int maxGames);
    /* This function is automatically called when a videoGameLibrary object
       is created and creates a library of videoGames. */
    ~videoGameLibrary();
    /* This function is automatically called when the videoGameLibrary object is
       destroyed. This releases the dynamically created individual video games
       and then deletes the array. */
    void addVideoGameToArray();
    /* This function should be called when you need to add a single video game
       to the videoGameLibrary */
    void displayVideoGames();
    /* This function should be called when the user wants to have all the
       videoGames in the library printed to the screen. */
    void displayVideoGameTitles();
    /* This function should be called when you want to print only the videoGame
       titles out of the videoGameLibrary */
    void loadVideoGamesFromFile(const char *filename);
    /* This function should be called when the user wants to read video game data
       from a file and add the video games to the video game library. The file
       must have data in the following order: title, developer, publisher, year. */
    void removeVideoGameFromArray();
    /* This function should be called when the user wants to remove one single
       videoGame from the videoGameLibrary. The videoGame to be removed must be
       identified by the user and then removed. */
    void saveToFile(const char *filename);
    /* This function should be called when the user wants to print all the
       videoGame data from the videoGameLibrary to a file. The data is printed
       in the following order (one piece of data per line): title, developer,
       publisher, and year. */
    void resizeVideoGameArray();
    /* This function is called by addVideoGameToArray when the array size is not
       big enough to hold a new video game that needs to be added. The function
       makes the array twice as big as it currently is and then moves all the
       videoGame pointers to this new array. */
private:
    /* A pointer to an array of pointers. Each pointer in the array should
       be able to point to (hold the memory address of) an individual
       videoGame object. */
    videoGame **videoGameArray;
    /* The maximum numer of games in the library and the current number of
       games in the library */
    int maxGames, numGames;
};

#endif