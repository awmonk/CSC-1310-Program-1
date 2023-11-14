/* This is a file that contains all of the program's classes and functions, as
   well as the driver, in one discrete file */

#include <bits/stdc++.h>
using namespace std;

class Text
{
public:
    Text(const char *textArray)
    {
        textLength = strlen(textArray);
        this->textArray = new char[textLength + 1];
        strcpy(this->textArray, textArray);
    };

    ~Text()
    {
        delete[] textArray;
        cout << "Text destructor: Released memory for textArray.\n";
    };

    void displayText() { cout << textArray << "\n"; };
    const char *getText() { return textArray; };
    int getTextLength() { return textLength; };

private:
    char *textArray;
    int textLength;
};

class videoGame
{
public:
    videoGame(Text *t, Text *d, Text *p, int y)
        : title(t), developer(d), publisher(p), year(y){};

    ~videoGame()
    {
        delete title;
        delete developer;
        delete publisher;
        cout << "VideoGame destructor: Released memory for VideoGame object.\n";
    };

    void printVideoGameDetails()
    {
        cout << setw(30) << right << "Game Title: "
             << setw(30) << left << title->getText()
             << "\n";

        cout << setw(30) << right << "Game Developer: "
             << setw(30) << left << developer->getText()
             << "\n";

        cout << setw(30) << right << "Game Publisher: "
             << setw(30) << left << publisher->getText()
             << "\n";

        cout << setw(30) << right << "Game Year: "
             << setw(30) << left << year
             << "\n";
    };

    void printVideoGameDetailsToFile(ofstream &outfile)
    {
        outfile << title->getText() << "\n"
                << developer->getText() << "\n"
                << publisher->getText() << "\n"
                << year << "\n";
    };

    void getVideoGameTitle() { cout << title->getText(); };

private:
    Text *title, *developer, *publisher;
    int year;
};

class videoGameLibrary
{
public:
    videoGameLibrary(int maxGames) : maxGames(maxGames), numGames(0)
    {
        videoGameArray = new videoGame *[maxGames];
    };

    ~videoGameLibrary()
    {
        for (int i = 0; i < numGames; i++)
            delete videoGameArray[i];

        delete[] videoGameArray;

        cout << "VideoGameLibrary destructor: Released memory for "
             << "each game in the video game array and the array itself."
             << "\n\nGOODBYE!\n\n";
    };

    void addVideoGameToArray()
    {
        if (numGames < maxGames)
        {
            char title[100], developer[100], publisher[100];
            int year;

            cout << "\n";
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

    void displayVideoGames()
    {
        for (int i = 0; i < numGames; i++)
        {
            cout << "\n"
                 << setw(50) << right
                 << "-------- Video Game " << i + 1 << " --------\n";
            videoGameArray[i]->printVideoGameDetails();
        }
    };

    void displayVideoGameTitles()
    {
        for (int i = 0; i < numGames; i++)
        {
            cout << "\n"
                 << i + 1 << ": ";
            videoGameArray[i]->getVideoGameTitle();
        }
    };

    void loadVideoGamesFromFile(const char *filename)
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

        cout << "\n"
             << numGames << " video games were read from the file and "
             << "added to your VideoGame library\n";

        return;
    };

    void removeVideoGameFromArray()
    {
        int choice;

        if (numGames >= 1)
        {
            cout << "\nChoose from the following video games to remove:";
            displayVideoGameTitles();
            cout << "\n";

            cout << "\nChoose a video game between 1 & " << numGames << ": ";
            cin >> choice;
            cout << "\n";

            if (choice >= 1 && choice <= numGames)
            {
                cout << "\nThe video game ";
                videoGameArray[choice - 1]->getVideoGameTitle();
                cout << " has been successfully deleted.\n\n";

                delete videoGameArray[choice - 1];

                for (int i = choice - 1; i < numGames - 1; i++)
                    videoGameArray[i] = videoGameArray[i + 1];

                numGames--;
            }
            else
                cout << "That is not a valid choice.\n";
        }
        else
        {
            cout << "There must be at least one game in the library "
                 << "to remove a game.\n";
        }
    };

    void saveToFile(const char *filename)
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

        cout << "All video games in your library have been printed to "
             << filename << "\n";
    };

    void resizeVideoGameArray()
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

private:
    videoGame **videoGameArray;
    int maxGames, numGames;
};

void showMenu()
{
    cout << "\nWhat would you like to do?\n\n"
         << "\t1. Load video games from a file\n"
         << "\t2. Save video games to a file\n"
         << "\t3. Add a video game\n"
         << "\t4. Remove a video game\n"
         << "\t5. Display all video games\n"
         << "\t6. Remove ALL video games from "
         << "this library and END PROGRAM\n\n"
         << "CHOOSE 1-6: ";
};

int main()
{
    int maxGames, choice = -1;
    char filename[100];

    cout << "\nHow many video games can your library hold? ";
    cin >> maxGames;

    videoGameLibrary *library = new videoGameLibrary(maxGames);

    while (choice != 6)
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nWhat is the name of the file? (example.txt): ";
            cin.ignore();

            cin.getline(filename, sizeof(filename));
            cout << "\n";

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
            break;

        default:
            cout << "That is not a valid choice.\n\n";
            break;
        }
    }

    cout << "\n";
    delete library;

    return 0;
};