#include "AbstractSimulation.h"
#include <iostream>

#include "TextureFactory.h"
#include "ShaderStore.h"

#include "glad/glad.h"
#include "Font.h"

//Debug
#define debug_textured_squares

#ifndef TEXT_RENDERING_EXAMPLE_H
#define TEXT_RENDERING_EXAMPLE_H

class TextRenderingExample: public AbstractSimulation {
public:
    TextRenderingExample() {};
    ~TextRenderingExample() {};

    void run() {
        #ifdef SHADER_PATH
        std::cout << SHADER_PATH << std::endl;
        #endif
        Font font("c:/windows/fonts/arial.ttf");
        
        ShaderStore shader;
        shader.addShader("glyph_vertex_shader.txt", GL_VERTEX_SHADER);
        shader.addShader("glyph_fragment_shader.txt", GL_FRAGMENT_SHADER);
        
        GLuint program = glCreateProgram();
        shader.linkProgram(program);
        glUseProgram(program);

        //Enable culling of all front facing shader.
        //Front facing shader have a 
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        unsigned int VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0); 

        int textColourLocation = glGetUniformLocation(program, "textColor");
        
        
        glm::mat4 projection = glm::ortho(0.f, 1000.f, 0.f, 1000.f);
        glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //This captures the escape key.
        glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) {
            
            
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            font.renderText(program, textColourLocation,
                VAO, VBO,
                "Example text.", 300.0f, 470.0f, 1.0f,
                glm::vec3(0.5, 0.2f, 0.2f));

            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
        
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return;
    };
};

#endif /* TEXT_RENDERING_EXAMPLE_H */