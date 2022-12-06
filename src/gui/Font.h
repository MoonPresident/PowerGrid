#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>

#include "glad/glad.h"
#include <glm.hpp>

class Font {
public:

    FT_Library ft;
    FT_Face face;

    int status;

    struct Character {
        unsigned int TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };

    std::map<char, Character> Characters;

    Font(const char* fontPath);
    int getStatus();
};

#endif /* FONT_H */