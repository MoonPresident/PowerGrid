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
    const size_t lineSize = 128;
    const size_t maxIndex = 1000;

    bool wrapped;
    int index;
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