

#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H

//Debug
//#define debug_texture_factory

//class Texture {
//private:
//    
//public:
//    unsigned char* data;
//    
//    Texture(std::string image_path, int width, int height, int nrChannels) {
//        data = stbi_load(image_path.c_str(), width, height, nrChannels);
//    }
//}


class TextureFactory {
private:
    
public:
    TextureFactory();
    
    unsigned int getTexture(const char* image_path);
};

#endif /* TEXTURE_FACTORY_H */