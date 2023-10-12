#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <cstring>
using namespace std;

class Text
{
public:
    Text(const char *textArray);
    ~Text();
    void displayText();
    const char *getText();
    int getTextLength();

private:
    char *textArray;
    int textLength;
};

#endif