/**
 * Author: MoonPresident
 * Date: January 31th 2020
 * 
 * Stores callbacks for GLFW functions.
 */

#include "shaderStore.h"

//Setup function
ShaderStore::ShaderStore (){
    std::cout << "ShaderStore activated" << std::endl;//shaders.data();
}


//Add shader to the store.
void ShaderStore::addShader(std::string shaderPath, GLenum shaderType) {
    //Open and read stream
    std::ifstream shaderFile;
    shaderFile.open(shaderPath.c_str());
    
    if(shaderFile) {
        //Init shader
        GLuint shader;
        shader = glCreateShader(shaderType);
        
        //Read in file contents
        std::string fileContents;
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


//Attach all shaders to the program.
void ShaderStore::attachAll(GLuint program) {
    for(int i = 0; i < shaders.size(); i++) {
//        std::cout << i << " : " << shaders.at(i) << std::endl;
        glAttachShader(program, shaders.at(i));
    }
}

//Delete shaders
void ShaderStore::deleteAll() {
    std::for_each(std::begin(shaders), std::end(shaders), glDeleteShader);
    shaders.clear();
}


//https://thebookofshaders.com/07/
#define SHADER_PATH         "..\\resources\\shaders\\"
#define SHADER_INDEX_FILE   "..\\resources\\shaders\\index.txt"

//Load in shaders
std::vector<Program> loadPrograms() {
    ShaderStore shaderStore;
    std::vector<Program> programs;
    std::string line, path, index(SHADER_INDEX_FILE);
    std::ifstream shaderIndex;
    shaderIndex.open(index);
    
    //Debug information to confirm the shaders have loaded correctly.
    #ifdef debug
    cout << (shaderIndex ? "Shader opened: " : "Shader failed: ") << index.c_str() << endl;
    #endif
    
    /* Iterate over the index file. The first characters determines the shader
     * type, the second character is a semicolon and the rest of the line is 
     * the files address.
     */
     
    while(getline(shaderIndex, line)) {
        #ifdef debug
        std::cout << "Line in: " << line << std::endl;
        #endif
        std::cout << programs.size() << std::endl;
        path.assign(SHADER_PATH).append(line.substr(2));
        char shaderType = line.at(0);
        switch(shaderType) {
            case 'p': {
                Program program;
                program.ID = glCreateProgram();
                program.drawType = (line.at(1) == 'l') * GL_LINES + (line.at(1) == 'f') * GL_TRIANGLE_FAN;
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
            
            #ifdef debug

            default:
                cout << "ShaderType not recognised: " << shaderType << endl;
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