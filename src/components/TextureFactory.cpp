#include <iostream>
#include <string>

#include "glad/glad.h"
#include "TextureFactory.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureFactory::TextureFactory () {
    #ifdef debug_all
    std::cout << "Texture factory created." << std::endl;
    #endif
    
    stbi_set_flip_vertically_on_load(true);
};


unsigned int TextureFactory::getTexture(const char* image_path) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(image_path, &width, &height, &nrChannels, 0);

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    
    //GL_NEAREST/LINEAR_MIPMAP_LINEAR/NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture." << std::endl;
    }
    
    stbi_image_free(data);
    return tex;
}