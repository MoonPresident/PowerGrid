#ifndef SHADER_H
#define SHADER_H

#include "my_debug.h"

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <iostream>

/**
 * Actually a Shader Program with subshaders but thats splitting hairs.
 */
class Shader
{
public:
    unsigned int ID;
    
    Shader() {};

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) {
        ID = glCreateProgram();
        GLuint vertShader = getShader(vertexPath, GL_VERTEX_SHADER);
        GLuint fragShader = getShader(fragmentPath, GL_FRAGMENT_SHADER);
        GLuint geomShader;

        glAttachShader(ID, vertShader);
        glAttachShader(ID, fragShader);
        // if geometry shader is given, compile geometry shader
        if(geometryPath != nullptr) { 
            geomShader = getShader(geometryPath, GL_GEOMETRY_SHADER); 
            glAttachShader(ID, geomShader);
        }
        glLinkProgram(ID);

        #if defined debug_all || defined debug_shaders
        {
            GLint success;
            GLchar infoLog[1024];
            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(ID, 1024, nullptr, infoLog);
                std::cout << "Error Linking Program:" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        #endif

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        if(geometryPath != nullptr)
            glDeleteShader(geomShader);
    }

    GLuint getShader(const char* vertexPath, GLenum shaderType) {
        GLuint shader = glCreateShader(shaderType);
        std::ifstream shaderFile(vertexPath);
        if(!shaderFile)
            throw std::runtime_error("Runtime error reading shader.");

        std::string fileContents;
        fileContents.assign(
            std::istreambuf_iterator<char>(shaderFile), 
            std::istreambuf_iterator<char>()
        );
        const char* shaderSource = fileContents.c_str();
        glShaderSource(shader, 1, &shaderSource, nullptr);

        glCompileShader(shader);
        
        #if defined debug_all || defined debug_shaders
        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        std::cout << "Compilation for shader type " << shaderType << ": " << success << " for shader " << shader << "\n";
        if(!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout <<"ERROR COMPILING SHADER " << shader << " OF TYPE " << shaderType << ": " << infoLog << "\n";
        }
        #endif

        shaderFile.close();
        return shader;
    }
};
#endif /* SHADER_H */

