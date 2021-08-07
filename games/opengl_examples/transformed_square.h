#include <iostream>

#include "my_debug.h"
#include "AbstractSimulation/h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Debug
//#define debug_transformed_square

#ifndef TRANSFORMED_SQUARE_H
#define TRANSFORMED_SQUARE_H

class TransformedSquare: public AbstractSimulation {
public:
    TransformedSquare () {
        #ifdef debug_all || debug_transformed_square
        std::cout << "Transformed square created." << std::endl;
        #endif
    }
    
    void run () {
        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
        vec = trans * vec;
        std::cout << vec.x << vec.y << vec.z << std::endl;
        
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        
        glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) {
            glUseProgram(program);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
    }
};

#endif /* TRANSFORMED_SQUARE_H */