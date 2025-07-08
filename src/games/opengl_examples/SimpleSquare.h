
#include "my_debug.h"
#include "AbstractSimulation.h"

#include "glad/glad.h"

#ifdef debug_all
#include <iostream>
#endif

#ifndef SIMPLE_SQUARE_H
#define SIMPLE_SQUARE_H

class SimpleSquare: AbstractSimulation {
    public:
    SimpleSquare() {
        #ifdef debug_all
        std::cout << "Test" << std::endl;
        #endif
        
    }
    virtual ~SimpleSquare() {}
    
    void run() {
        GLuint vao, vbo;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        static const GLfloat vertexData[] = {
            -0.2f, -0.2f, 0.f,
            0.2f, -0.2f, 0.f,
            0.2f, 0.2f, 0.f,
            -0.2f, 0.2f, 0.f,
            -0.2f, -0.2f, 0.f,
            0.2f, 0.2f, 0.f,
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);
        
        GLuint vertShader, fragShader;
        vertShader = glCreateShader(GL_VERTEX_SHADER);
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        GLuint program = glCreateProgram();
        
        const char* vertShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main() {gl_Position = vec4(aPos, 1.0);}";
        glShaderSource(vertShader, 1, &vertShaderSource, nullptr);
        glCompileShader(vertShader);
        glAttachShader(program, vertShader);
        
        const char* fragShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main() {FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}";
        glShaderSource(fragShader, 1, &fragShaderSource, nullptr);
        glCompileShader(fragShader);
        glAttachShader(program, fragShader);
        
        glLinkProgram(program);
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        //This captures the escape key.
        glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        while(
            glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) 
        {
            glUseProgram(program);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            
            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
        
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return;
    }
    
};

#endif /* SIMPLE_SQUARE_H */