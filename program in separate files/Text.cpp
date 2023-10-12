#include "Text.h"
using namespace std;

Text::Text(const char *textArray)
{
    textLength = strlen(textArray);
    this->textArray = new char[textLength + 1];
    strcpy(this->textArray, textArray);
};

Text::~Text()
{
    delete[] textArray;
    cout << "Text destructor: Released memory for textArray.\n";
};

void Text::displayText() { cout << textArray << endl; };
const char *Text::getText() { return textArray; };
int Text::getTextLength() { return textLength; };