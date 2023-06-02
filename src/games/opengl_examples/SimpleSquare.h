
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
        
        GLuint vertShader, fragShader;
        vertShader = glCreateShader(GL_VERTEX_SHADER);
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        
        const char* vertShaderSource = "#version 330 core"
            "layout (location = 0) in vec3 aPos;"
            "void main() {gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}";
        const char* fragShaderSource = "#version 330 core"
            "out vec4 FragColor;"
            "void main() {FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}";
        glShaderSource(vertShader, 1, &vertShaderSource, nullptr);
        glShaderSource(fragShader, 1, &fragShaderSource, nullptr);
        glCompileShader(vertShader);
        glCompileShader(fragShader);
        
        GLuint program = glCreateProgram();

        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);
        
        //This captures the escape key.
        glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        while(
            glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) 
        {
            glUseProgram(program);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
            
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