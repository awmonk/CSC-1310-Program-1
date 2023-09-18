#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <cstring>
using namespace std;

class Text {
    public:
        Text(const char *textArray);
        /* Called automatically when Text object is created, dynamically allocates
           a character array which contains the character array passed to the
           function. */
        ~Text();
        /* Release dynamically allocated memory for the c-string in the Text object */
        void displayText();
        /* Print the c-string (textArray) to the screen. */
        const char* getText();
        /* Returns a pointer to a constant character array */
        int getTextLength();
        /* Returns the length of the string */
    private:
        char *textArray;
        /* A pointer to a constant character array */
        int textLength;
        /* An integer representing the number of characters stored in the textArray */
};

#endif