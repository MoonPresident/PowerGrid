


#ifndef FONT_H
#define FONT_H

//Text Rendering
#define STB_TRUETYPE_IMPLEMENTATION 1
#include "stb_truetype.h"

#include <ft2build.h>
#include FT_FREETYPE_H

class Font {
public:
    unsigned char ttf_buffer[1<<20];
    static const int alpha_bitmap_width = 960;
    static const int alpha_bitmap_height = alpha_bitmap_width;
    unsigned char temp_bitmap[alpha_bitmap_width * alpha_bitmap_height];
    stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
    GLuint ftex;
    stbtt_aligned_quad q;
    
    float textVertices[16];
    int textIndices[6];
    
    
    //Consider a move onto the better library with this for reference
    //https://github.com/justinmeiners/stb-truetype-example/blob/master/main.c
    //May not be a real possibility tho.
    Font(const char* fontPath, float charHeight) {
        fread(ttf_buffer, 1, 1<<20, fopen(fontPath, "rb"));
        stbtt_BakeFontBitmap(ttf_buffer, 0, charHeight, 
                temp_bitmap, alpha_bitmap_width, alpha_bitmap_height, 32, 96, cdata); 
        //No guarantee this fits! ^^
        
        glGenTextures(1, &ftex);
        glBindTexture(GL_TEXTURE_2D, ftex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, alpha_bitmap_width,alpha_bitmap_height, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
        
        //Set parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, -10);
        
        float x = -0.f, y = -0.f;
        char* textCharacter = "a";
        stbtt_GetBakedQuad(cdata, 
            alpha_bitmap_width, 
            alpha_bitmap_height, 
            *textCharacter - 32, &x,&y,&q, 1
        );//1=opengl & d3d10+,0=d3d9
        
        for(int i = 0; i < 3; i++) {
            textIndices[i] = i;
            textIndices[i + 3] = i + 1;
        }
    }
    
    Font(const char* fontPath) : Font(fontPath, 128.0) {}
    Font() : Font("c:/windows/fonts/times.ttf", 128.0) {}
    
//    float textVertices[] = {
//        0.f,   0.f,   0.f,    q.s0, q.t1,
//        0.f,   0.05f, 0.f,    q.s0, q.t0,
//        0.05f, 0.f,   0.f,    q.s1, q.t1,
//        0.05f, 0.05f, 0.f,    q.s1, q.t0,
//    };

    //Freetype implementation
    FT_Library ft;
    
    
};

#endif /* FONT_H */