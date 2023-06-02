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


auto TextureFactory::getTexture(const char* image_path) -> unsigned int {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(image_path, &width, &height, &nrChannels, 0);

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    if(data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);

        //GL_NEAREST/LINEAR_MIPMAP_LINEAR/NEAREST
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture." << std::endl;
    }
    
    stbi_image_free(data);
    return tex;
}