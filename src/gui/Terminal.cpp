#include "Terminal.h"

Terminal::Terminal():
    wrapped(false),
    index(0),
    isVisible(false),
    backgroundShader(
        "C:/dev/PowerGrid/resources/shaders/simple_colorable.vs",
        "C:/dev/PowerGrid/resources/shaders/simple_colorable.fs"
    )
    // text()
{
    //Set up terminal
    textLines.reserve(maxIndex);

    glGenVertexArrays(1, &backgroundVAO);
    glGenBuffers(1, &backgroundVBO);
    glBindVertexArray(backgroundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, backgroundVBO);
    
    float vertices[18] = {
         0.f,   0.f,  0.f,
         0.f,  0.5f,  1.f,
        0.5f,  0.0f,  1.f,
         0.f,  0.5f,  1.f,
        0.5f,  0.5f,  1.f,
        0.5f,   0.f,  1.f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
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

    glUseProgram(backgroundShader.ID);

    int colorLocation = glGetUniformLocation(backgroundShader.ID, "textColor");
    glUniform4f(colorLocation, 0.2f, 0.2f, 0.2f, 0.6f);
    glBindBuffer(GL_ARRAY_BUFFER, backgroundVBO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

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