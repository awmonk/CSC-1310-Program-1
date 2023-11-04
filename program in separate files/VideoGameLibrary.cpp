#include "Text.h"
#include "VideoGameLibrary.h"
using namespace std;

videoGameLibrary::videoGameLibrary(int maxGames) : maxGames(maxGames), numGames(0)
{
    videoGameArray = new videoGame *[maxGames];
};

videoGameLibrary::~videoGameLibrary()
{
    for (int i = 0; i < numGames; i++)
        delete videoGameArray[i];

    delete[] videoGameArray;

    cout << "VideoGameLibrary destructor: Released memory for ";
    cout << "each game in the video game array and the array itself.";
    cout << "\n\nGOODBYE!\n\n";
};

void videoGameLibrary::addVideoGameToArray()
{
    if (numGames < maxGames)
    {
        char title[100], developer[100], publisher[100];
        int year;

        cout << endl;
        cin.ignore();

        cout << "Enter VIDEO GAME Title: ";
        cin.getline(title, sizeof(title));

        cout << "Enter VIDEO GAME Developer: ";
        cin.getline(developer, sizeof(developer));

        cout << "Enter VIDEO GAME Publisher: ";
        cin.getline(publisher, sizeof(publisher));

        cout << "Enter VIDEO GAME Year: ";
        cin >> year;
        cin.ignore();

        Text *titleText = new Text(title);
        Text *developerText = new Text(developer);
        Text *publisherText = new Text(publisher);

        videoGameArray[numGames] =
            new videoGame(titleText, developerText, publisherText, year);

        numGames++;
    }
    else
        resizeVideoGameArray();
};

void videoGameLibrary::displayVideoGames()
{
    for (int i = 0; i < numGames; i++)
    {
        cout << "\n";
        cout << setw(50) << right;
        cout << "-------- Video Game " << i + 1 << " --------\n";
        videoGameArray[i]->printVideoGameDetails();
    }
};

void videoGameLibrary::displayVideoGameTitles()
{
    for (int i = 0; i < numGames; i++)
    {
        cout << endl;
        cout << i + 1 << ": ";
        videoGameArray[i]->getVideoGameTitle();
    }
};

void videoGameLibrary::loadVideoGamesFromFile(const char *filename)
{
    char title[10000], developer[10000], publisher[10000];
    int year;

    ifstream infile(filename);

    if (!infile)
    {
        cout << "Sorry, I was unable to open the file.\n";
        return;
    }

    while (infile.getline(title, sizeof(title)))
    {
        infile.getline(developer, sizeof(developer));
        infile.getline(publisher, sizeof(publisher));
        infile >> year;
        infile.ignore();

        Text *titleText = new Text(title);
        Text *developerText = new Text(developer);
        Text *publisherText = new Text(publisher);

        if (numGames == maxGames)
            resizeVideoGameArray();

        videoGameArray[numGames] =
            new videoGame(titleText, developerText, publisherText, year);

        numGames++;

        cout << title << " was added successfully.\n";
    }
    infile.close();

    cout << endl;
    cout << numGames << " video games were read from the file and ";
    cout << "added to your VideoGame library\n";

    return;
};

void videoGameLibrary::removeVideoGameFromArray()
{
    int userChoice;

    if (numGames >= 1)
    {
        cout << "\nChoose from the following video games to remove:";
        displayVideoGameTitles();
        cout << endl;

        cout << "\nChoose a video game between 1 & " << numGames << ": ";
        cin >> userChoice;
        cout << endl;

        if (userChoice >= 1 && userChoice <= numGames)
        {
            cout << "\nThe video game ";
            videoGameArray[userChoice - 1]->getVideoGameTitle();
            cout << " has been successfully deleted.\n\n";

            delete videoGameArray[userChoice - 1];

            for (int i = userChoice - 1; i < numGames - 1; i++)
                videoGameArray[i] = videoGameArray[i + 1];

            numGames--;
        }
        else
            cout << "That is not a valid choice.\n";
    }
    else
    {
        cout << "There must be at least one game in the library ";
        cout << "to remove a game.\n";
    }
};

void videoGameLibrary::saveToFile(const char *filename)
{
    char userFilename[100];

    if (!filename)
    {
        cout << "What do you want to name the file? (example.txt): ";
        cin.ignore();
        cin.getline(userFilename, sizeof(userFilename));
        filename = userFilename;
    }

    ofstream outfile(filename);

    if (!outfile)
    {
        cout << "Error: Unable to open the file for writing.\n";
        return;
    }

    for (int i = 0; i < numGames; i++)
        videoGameArray[i]->printVideoGameDetailsToFile(outfile);

    outfile.close();
    cout << "All video games in your library have been printed to ";
    cout << filename << endl;
};

void videoGameLibrary::resizeVideoGameArray()
{
    int newSize = maxGames * 2;

    cout << "\nResizing VideoGameArray from " << maxGames;
    cout << " to " << newSize << ".\n";

    videoGame **newVideoGameArray = new videoGame *[newSize];

    for (int i = 0; i < numGames; i++)
        newVideoGameArray[i] = videoGameArray[i];

    delete[] videoGameArray;

    maxGames = newSize;
    videoGameArray = newVideoGameArray;
};