#include <Text.h>
using namespace std;

class Text {
    public:
        Text(const char *textArray) {
            /* Dynamically allocate a new character string the size of the string
               passed to this function plus one (for the null terminator). Then, copy
               the text sent as an argument to this constructor to the new dynamically
               allocated c-string (using the strcpy function from the cstring library).
               Then, set the textArray attribute to this newly created c-string. */
            textLength = strlen(textArray);
            this->textArray = new char[textLength + 1];
            strcpy(this->textArray, textArray);
        };
        ~Text() {
            /* Releases the memory for the c-string pointed to by textArray and prints
               a message */
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