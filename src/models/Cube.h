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
    glm::vec3 lightPos, lightColor, viewPos;
    GLfloat ambientLight;
    Cube(): Cube(
        "C:\\dev\\PowerGrid\\resources\\shaders\\transform_3d_vertex_shader.txt",
        "C:\\dev\\PowerGrid\\resources\\shaders\\phong_texture_fragment_shader.txt"
    ) {

    };

    Cube(const char* vertShaderPath, const char* fragShaderPath): 
          shader(vertShaderPath, fragShaderPath) 
        , ambientLight(0.9f)
    {

        glGenVertexArrays(1, &vao);        
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        
        glBindVertexArray(vao);
        glEnable(GL_DEPTH_TEST);

        
        static const GLfloat vertexData[] = {
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,      0.f, 0.f, 1.f,// front bottom left
             0.5f, -0.5f,  0.5f,   1.0f, 0.0f,      0.f, 0.f, 1.f,// front bottom right
             0.5f,  0.5f,  0.5f,   1.0f, 1.0f,      0.f, 0.f, 1.f,// front top right
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,      0.f, 0.f, 1.f,// front top left
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,      0.f, 0.f, 1.f,// front bottom left
             0.5f,  0.5f,  0.5f,   1.0f, 1.0f,      0.f, 0.f, 1.f,// front top right
             
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,      0.f, 0.f, -1.f,// back  bottom left
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,      0.f, 0.f, -1.f,// back  top left 
             0.5f,  0.5f, -0.5f,   1.0f, 1.0f,      0.f, 0.f, -1.f,// back  top right
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f,      0.f, 0.f, -1.f,// back  bottom right
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,      0.f, 0.f, -1.f,// back  bottom left
             0.5f,  0.5f, -0.5f,   1.0f, 1.0f,      0.f, 0.f, -1.f,// back  top right
             
             0.5f,  0.5f,  0.5f,   1.0f, 0.0f,      0.f, 1.f, 0.f,// front top right
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,      0.f, 1.f, 0.f,// front top left
             0.5f,  0.5f, -0.5f,   1.0f, 1.0f,      0.f, 1.f, 0.f,// back  top right
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,      0.f, 1.f, 0.f,// back  top left 
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,      0.f, 1.f, 0.f,// front top left
             0.5f,  0.5f, -0.5f,   1.0f, 1.0f,      0.f, 1.f, 0.f,// back  top right
             
             0.5f, -0.5f,  0.5f,   1.0f, 1.0f,      0.f, -1.f, 0.f,// front bottom right
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f,      0.f, -1.f, 0.f,// back  bottom right
            -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,      0.f, -1.f, 0.f,// front bottom left
            -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,      0.f, -1.f, 0.f,// front bottom left
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f,      0.f, -1.f, 0.f,// back  bottom right
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,      0.f, -1.f, 0.f,// back  bottom left
            
             0.5f,  0.5f,  0.5f,   0.0f, 1.0f,      1.f, 0.f, 0.f,// front top right
             0.5f,  0.5f, -0.5f,   1.0f, 1.0f,      1.f, 0.f, 0.f,// back  top right
             0.5f, -0.5f,  0.5f,   0.0f, 0.0f,      1.f, 0.f, 0.f,// front bottom right
             0.5f,  0.5f, -0.5f,   1.0f, 1.0f,      1.f, 0.f, 0.f,// back  top right
             0.5f, -0.5f,  0.5f,   0.0f, 0.0f,      1.f, 0.f, 0.f,// front bottom right
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f,      1.f, 0.f, 0.f,// back  bottom right
             
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,      -1.f, 0.f, 0.f,// back  top left 
            -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,      -1.f, 0.f, 0.f,// front top left
            -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,      -1.f, 0.f, 0.f,// front bottom left
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,      -1.f, 0.f, 0.f,// back  top left 
            -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,      -1.f, 0.f, 0.f,// front bottom left
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,      -1.f, 0.f, 0.f,// back  bottom left
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
    
    void setAmbientLight(float _a) { ambientLight = _a; }

    void setLightPos(glm::vec3 _lightPos) { lightPos = _lightPos; }
    void setLightColor(glm::vec3 _lightColor) { lightColor = _lightColor; }

    void setViewPos(glm::vec3 _viewPos) { viewPos = _viewPos; }

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

        int colorLoc = glGetUniformLocation(shader.ID, "colorIn");
        glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(1.f, 1.f, 1.f, 1.f)));

        int offsetLoc = glGetUniformLocation(shader.ID, "aOffset");
        glUniform3fv(offsetLoc, 1, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));

        int lightPosLoc = glGetUniformLocation(shader.ID, "lightPos");
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
        
        int lightColorLoc = glGetUniformLocation(shader.ID, "lightColor");
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
        
        int viewPosLoc = glGetUniformLocation(shader.ID, "lightColor");
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
};

#endif /* CUBE_H */