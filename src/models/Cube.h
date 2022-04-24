#ifndef CUBE_H
#define CUBE_H

#include "Shader.h"
#include "TextureFactory.h"

#include "glad/glad.h"
#include "glm.hpp"

class Cube {
public:
    GLuint vao, vbo, ebo, tex;
    Shader shader;

    Cube(): Cube(
        "C:\\dev\\PowerGrid\\resources\\shaders\\transform_3d_vertex_shader.txt",
        "C:\\dev\\PowerGrid\\resources\\shaders\\phong_texture_fragment_shader.txt"
    ) {};

    Cube(const char* vertShaderPath, const char* fragShaderPath): 
          shader(vertShaderPath, fragShaderPath) 
    {

        glGenVertexArrays(1, &vao);        
        glGenBuffers(1, &vbo);
        
        glBindVertexArray(vao);
        glEnable(GL_DEPTH_TEST);

        static const GLfloat vertexData[] = {
            -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,         0.f, 0.f, 1.f,// front bottom left
             0.5f, -0.5f,  0.5f,        1.0f, 0.0f,         0.f, 0.f, 1.f,// front bottom right
             0.5f,  0.5f,  0.5f,        1.0f, 1.0f,         0.f, 0.f, 1.f,// front top right
            -0.5f,  0.5f,  0.5f,        0.0f, 1.0f,         0.f, 0.f, 1.f,// front top left
            -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,         0.f, 0.f, 1.f,// front bottom left
             0.5f,  0.5f,  0.5f,        1.0f, 1.0f,         0.f, 0.f, 1.f,// front top right

            -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,         0.f, 0.f, -1.f,// back  bottom left
            -0.5f,  0.5f, -0.5f,        0.0f, 1.0f,         0.f, 0.f, -1.f,// back  top left 
             0.5f,  0.5f, -0.5f,        1.0f, 1.0f,         0.f, 0.f, -1.f,// back  top right
             0.5f, -0.5f, -0.5f,        1.0f, 0.0f,         0.f, 0.f, -1.f,// back  bottom right
            -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,         0.f, 0.f, -1.f,// back  bottom left
             0.5f,  0.5f, -0.5f,        1.0f, 1.0f,         0.f, 0.f, -1.f,// back  top right

             0.5f,  0.5f,  0.5f,        1.0f, 0.0f,         0.f, 1.f, 0.f,// front top right
            -0.5f,  0.5f,  0.5f,        0.0f, 0.0f,         0.f, 1.f, 0.f,// front top left
             0.5f,  0.5f, -0.5f,        1.0f, 1.0f,         0.f, 1.f, 0.f,// back  top right
            -0.5f,  0.5f, -0.5f,        0.0f, 1.0f,         0.f, 1.f, 0.f,// back  top left 
            -0.5f,  0.5f,  0.5f,        0.0f, 0.0f,         0.f, 1.f, 0.f,// front top left
             0.5f,  0.5f, -0.5f,        1.0f, 1.0f,         0.f, 1.f, 0.f,// back  top right

             0.5f, -0.5f,  0.5f,        1.0f, 1.0f,         0.f, -1.f, 0.f,// front bottom right
             0.5f, -0.5f, -0.5f,        1.0f, 0.0f,         0.f, -1.f, 0.f,// back  bottom right
            -0.5f, -0.5f,  0.5f,        0.0f, 1.0f,         0.f, -1.f, 0.f,// front bottom left
            -0.5f, -0.5f,  0.5f,        0.0f, 1.0f,         0.f, -1.f, 0.f,// front bottom left
             0.5f, -0.5f, -0.5f,        1.0f, 0.0f,         0.f, -1.f, 0.f,// back  bottom right
            -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,         0.f, -1.f, 0.f,// back  bottom left

             0.5f,  0.5f,  0.5f,        0.0f, 1.0f,         1.f, 0.f, 0.f,// front top right
             0.5f,  0.5f, -0.5f,        1.0f, 1.0f,         1.f, 0.f, 0.f,// back  top right
             0.5f, -0.5f,  0.5f,        0.0f, 0.0f,         1.f, 0.f, 0.f,// front bottom right
             0.5f,  0.5f, -0.5f,        1.0f, 1.0f,         1.f, 0.f, 0.f,// back  top right
             0.5f, -0.5f,  0.5f,        0.0f, 0.0f,         1.f, 0.f, 0.f,// front bottom right
             0.5f, -0.5f, -0.5f,        1.0f, 0.0f,         1.f, 0.f, 0.f,// back  bottom right
             
            -0.5f,  0.5f, -0.5f,        0.0f, 1.0f,         -1.f, 0.f, 0.f,// back  top left 
            -0.5f,  0.5f,  0.5f,        1.0f, 1.0f,         -1.f, 0.f, 0.f,// front top left
            -0.5f, -0.5f,  0.5f,        1.0f, 0.0f,         -1.f, 0.f, 0.f,// front bottom left
            -0.5f,  0.5f, -0.5f,        0.0f, 1.0f,         -1.f, 0.f, 0.f,// back  top left 
            -0.5f, -0.5f,  0.5f,        1.0f, 0.0f,         -1.f, 0.f, 0.f,// front bottom left
            -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,         -1.f, 0.f, 0.f,// back  bottom left
        };
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (5 * sizeof(float)));
        glEnableVertexAttribArray(2);

        
        TextureFactory texFactory;
        tex = texFactory.getTexture("C:\\dev\\PowerGrid\\src\\games\\opengl_examples\\fish_eyes.jpg");
        glBindTexture(GL_TEXTURE_2D, tex);
    }

    void draw() {
        glUseProgram(shader.ID);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
};

#endif /* CUBE_H */