#include "VideoGame.h"
using namespace std;

videoGame::videoGame(Text *t, Text *d, Text *p, int y)
    : title(t), developer(d), publisher(p), year(y){};

videoGame::~videoGame()
{
    delete title;
    delete developer;
    delete publisher;
    cout << "VideoGame destructor: Released memory for VideoGame object.\n";
};

void videoGame::printVideoGameDetails()
{
    cout << setw(30) << right << "Game Title: ";
    cout << setw(30) << left << title->getText();
    cout << "\n";

    cout << setw(30) << right << "Game Developer: ";
    cout << setw(30) << left << developer->getText();
    cout << "\n";

    cout << setw(30) << right << "Game Publisher: ";
    cout << setw(30) << left << publisher->getText();
    cout << "\n";

    cout << setw(30) << right << "Game Year: ";
    cout << setw(30) << left << year;
    cout << "\n";
};

void videoGame::printVideoGameDetailsToFile(ofstream &outfile)
{
    outfile << title->getText() << "\n";
    outfile << developer->getText() << "\n";
    outfile << publisher->getText() << "\n";
    outfile << year << "\n";
};

void videoGame::getVideoGameTitle() { cout << title->getText(); };