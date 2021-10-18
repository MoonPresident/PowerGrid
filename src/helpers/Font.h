#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>

class Font {
public:

    struct Character {
        unsigned int TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };

    std::map<char, Character> Characters;
    
    FT_Library ft;
    FT_Face face;

    int status;

    int getStatus() { return status; }
    
    //Consider a move onto the better library with this for reference
    //https://github.com/justinmeiners/stb-truetype-example/blob/master/main.c
    //May not be a real possibility tho.
    Font(const char* fontPath) {
        status = 0;
        if(FT_Init_FreeType(&ft)) {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library." << std::endl;
            status = -1;
            return;
        }

        if(FT_New_Face(ft, fontPath, 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font." << std::endl;
            status = -1;
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, 48);

        if(FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph." << std::endl;
            status = -1;
            return;
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for(unsigned char c = 0; c < 128; c++) {
            if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYPE: Failed to load Glyph." << std::endl;
                continue;
            }

            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        // fread(ttf_buffer, 1, 1<<20, fopen(fontPath, "rb"));
        // stbtt_BakeFontBitmap(ttf_buffer, 0, charHeight, 
        //         temp_bitmap, alpha_bitmap_width, alpha_bitmap_height, 32, 96, cdata); 
        // //No guarantee this fits! ^^
        
        // glGenTextures(1, &ftex);
        // glBindTexture(GL_TEXTURE_2D, ftex);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, alpha_bitmap_width,alpha_bitmap_height, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
        
        // //Set parameters
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, -10);
        
        // float x = -0.f, y = -0.f;
        // char* textCharacter = "a";
        // stbtt_GetBakedQuad(cdata, 
        //     alpha_bitmap_width, 
        //     alpha_bitmap_height, 
        //     *textCharacter - 32, &x,&y,&q, 1
        // );//1=opengl & d3d10+,0=d3d9
        
        // for(int i = 0; i < 3; i++) {
        //     textIndices[i] = i;
        //     textIndices[i + 3] = i + 1;
        // }
    }

    void renderText(int program,
                    int location,
                    unsigned int VAO,
                    unsigned int VBO,
                    std::string text, 
                    float x, float y, float scale, 
                    glm::vec3 color)
    {
        // activate corresponding render state	
        glUseProgram(program);
        glUniform3f(location, color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = Characters[*c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },            
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }           
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    Font() : Font("c:/windows/fonts/times.ttf") {}
    
//    float textVertices[] = {
//        0.f,   0.f,   0.f,    q.s0, q.t1,
//        0.f,   0.05f, 0.f,    q.s0, q.t0,
//        0.05f, 0.f,   0.f,    q.s1, q.t1,
//        0.05f, 0.05f, 0.f,    q.s1, q.t0,
//    };

    //Freetype implementation
    
    
};

#endif /* FONT_H */