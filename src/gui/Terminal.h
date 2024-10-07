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
#include <array>

class Terminal {
private:
    const int lineSize = 128;
    const int maxIndex = 1000;

    int index;
    bool wrapped;
    bool isVisible;

    //Shader target
    int colorLocation;
public:
    Text text;
    std::vector<std::string> textLines;

    unsigned int backgroundVAO, backgroundVBO;

    //Graphical elements
    Shader backgroundShader;

    Terminal();
    ~Terminal();

    void log(const char* newLine);
    void draw();

    void toggleVisible();
};

#endif /* TERMINAL_H */