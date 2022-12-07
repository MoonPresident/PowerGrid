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
    //Set up terminal
    textLines.resize(maxIndex);

    glGenVertexArrays(1, &backgroundVAO);
    glGenBuffers(1, &backgroundVBO);
    glBindVertexArray(backgroundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, backgroundVBO);
    
    float vertices[18] = {
            -1.0f, -1.0f,  -1.f,
             0.2f, -1.0f,  -1.f,
             0.2f,  0.2f,  -1.f,
            -1.0f,  0.2f,  -1.f,
            -1.0f, -1.0f,  -1.f,
             0.2f,  0.2f,  -1.f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    for(int i = 0; i < 10; i++) {
        char buffer[30];
        sprintf(buffer, "Terminal: Pre init %i.", i);
        log(buffer);
    }
    log("Terminal: Initialised.");
    log("Terminal: Logging...");
    for(int i = 0; i < 10; i++) {
        char buffer[30];
        sprintf(buffer, "Terminal: %i.", i);
        log(buffer);
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
        // return;
    }


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

        
    glUseProgram(backgroundShader.ID);
    glBindVertexArray(backgroundVAO);

    GLboolean blendCheck;
    blendCheck = GL_FALSE;
    glGetBooleanv(GL_BLEND, &blendCheck);
    if(blendCheck == GL_TRUE) std::cout << "TRUE\n";

    int colorLocation = glGetUniformLocation(backgroundShader.ID, "colorIn");
    glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.3f, 0.3f, 0.3f, 0.4f)));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Handle height
    //handle scroll? Maybe.

    //print grey semiopaque background.
    //renderBackground.
    
    //print all text.
    //  find visible lines and draw.
    //  Also, input buffer.

    //print input.

}