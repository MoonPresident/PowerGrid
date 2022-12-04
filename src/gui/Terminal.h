/**
 * Author: MoonPresident
 * Date: November 30th 2022
 * 
 * Short term memory for logging. Might enhance later with logging to a text document.
 */


#ifndef TERMINAL_H
#define TERMINAL_H

#include "Text.h"
#include <vector>

const int lineSize = 128;
const int maxIndex = 1000;

class Terminal {
public:
    Text text;
    std::vector<std::string> textLines;
    int index;
    bool wrapped;

    void log(const char* newLine);
    void draw();
};

#endif /* TERMINAL_H */