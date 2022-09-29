#ifndef TEXT_H
#define TEXT_H

#include "Font.h"
#include "glm.hpp"

class Text {
private:
    Shader textShader;

    unsigned int textVAO, textVBO;
    int location;
    Font font;
    int textColourLocation;
    
public:


    Text():
        font("c:/windows/fonts/arial.ttf"),
        textShader("C:\\dev\\PowerGrid\\resources\\shaders\\glyph_vertex_shader.txt", 
                    "C:\\dev\\PowerGrid\\resources\\shaders\\glyph_fragment_shader.txt")
    {
        //Buffers:
        glGenVertexArrays(1, &textVAO);
        glGenBuffers(1, &textVBO);
        glBindVertexArray(textVAO);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        textColourLocation = glGetUniformLocation(textShader.ID, "textColor");

        setPerspective(800, 600);
    };

    void setPerspective(int width, int height) {
        int projectionL = glGetUniformLocation(textShader.ID, "projection");
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
        glUseProgram(textShader.ID);
        glUniformMatrix4fv(projectionL, 1, GL_FALSE, glm::value_ptr(projection));
    }



    void renderText(std::string text, 
                    float x, float y, float scale, 
                    glm::vec3 color)
    {
        // activate corresponding render state	
        glUseProgram(textShader.ID);
        
        glUniform3f(textColourLocation, color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(textVAO);
        
        // iterate through all characters
        std::string::const_iterator c;
        int i = 0;
        for (c = text.begin(); c != text.end(); c++)
        {
            
            Font::Character ch = font.Characters[*c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },            
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }           
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, textVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

#endif /*Text*/