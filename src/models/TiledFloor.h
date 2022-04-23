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
        
        glBindVertexArray(vao);
        glEnable(GL_DEPTH_TEST);
                
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
        int sideLength = 4;
        
        //Length is 2 * sideLength, 2 triangles per squares, only half in each colour
        // triCount * sideLength * sideLength = 2 * (2 * sideLength) * (2 * sideLength) / 2
        int triangleCount = 6 * sideLength * sideLength;

        int squareStride = 36;
        std::vector<GLfloat> verts(squareStride * triangleCount);

        glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(1.f, 1.f, 1.f, 1.f)));
        glUniform3fv(offLoc, 1, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));
        for(int i = 0; i < sideLength;  ++i) {
            static const int columnOffset = i * sideLength * squareStride;
            for(int j = 0; j < sideLength; ++j) {
                float xBase = 2.f * i - sideLength;
                float zBase = 2.f * j - sideLength;
                std::cout << "(" << xBase << ", " << zBase << ") \t";
                static const GLfloat vertexDataA[] = {
                    xBase,       0.f, zBase,
                    xBase,       0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase,
                    xBase,       0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase,
                    ++xBase,     0.f, ++zBase,
                    xBase,       0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase,
                    xBase,       0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase,
                };
                verts.insert(verts.begin() + j * squareStride + columnOffset, &vertexDataA[0], &vertexDataA[squareStride]);
            }
            std::cout << std::endl;
        }
        for(int i = 0; i <squareStride*sideLength; i+=3) {
            std::cout << verts.at(i) << ", " << verts.at(i + 1) << ", " << verts.at(i+2) << std::endl;
        }
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 6 *triangleCount);

        glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(0.f, 0.f, 0.f, 1.f)));
        for(int i = 0; i < 2 * sideLength;  ++i) {
            for(int j = 0; j < 2 * sideLength; ++j) {
                float xBase = 2.f * i - sideLength + 1;
                float zBase = 2.f * j - sideLength;
                std::cout << "(" << xBase << ", " << zBase << ")  \t";
                static const GLfloat vertexDataA[] = {
                    xBase,       0.f, zBase,
                    xBase,       0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase,
                    xBase,       0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase,
                    ++xBase,     0.f, ++zBase,
                    xBase,       0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase,
                    xBase,       0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase + 1.f,
                    xBase + 1.f, 0.f, zBase,
                };
                verts.insert(verts.begin() + 2 * i * squareStride, &vertexDataA[0], &vertexDataA[squareStride]);
            }
            std::cout << std::endl;
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 6 *triangleCount);
    }
};

#endif /* TILED_FLOOR_H */