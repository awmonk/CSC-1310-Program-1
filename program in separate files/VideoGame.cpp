#include <VideoGame.h>
using namespace std;

const int fieldWidth = 30;

class videoGame {
    public:
        videoGame(Text *title, Text *developer, Text *publisher, int year) {
            /* Initializes all attributes to the arguments sent to this function. */
            this->title     = title;
            this->developer = developer;
            this->publisher = publisher;
            this->year      = year;
        };
        ~videoGame() {
            /* Releases the dynamically allocated space for the videoGame title,
               developer, and publisher and then prints a message */
            delete title;
            delete developer;
            delete publisher;
            cout << "VideoGame destructor: Released memory for VideoGame object.";
            cout << endl;
        };
        void printVideoGameDetails() {
            /* Prints the title, developer, publisher, & year. In order to print the
               Text objects the displayText function is called. Uses the setw
               function defined in <iomanip> to produce the desired output */
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
            /* Print the title, developer, publisher, & year to the file stream object
               that was sent to this function. In order to print the Text objects to
               the file, you must first retrieve the c-string attribute (calling the
               getText function) from this Text, and then you can print it to the
               file. */
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