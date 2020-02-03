/**
 * Author: MoonPresident
 * Date: January 31th 2020
 * 
 * Stores callbacks for GLFW functions.
 */
 
#ifndef SHADER_STORE_H
#define SHADER_STORE_H

#include <main.h>

struct Shader {
    GLuint ID;
};

 
class ShaderStore {
private:
    std::vector<GLuint> shaders;
public:
    ShaderStore();
    void addShader(std::string shaderPath, GLenum shaderType); 
    void deleteAll();
    void attachAll(GLuint program);
};
 
 #endif /* SHADER_STORE_H */