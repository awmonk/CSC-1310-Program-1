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

    void displayText() { cout << textArray << endl; };
    const char *getText() { return textArray; };
    int getTextLength() { return textLength; };

private:
    char *textArray;
    int textLength;
};

class videoGame
{
public:
    videoGame(Text *title, Text *developer, Text *publisher, int year)
    {
        this->title = title;
        this->developer = developer;
        this->publisher = publisher;
        this->year = year;
    };

    ~videoGame()
    {
        delete title;
        delete developer;
        delete publisher;
        cout << "VideoGame destructor: Released memory for VideoGame object.\n";
    };

    void printVideoGameDetails()
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

    void printVideoGameDetailsToFile(ofstream &outfile)
    {
        outfile << title->getText() << "\n";
        outfile << developer->getText() << "\n";
        outfile << publisher->getText() << "\n";
        outfile << year << "\n";
    };

    void getVideoGameTitle() { cout << title->getText(); };

private:
    Text *title, *developer, *publisher;
    int year;
};

class videoGameLibrary
{
public:
    videoGameLibrary(int maxGames)
    {
        videoGameArray = new videoGame *[maxGames];
        this->maxGames = maxGames;
        numGames = 0;
    };

    ~videoGameLibrary()
    {
        for (int i = 0; i < numGames; i++)
            delete videoGameArray[i];

        delete[] videoGameArray;

        cout << "VideoGameLibrary destructor: Released memory for ";
        cout << "each game in the video game array and the array itself.";
        cout << "\n\nGOODBYE!\n\n";
    };

    void addVideoGameToArray()
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

    void displayVideoGames()
    {
        for (int i = 0; i < numGames; i++)
        {
            cout << "\n";
            cout << setw(50) << right;
            cout << "-------- Video Game " << i + 1 << " --------\n";
            videoGameArray[i]->printVideoGameDetails();
        }
    };

    void displayVideoGameTitles()
    {
        for (int i = 0; i < numGames; i++)
        {
            cout << endl;
            cout << i + 1 << ": ";
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

        cout << endl;
        cout << numGames << " video games were read from the file and ";
        cout << "added to your VideoGame library\n";

        return;
    };

    void removeVideoGameFromArray()
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

    void saveToFile(const char *filename)
    {
        char userFilename[100];
        if (filename == nullptr)
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