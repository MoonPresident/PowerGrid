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
    glm::mat4 proj, model, view;
    GLfloat ambientLight;

    Cube(): shader(
            "C:\\dev\\PowerGrid\\resources\\shaders\\transform_3d_vertex_shader.txt",
            "C:\\dev\\PowerGrid\\resources\\shaders\\phong_texture_fragment_shader.txt"
        ) {
        ambientLight = 0.9f;
        glGenVertexArrays(1, &vao);        
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        
        glBindVertexArray(vao);
        glEnable(GL_DEPTH_TEST);

        
        static const GLfloat vertexData[] = {
             0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // front top right
             0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // front bottom right
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // front bottom left
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // front top left 
             0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // back  top right
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // back  bottom right
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // back  bottom left
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // back  top left 
        };
        
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3,
            4, 5, 7,
            5, 6, 7,
            
            0, 4, 3,
            4, 7, 3,
            1, 5, 2,
            5, 2, 6,
            
            0, 4, 1,
            4, 5, 1,
            3, 7, 2,
            7, 6, 2,
        };
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        TextureFactory texFactory;
        tex = texFactory.getTexture("C:\\dev\\PowerGrid\\src\\games\\opengl_examples\\fish_eyes.jpg");
        glBindTexture(GL_TEXTURE_2D, tex);
    }

    void setAmbientLight(float _a) { ambientLight = _a; }

    void setMats(glm::mat4 _model, glm::mat4 _view, glm::mat4 _proj) { model = _model; view = _view; proj = _proj;}

    void draw() {
        glUseProgram(shader.ID);
        int modelLoc = glGetUniformLocation(shader.ID, "model");
        int viewLoc = glGetUniformLocation(shader.ID, "view");
        int projLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        int ambientLightLoc = glGetUniformLocation(shader.ID, "ambientLight");
        glUniform1f(ambientLightLoc, ambientLight);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
};

#endif /* CUBE_H */