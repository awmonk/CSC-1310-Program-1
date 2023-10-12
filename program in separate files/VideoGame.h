#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include <iomanip>
#include <fstream>
#include "Text.h"
using namespace std;

class videoGame
{
public:
    videoGame(Text *title, Text *developer, Text *publisher, int year);
    ~videoGame();
    void printVideoGameDetails();
    void printVideoGameDetailsToFile(ofstream &outputFile);
    void getVideoGameTitle();

private:
    Text *title, *developer, *publisher;
    int year;
};

#endif