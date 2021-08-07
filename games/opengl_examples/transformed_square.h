#include <iostream>

#include "my_debug.h"
#include "AbstractSimulation.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

//Debug
//#define debug_transformed_square

//https://learnopengl.com/Getting-started/Transformations

#ifndef TRANSFORMED_SQUARE_H
#define TRANSFORMED_SQUARE_H

class TransformedSquare: public AbstractSimulation {
public:
    TransformedSquare () {
        #ifdef debug_all
        std::cout << "Transformed square created." << std::endl;
        #endif
    }
    
    void run () {
        GLuint vao, vbo, ebo;
        glGenVertexArrays(1, &vao);        
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        
        glBindVertexArray(vao);

        
        static const GLfloat vertexData[] = {
             0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
        };
        
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3,
        };
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        ShaderStore shader;
        shader.addShader("..\\resources\\shaders\\transform_vertex_shader.txt", GL_VERTEX_SHADER);
        shader.addShader("..\\resources\\shaders\\texture_2d_fragment_shader.txt", GL_FRAGMENT_SHADER);
        
        GLuint program = glCreateProgram();
        shader.linkProgram(program);
        
        TextureFactory texFactory;
        GLuint tex = texFactory.getTexture("..\\games\\opengl_examples\\fish_eyes.jpg");
        glBindTexture(GL_TEXTURE_2D, tex);
        
        float x_off[2] = {-0.5f, 0.5f};
        float y_off[2] = {-0.5f, 0.5f};
        int x_dir[2] = {1, 1};
        int y_dir[2] = {1, 1};
        
        //This captures the escape key.
        glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) {
            

            
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            glBindTexture(GL_TEXTURE_2D, tex);
            
            glUseProgram(program);
            
            for(int i = 0; i < 2; i++) {
                x_off[i] += 0.0001f * x_dir[i];
                y_off[i] += 0.00007f * y_dir[i];
                
                if(x_off[i] > 0.5f || x_off[i] < -0.5f) {
                    x_dir[i] *= -1;
                }
                
                if(y_off[i] > 0.5f || y_off[i] < -0.5f) {
                    y_dir[i] *= -1;
                }
                
                glm::mat4 trans = glm::mat4(1.0f);
                trans = glm::translate(trans, glm::vec3(x_off[i], y_off[i], 0.0f));
                trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
                
                unsigned int transformLoc = glGetUniformLocation(program, "transform");
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
                
                glBindVertexArray(vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            
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

#endif /* TRANSFORMED_SQUARE_H */