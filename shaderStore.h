/**
 * Author: MoonPresident
 * Date: January 31th 2020
 * 
 * Stores callbacks for GLFW functions.
 */
 
#ifndef SHADER_STORE_H
#define SHADER_STORE_H


#include "glad/glad.h"
#include "glfw3.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


class ShaderStore {
private:
    std::vector<GLuint> shaders;
public:
    ShaderStore();
    void addShader(std::string shaderPath, GLenum shaderType); 
    void deleteAll();
    void attachAll(GLuint program);
};


struct Program {
    GLuint ID;
    GLuint drawType;
    ShaderStore shaderStore;
};

#endif /* SHADER_STORE_H */