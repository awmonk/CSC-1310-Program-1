#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include <iomanip>
#include <fstream>
#include "Text.h"
using namespace std;

class videoGame {
      public:
         videoGame(Text *title, Text *developer, Text *publisher, int year);
         /* This function should be called when all video game information is
            known and it will create a new video game with this information. */
         ~videoGame();
         /* This function is automatically called when a Video game object is
            destroyed. This function releases the dynamically allocated text
            arrays in the videoGame object. */
         void printVideoGameDetails();
         /* This function should be called when the user wants to print ALL
            the videoGame information to the screen. */
         void printVideoGameDetailsToFile(ofstream &outputFile);
         /* This function should be called when the user wants to print ALL
            the videoGame information to the file. */
         void getVideoGameTitle();
         /* Returns a pointer to the Text object containing the video game title */
      private:
         /* Pointers to each attribute in the videoGame object */
         Text *title, *developer, *publisher;
         /* An integer representing the year the game was released */
         int year;
         /* Used for setting the output width */
         const int fieldWidth = 30;
};

#endif