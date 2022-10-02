/**
 * Author: MoonPresident
 * Date: January 31th 2020
 * 
 * Stores callbacks for GLFW functions.
 */

//Include this everywhere
#include "config.h"
#include "my_debug.h"

#include "shaderStore.h"
#define SHADER_PATH         "C:/dev/PowerGrid/resources/shaders/"
#define SHADER_INDEX_FILE   "C:/dev/PowerGrid/resources/shaders/index.txt"


//Setup function
ShaderStore::ShaderStore () {
    #if defined debug_all || defined debug_flow || defined debug_shaders
    std::cout << "ShaderStore activated" << std::endl;
    #endif
}

void ShaderStore::addShader(std::string shaderFilename, GLenum shaderType) {
    std::ifstream shaderFile(shaderFilename);
    
    if(!shaderFile) {
        std::cout << "Unable to open file: " << shaderFilename.c_str() <<  std::endl;
    } else {
        GLuint shader;
        shader = glCreateShader(shaderType);
        
        std::string fileContents;
        fileContents.assign(
            std::istreambuf_iterator<char>(shaderFile), 
            std::istreambuf_iterator<char>()
        );
        
        const char* shaderSource = fileContents.c_str();
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        
        
        #if defined debug_all || defined debug_shaders
        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        std::cout << "Compilation: " << success << " for shader " << shader << std::endl;
        if(!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout <<"ERROR COMPILING SHADER " << shader << ": " << infoLog << std::endl;
        }
        #endif
        
        shaders.push_back(shader);
    }
}

void ShaderStore::linkProgram(GLuint program) {
    attachAll(program);
    glLinkProgram(program);
    
    #if defined debug_all || defined debug_shaders
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    std::cout << "Compilation: " << success << " for program " << program << std::endl;
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout <<"ERROR COMPILING PROGRAM " << program << ": " << infoLog << std::endl;
    }
    #endif
    deleteAll();
}


//Attach all shaders to the program.
void ShaderStore::attachAll(GLuint program) {
    for(int i = 0; i < shaders.size(); i++) {
        glAttachShader(program, shaders.at(i));
    }
}

//Delete shaders
void ShaderStore::deleteAll() {
    std::for_each(std::begin(shaders), std::end(shaders), glDeleteShader);
    shaders.clear();
}


//https://thebookofshaders.com/07/

//Load in shaders
std::vector<Program> loadPrograms() {
    ShaderStore shaderStore;
    std::vector<Program> programs;
    std::string line, path, index(SHADER_INDEX_FILE);
    std::ifstream shaderIndex;
    shaderIndex.open(index);

    if(shaderIndex.fail()) std::cout << "BAD INDEX";
    
    //Debug information to confirm the shaders have loaded correctly.
    #if defined debug_all || defined debug_shaders
    std::cout << (shaderIndex ? "Reading shader index: " : "Failed to read: ") << index.c_str() << std::endl;
    #endif
    
    /* Iterate over the index file. The first characters determines the shader
     * type, the second character is a semicolon and the rest of the line is 
     * the files address.
     */
    
    while(getline(shaderIndex, line)) {
        #if defined debug_all || defined debug_shaders
        std::cout << "Program size: " << programs.size() << std::endl;
        #endif

        path.assign(SHADER_PATH).append(line.substr(2));
        char shaderType = line.at(0);
        switch(shaderType) {
            case 'p': {
                Program program;
                program.ID = glCreateProgram();
                program.drawType =  (line.at(1) == 'l') * GL_LINES + 
                                    (line.at(1) == 'f') * GL_TRIANGLE_FAN +
                                    (line.at(1) == 't') * GL_TRIANGLES;
                programs.push_back(program);
                break;
            }
            case 'v':
                programs.back().shaderStore.addShader(path, GL_VERTEX_SHADER);
                break;
            case 'f':
                programs.back().shaderStore.addShader(path, GL_FRAGMENT_SHADER);
            case '/':
                break;
            
            #if defined debug_all || defined debug_shaders
            default:
                std::cout << "ShaderType not recognised: " << shaderType << std::endl;
            #endif
        }
    }
    
    //Compile the shader programs, 1 program at a time
    for(auto program: programs) {
        program.shaderStore.attachAll(program.ID);
        glLinkProgram(program.ID);
        program.shaderStore.deleteAll();
    }
    return programs;
}