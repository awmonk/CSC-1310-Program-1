/* This is a file that contains all of the program's classes and functions, as
   well as the driver, in one discrete file */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;

const int fieldWidth = 30;

class Text {
    public:
        Text(const char *textArray) {
            textLength = strlen(textArray);
            this->textArray = new char[textLength + 1];
            strcpy(this->textArray, textArray);
        };
        ~Text() {
            delete[] textArray;
            cout << "Text destructor: Released memory for textArray.";
            cout << endl;
        };
        void displayText() {
            cout << textArray << endl;
        };
        const char* getText() {
            return textArray;
        };
        int getTextLength() {
            return textLength;
        };
    private:
        char *textArray;
        int textLength;
};

class videoGame {
    public:
        videoGame(Text *title, Text *developer, Text *publisher, int year) {
            this->title     = title;
            this->developer = developer;
            this->publisher = publisher;
            this->year      = year;
        };
        ~videoGame() {
            delete title;
            delete developer;
            delete publisher;
            cout << "VideoGame destructor: Released memory for VideoGame object.";
            cout << endl;
        };
        void printVideoGameDetails() {
            cout << setw(fieldWidth) << right << "Game Title: "     << left
                 << title->getText();
            cout << endl;

            cout << setw(fieldWidth) << right << "Game Developer: " << left
                 << developer->getText();
            cout << endl;

            cout << setw(fieldWidth) << right << "Game Publisher: " << left
                 << publisher->getText();
            cout << endl;

            cout << setw(fieldWidth) << right << "Game Year: "      << left
                 << year;
            cout << endl << endl;
        };
        void printVideoGameDetailsToFile(ofstream &outputFile) {
            outputFile << title->getText()     << endl;
            outputFile << developer->getText() << endl;
            outputFile << publisher->getText() << endl;
            outputFile << year                 << endl;
        };
        void getVideoGameTitle() {
            cout << title->getText();
        };
    private:
        Text *title, *developer, *publisher;
        int year;
};

class videoGameLibrary {
    public:
        videoGameLibrary(int maxGames) {
            videoGameArray = new videoGame*[maxGames];
            this->maxGames = maxGames;
            numGames = 0;
        };
        ~videoGameLibrary() {
            for (int i = 0; i < numGames; i++) {
                delete videoGameArray[i];
            }
            delete[] videoGameArray;
            cout << "VideoGameLibrary destructor: Released memory for ";
            cout << "each game in the video game array and the array itself.";
            cout << endl;
        };
        void addVideoGameToArray() {
            if (numGames < maxGames) {
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
                cin  >> year;
                cin.ignore();

                Text *titleText     = new Text(title);
                Text *developerText = new Text(developer);
                Text *publisherText = new Text(publisher);

                videoGameArray[numGames]
                    = new videoGame(titleText, developerText, publisherText, year);
                numGames++;
            }
            else
                resizeVideoGameArray();
        };
        void displayVideoGames() {
            for (int i = 0; i < numGames; i++) {
                cout << setw(fieldWidth + 18) << right;
                cout << "--------Video Game " << i + 1 << "--------";
                cout << endl;
                videoGameArray[i]->printVideoGameDetails();
            }
        };
        void displayVideoGameTitles() {
            for(int i = 0; i < numGames; i++) {
                cout << endl << i + 1 << ": ";
                videoGameArray[i]->getVideoGameTitle();
            }
        };
        void loadVideoGamesFromFile(const char* filename) {
            char title[10000], developer[10000], publisher[10000];
            int year;
            
            ifstream inputFile(filename);

            if (!inputFile) {
                cout << "Sorry, I was unable to open the file." << endl;
                return;
            }

            while (inputFile.getline(title, sizeof(title))) {
                inputFile.getline(developer, sizeof(developer));
                inputFile.getline(publisher, sizeof(publisher));
                inputFile >> year;
                inputFile.ignore();

                Text *titleText     = new Text(title);
                Text *developerText = new Text(developer);
                Text *publisherText = new Text(publisher);

                videoGameArray[numGames] 
                    = new videoGame(titleText, developerText, publisherText, year);
                numGames++;

                if (numGames == maxGames)
                    resizeVideoGameArray();
                cout << title << " was added successfully.\n";
            }

            inputFile.close();
            cout << endl << numGames << " video games were read from the file and ";
            cout << "added to your VideoGame library\n";
            return;
        };
        void removeVideoGameFromArray() {
            int userChoice;
            if (numGames >= 1) {
                cout << "\nChoose from the following video games to remove:";
                displayVideoGameTitles();
                cout << endl;

                cout << "\nChoose a video game between 1 & " << numGames << ": ";
                cin >> userChoice;
                cout << endl;

                if (userChoice >= 1 && userChoice <= numGames) {
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
            else {
                cout << "There must be at least one game in the library ";
                cout << "to remove a game." << endl;
            }
        };
        void saveToFile(const char* filename) {
            char userFilename[100];
                if (filename == nullptr) {
                    cout << "What do you want to name the file? (example.txt): ";
                    cin.ignore();
                    cin.getline(userFilename, sizeof(userFilename));
                    filename = userFilename;
                }

                ofstream outputFile(filename);

                if (!outputFile) {
                    cout << "Error: Unable to open the file for writing." << endl;
                    return;
                }

                for (int i = 0; i < numGames; i++)
                    videoGameArray[i]->printVideoGameDetailsToFile(outputFile);

                outputFile.close();
                cout << "All video games in your library have been printed to ";
                cout << filename << endl;
        };
        void resizeVideoGameArray() {
            int newSize = maxGames * 2;

            cout << "\nResizing VideoGameArray from " << maxGames;
            cout << " to " << newSize << ".\n";

            videoGame** newVideoGameArray = new videoGame*[newSize];

            for (int i = 0; i < numGames; i++)
                newVideoGameArray[i] = videoGameArray[i];

            delete[] videoGameArray;
            maxGames = newSize;
            videoGameArray = newVideoGameArray;
        };
    private:
        videoGame** videoGameArray;
        int maxGames, numGames;
};

void showMenu();

int main() {
    int maxGames, userChoice = -1;
    bool quit = false;
    char filename[100];

    cout << "How many video games can your library hold? ";
    cin  >> maxGames;

    videoGameLibrary library(maxGames);

     while(!quit) {
        cout << endl;
        showMenu();
        cin  >> userChoice;
        switch(userChoice) {
            case 1:
                cout << "\nWhat is the name of the file? (example.txt): ";
                cin.ignore();
                cin.getline(filename, sizeof(filename));
                cout << endl;
                library.loadVideoGamesFromFile(filename);
                break;
            case 2:
                library.saveToFile(filename);
                break;
            case 3:
                library.addVideoGameToArray();
                break;
            case 4:
                library.removeVideoGameFromArray();
                break;
            case 5:
                library.displayVideoGames();
                break;
            case 6:
                cout << "\nGOODBYE!\n" << endl;
                quit = true;
                break;
            default:
                cout << "That is not a valid choice.\n" << endl;
                break;
        }
    }
    return 0;
};

void showMenu() {
    cout << "What would you like to do?\n";
    cout << "\t1. Load video games from a file\n";
    cout << "\t2. Save video games to a file\n";
    cout << "\t3. Add a video game\n";
    cout << "\t4. Remove a video game\n";
    cout << "\t5. Display all video games\n";
    cout << "\t6. Remove ALL video games from ";
    cout << "this library and END PROGRAM\n";
    cout << "CHOOSE 1-6: ";
};