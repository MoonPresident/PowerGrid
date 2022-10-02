


#ifndef TERMINAL_H
#define TERMINAL_H

#include "Text.h"
#include <vector>

class Terminal {
public:
    Text text;
    
    std::vector<std::string> textLines;
    int index;
    bool wrapped;

    Terminal():
        wrapped(false),
        index(0)
     {
        //Set up terminal
        textLines.reserve(1000);
    }

    ~Terminal() {
        textLines.clear();
    }

    void log(const char* newLine) {
        //Redraw including and update to the logs.
        std::string line(newLine);
        if(line.size() > 1000) {
            line = line.substr(1000);
        }
        textLines[index++] = line;
        if(index >= maxIndex) {
            index = 0;
            wrapped = true;
        }
    }

    void draw() {
        //Draw.
        

        //Handle height
        //handle scroll? Maybe.
        text.renderText();
    }
};

#endif /* TERMINAL_H */