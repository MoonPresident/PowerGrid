
#include "my_debug.h"
#include "AbstractSimulation.h"

#include "glad/glad.h"
#include "shaderStore.h"

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
        
        ShaderStore shader;
        shader.addShader("..\\resources\\shaders\\generic_2d_vertex_shader.txt", GL_VERTEX_SHADER);
        shader.addShader("..\\resources\\shaders\\generic_2d_fragment_shader.txt", GL_FRAGMENT_SHADER);
        
        GLuint program = glCreateProgram();
        shader.linkProgram(program);
        
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