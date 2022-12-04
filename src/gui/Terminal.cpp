#include "Terminal.h"

Terminal::Terminal():
    wrapped(false),
    index(0)
{
    //Set up terminal
    textLines.reserve(maxIndex);
}

Terminal::~Terminal() {
    textLines.clear();
}

void Terminal::log(const char* newLine) {
    //Redraw including and update to the logs.
    std::string line(newLine);
    if(line.size() > lineSize) {
        line = line.substr(lineSize);
    }
    
    textLines[index++] = line;

    if(index >= maxIndex) {
        index = 0;
        wrapped = true;
    }
}

void Terminal::draw() {
    //Draw.
    if(!isVisible) {
        return;
    }

    //Handle height
    //handle scroll? Maybe.

    //print grey semiopaque background.
    //renderBackground.
    
    //print all text.
    //  find visible lines and draw.
    //  Also, input buffer.

    //print input.

    // text.renderText();
}