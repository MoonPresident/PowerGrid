/**
 * Author: MoonPresident
 * Date: January 31th 2020
 * 
 * Stores callbacks for GLFW functions.
 */

#include "shaderStore.h"


ShaderStore::ShaderStore (){
    std::cout << "ShaderStore activated" << std::endl;//shaders.data();
}


void ShaderStore::addShader(std::string shaderPath, GLenum shaderType) {
    std::ifstream shaderFile;
    shaderFile.open(shaderPath.c_str());
    
    if(shaderFile) {
        GLuint shader;
        std::string fileContents;
        shader = glCreateShader(shaderType);
        
        fileContents.assign(
            std::istreambuf_iterator<char>(shaderFile), 
            std::istreambuf_iterator<char>()
        );
        
        const char* shaderSource = fileContents.c_str();

        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        
        std::cout << shader << std::endl;
        
        shaders.push_back(shader);
    } else {
        std::cout << "Unable to open file: " << shaderPath.c_str() <<  std::endl;
    }
}

void ShaderStore::attachAll(GLuint program) {
    for(int i = 0; i < shaders.size(); i++) {
        std::cout << i << " : " << shaders.at(i) << std::endl;
        glAttachShader(program, shaders.at(i));
    }
}

void ShaderStore::deleteAll() {
    std::for_each(std::begin(shaders), std::end(shaders), glDeleteShader);
    shaders.clear();
}