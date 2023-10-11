#include "VideoGame.h"
using namespace std;

videoGame::videoGame(Text *title, Text *developer, Text *publisher, int year)
{
    /* Initializes all attributes to the arguments sent to this function. */
    this->title = title;
    this->developer = developer;
    this->publisher = publisher;
    this->year = year;
};

videoGame::~videoGame()
{
    /* Releases the dynamically allocated space for the videoGame title,
       developer, and publisher and then prints a message */
    delete title;
    delete developer;
    delete publisher;
    cout << "VideoGame destructor: Released memory for VideoGame object.\n";
};

void videoGame::printVideoGameDetails()
{
    /* Prints the title, developer, publisher, & year. In order to print the
       Text objects the displayText function is called. Uses the setw
       function defined in <iomanip> to produce the desired output */
    cout << setw(30) << right << "Game Title: ";
    cout << setw(30) << left << title->getText();
    cout << endl;

    cout << setw(30) << right << "Game Developer: ";
    cout << setw(30) << left << developer->getText();
    cout << endl;

    cout << setw(30) << right << "Game Publisher: ";
    cout << setw(30) << left << publisher->getText();
    cout << endl;

    cout << setw(30) << right << "Game Year: ";
    cout << setw(30) << left << year;
    cout << endl;
    cout << endl;
};

void videoGame::printVideoGameDetailsToFile(ofstream &outputFile)
{
    /* Print the title, developer, publisher, & year to the file stream object
       that was sent to this function. In order to print the Text objects to
       the file, you must first retrieve the c-string attribute (calling the
       getText function) from this Text, and then you can print it to the
       file. */
    outputFile << title->getText() << endl;
    outputFile << developer->getText() << endl;
    outputFile << publisher->getText() << endl;
    outputFile << year << endl;
};

void videoGame::getVideoGameTitle() { cout << title->getText(); };