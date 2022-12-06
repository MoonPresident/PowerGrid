#ifndef TEXT_H
#define TEXT_H

#include "Font.h"
#include "ext.hpp"
#include "Shader.h"
//TODO: Add setfont function

class Text {
private:
    Shader textShader;

    unsigned int textVAO, textVBO;
    int location;
    Font font;
    int textColourLocation;
    
public:
    Text();
    ~Text();

    void setPerspective(int width, int height);

    //TODO:
    //void renderMultiline
    
    //TODO: Gives options on rendering from the top or the bottom, from the left or the right.
    //Alignment options I suppose.
    void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif /*Text*/