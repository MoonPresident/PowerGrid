/**
 * Author: MoonPresident
 * Date: November 30th 2022
 * 
 * Short term memory for logging. Might enhance later with logging to a text document.
 */

//TODO
// scrolling
// capture key inputs.
// Maybe terminal should just override all key inputs if its up?
// Should generalise the key handling interrupt. Keyboard class?

#include "Terminal.h"
#include "my_debug.h"

Terminal::Terminal():
    wrapped(false),
    index(0),
    isVisible(false),
    text(),
    backgroundShader(
        "C:/dev/PowerGrid/resources/shaders/screen_oriented_colorable.vs",
        "C:/dev/PowerGrid/resources/shaders/simple_colorable.fs"
    )
{
    //Shader management
    colorLocation = glGetUniformLocation(backgroundShader.ID, "colorIn");
    
    //Set up terminal
    textLines.resize(maxIndex);

    glGenVertexArrays(1, &backgroundVAO);
    glGenBuffers(1, &backgroundVBO);
    glBindVertexArray(backgroundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, backgroundVBO);
    
    //TODO: Abstract and link to line length by perspective. 
    //(I assume this will present itself as screen height determining terminal width.)
    std::array<float, 18> vertices = {
            -1.0f, -1.0f,  -0.99f,
             0.2f, -1.0f,  -0.99f,
             0.2f,  0.2f,  -0.99f,
            -1.0f,  0.2f,  -0.99f,
            -1.0f, -1.0f,  -0.99f,
             0.2f,  0.2f,  -0.99f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.data()), vertices.data(), GL_STATIC_DRAW); 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);

    //unbind buffer to prevent overwriting.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    for(int i = 0; i < 10; i++) {
        std::array<char, 30> buffer;
        sprintf(buffer.data(), "Terminal: Pre init %i.", i);
        log(buffer.data());
    }
    log("Terminal: Initialised.");
    log("Terminal: Logging...");
    for(int i = 0; i < 10; i++) {
        std::array<char, 30> buffer;
        sprintf(buffer.data(), "Terminal: %i.", i);
        log(buffer.data());
    }
    
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
        textLines[index++] = "Wrapping log.";
    }
}

//Either need a new shader or to actually do screen space transforms on this. 
//Maybe split those options into different implementations.
void Terminal::draw() {
    //Draw.
    if(!isVisible) {
        return;
    }

    glDisable(GL_DEPTH_TEST);

    glUseProgram(backgroundShader.ID);
    glBindVertexArray(backgroundVAO);
    glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.2f, 0.2f, 0.2f, 0.8f)));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Handle height
    //handle scroll? Maybe.

    float currentHeight = 2.f;
    float lineSpacing = 15.f;
    

    for(int i = index; i > 0; i--) {
        int offsetIndex = i - 1; //Index is always 1 ahead of latest index.
        text.renderText(textLines.at(offsetIndex), 2.f, currentHeight, 0.25f, glm::vec3(1.f, 1.f, 1.f));
        currentHeight += lineSpacing;
    }

    if(wrapped) {
        for(int i = maxIndex; i > index; i--) {
            int offsetIndex = i - 1;
            text.renderText(textLines.at(offsetIndex), 2.f, currentHeight, 0.25f, glm::vec3(1.f, 1.f, 1.f));
            currentHeight += lineSpacing;
        }
    }

    glEnable(GL_DEPTH_TEST);

}

void Terminal::toggleVisible() {
    isVisible = !isVisible;
}