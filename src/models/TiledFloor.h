#ifndef TILED_FLOOR_H
#define TILED_FLOOR_H

#include "Shader.h"
#include "TextureFactory.h"

#include "glad/glad.h"
#include "glm.hpp"

class TiledFloor {
public:
    GLuint vao, vbo, ebo, tex;
    Shader shader;
    glm::mat4 proj, model, view;
    GLfloat ambientLight;

    TiledFloor(): shader(
            "C:\\dev\\PowerGrid\\resources\\shaders\\simple_colorable.vs",
            "C:\\dev\\PowerGrid\\resources\\shaders\\simple_colorable.fs"
        ) {
        ambientLight = 0.9f;
        glGenVertexArrays(1, &vao);        
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        
        glBindVertexArray(vao);
        glEnable(GL_DEPTH_TEST);

        
        static const GLfloat vertexData[] = {
            0.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            1.f, 0.f, 0.f,
            1.f, 0.f, 1.f,
        };
        
        unsigned int indices[] = {
            0, 1, 3,
            0, 3, 2,
        };
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);
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
        glUniform1f(ambientLightLoc, 1.f);

        glBindVertexArray(vao);
        int colorLoc = glGetUniformLocation(shader.ID, "colorIn");
        int offLoc = glGetUniformLocation(shader.ID, "aOffset");

//This works but chugs the framerate, either make it small or put it into a shader.
        int size = 200.f;
        glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(1.f, 1.f, 1.f, 1.f)));
        for(float i = -size; i < size;  i += 2.f) {
            for(float j = -size + 1; j < size; j += 2.f) {
                glUniform3fv(offLoc, 1, glm::value_ptr(glm::vec3(i, 0.f, j)));
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }
        
        for(float i = -size + 1.f; i < size;  i += 2.f) {
            for(float j = -size; j < size; j += 2.f) {
                glUniform3fv(offLoc, 1, glm::value_ptr(glm::vec3(i, 0.f, j)));
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }

        glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(0.f, 0.f, 0.f, 1.f)));
        for(float i = -size; i < size;  i += 2.f) {
            for(float j = -size; j < size; j += 2.f) {
                glUniform3fv(offLoc, 1, glm::value_ptr(glm::vec3(i, 0.f, j)));
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }
        
        for(float i = -size + 1.f; i < size;  i += 2.f) {
            for(float j = -size + 1.f; j < size; j += 2.f) {
                glUniform3fv(offLoc, 1, glm::value_ptr(glm::vec3(i, 0.f, j)));
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }
    }
};

#endif /* TILED_FLOOR_H */