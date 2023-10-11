#include "Text.h"
#include "VideoGameLibrary.h"
using namespace std;

videoGameLibrary::videoGameLibrary(int maxGames)
{
    /* The function will dynamically allocate an array of pointers
        to VideoGame objects based on the maximum size and will also
        set the current number of video games to zero. */
    videoGameArray = new videoGame *[maxGames];
    this->maxGames = maxGames;
    numGames = 0;
};

videoGameLibrary::~videoGameLibrary()
{
    /* This function releases the dynamically created individual
        videoGames, deletes the array, and then prints a message. */
    for (int i = 0; i < numGames; i++)
        delete videoGameArray[i];

    delete[] videoGameArray;

    cout << "VideoGameLibrary destructor: Released memory for ";
    cout << "each game in the video game array and the array itself.";
    cout << "\n\nGOODBYE!\n\n";
    return;
};

void videoGameLibrary::addVideoGameToArray()
{
    /* It should ask the user for the video game title (read in as
        c-string, then dynamically create a Text object), developer
        (read in as c-string, then dynamically create a Text object),
        publisher (read in as c-string, then dynamically create a Text
        object), and release year (integer). Then it should dynamically
        allocate a new VideoGame object, sending the video game data
        just acquired from the user as arguments to the VideoGame
        constructor. Then, this function should check to see if
        numGames is equal to maxGames. If it is equal, then call the
        resizeVideoGameArray function. Then, it should assign this new
        video game to the correct pointer in the videoGamesArray.Last,
        it should increment numGames. */
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
    /* This function loops through the videoGamesArray and calls
        each videoGame’s printVideoGameDetails function. */
    if (numGames == 0)
        cout << "There are no games in this library.\n";

    for (int i = 0; i < numGames; i++)
    {
        /* Getting the title to be the right distance was kind of annyoing */
        cout << setw(48) << right;
        cout << "--------Video Game " << i + 1 << "--------\n";
        videoGameArray[i]->printVideoGameDetails();
    }
};

void videoGameLibrary::displayVideoGameTitles()
{
    /* This function should loop through the videoGameArray, retrieve
        the videoGame’s title by calling the videoGame’s getVideoGameTitle
        function, and then print out the title by calling the Text’s
        displayText function. */
    for (int i = 0; i < numGames; i++)
    {
        cout << endl;
        cout << i + 1 << ": ";
        videoGameArray[i]->getVideoGameTitle();
    }
};

void videoGameLibrary::loadVideoGamesFromFile(const char *filename)
{
    /* This function will use a loop to read the contents of the file
        until reaching the end of file. For each video game, it will read
        the title in with a c-string and then dynamically allocate a Text
        to hold the title. Then it will read in the video game developer
        with a c-string and then dynamically allocate a Text to hold the
        publisher. Then it will read in the video game year. Then, it will
        dynamically create a new videoGame object, sending the video game
        data just acquired from the user as arguments to the videoGame
        constructor. Then, this function should check to see if numGames
        is equal to maxGames. If it is equal, then call the
        resizeVideoGameArray function. Then, it should assign this new
        video game to the correct pointer in the videoGameArray. Then,
        it should increment numGames. Then, it should print the title of
        the video game and say “ was added successfully” This should
        happen for each video game read from the file. At the end of the
        function, it should print out how many video games were read from
        the file & added to the library. */
    char title[10000], developer[10000], publisher[10000];
    int year;

    ifstream inputFile(filename);

    if (!inputFile)
    {
        cout << "Sorry, I was unable to open the file." << endl;
        return;
    }

    while (inputFile.getline(title, sizeof(title)))
    {
        inputFile.getline(developer, sizeof(developer));
        inputFile.getline(publisher, sizeof(publisher));
        inputFile >> year;
        inputFile.ignore();

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

    inputFile.close();

    cout << endl;
    cout << numGames << " video games were read from the file and ";
    cout << "added to your VideoGame library\n";
    return;
};

void videoGameLibrary::removeVideoGameFromArray()
{
    /* This function should first make sure that the number of video
        games is at least 1. If not, it should print that there must
        always be one video game in the library and the function should
        end. Then, the function should call the displayVideoGameTitles
        function to print all the videoGame titles. Then, ask the user
        to choose a videoGame to remove between 1 & numGames. Once the
        user identifies the videoGame, your program should print that
        the videoGame title has been successfully deleted. Then, release
        the dynamically allocated space for this videoGame and move all
        array elements in videoGameArray back 1 starting with this deleted
        videoGame’s element. Last, decrement numGames. */
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
            cout << " has been successfully deleted.\n";
            cout << endl;

            delete videoGameArray[userChoice - 1];

            for (int i = userChoice - 1; i < numGames - 1; i++)
                videoGameArray[i] = videoGameArray[i + 1];
            cout << endl;
            numGames--;
        }
        else
            cout << "That is not a valid choice." << endl;
    }
    else
    {
        cout << "There must be at least one game in the library ";
        cout << "to remove a game." << endl;
    }
};

void videoGameLibrary::saveToFile(const char *filename)
{
    /* Open the file with the filename that was sent to this function.
        Then, use a loop to go through the videoGameArray and call the
        videoGame’s printVideoGameDetailsToFile function, sending the
        filestream object to be printed to. Then, close the file and print
        a confirmation that all video games have been printed to the
        filename. */
    char userFilename[100];

    if (filename == nullptr)
    {
        cout << "What do you want to name the file? (example.txt): ";
        cin.ignore();
        cin.getline(userFilename, sizeof(userFilename));
        filename = userFilename;
    }

    ofstream outputFile(filename);

    if (!outputFile)
    {
        cout << "Error: Unable to open the file for writing." << endl;
        return;
    }

    for (int i = 0; i < numGames; i++)
        videoGameArray[i]->printVideoGameDetailsToFile(outputFile);

    outputFile.close();
    cout << "All video games in your library have been printed to ";
    cout << filename << endl;
};

void videoGameLibrary::resizeVideoGameArray()
{
    /* This function is called by addVideoGameToArray when the array
        size is not big enough to hold a new video game that needs to
        be added. The function makes the array twice as big as it
        currently is and then moves all the video game pointers to
        this new array. */
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