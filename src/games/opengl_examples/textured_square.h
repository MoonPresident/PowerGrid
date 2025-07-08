#include "AbstractSimulation.h"
#include <iostream>

#include "TextureFactory.h"
#include "ShaderStore.h"

#include "glad/glad.h"

//Debug
#define debug_textured_squares

#ifndef TEXTURED_SQUARE_H
#define TEXTURED_SQUARE_H

class TexturedSquare: public AbstractSimulation {
public:
    TexturedSquare() {
        #ifdef debug_all
        std::cout << "Textured Square started " << std::endl;
#endif 
    }
    
    void run() {
        GLuint vao, vbo, ebo;
        glGenVertexArrays(1, &vao);        
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        
        static const GLfloat vertexData[] = {
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3,
        };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        ShaderStore shader;
        shader.addShader("C:\\dev\\PowerGrid\\resources\\shaders\\texture_2d_vertex_shader.txt", GL_VERTEX_SHADER);
        shader.addShader("C:\\dev\\PowerGrid\\resources\\shaders\\texture_2d_fragment_shader.txt", GL_FRAGMENT_SHADER);
        
        GLuint program = glCreateProgram();
        shader.linkProgram(program);
        
        TextureFactory texFactory;
        GLuint tex = texFactory.getTexture("C:\\dev\\PowerGrid\\src\\games\\opengl_examples\\fish_eyes1.jpg");
        glBindTexture(GL_TEXTURE_2D, tex);
        
        //This captures the escape key.
        glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) {
            
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            glBindTexture(GL_TEXTURE_2D, tex);
            
            glUseProgram(program);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
            
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
        
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return;
    }
};

#endif /* TEXTURED_SQUARE_H */