/**
 * Author: MoonPresident
 * Date: May 4th 2020
 * 
 * This class was made mostly for the purpose of trying out template.
 */


#ifndef SHAPES_H
#define SHAPES_H

#define ARRAY_2D 2
#define ARRAY_COLOR 3

void hardCodedTriangle(); 

template<std::size_t ArraySize> 
class Shape2D final {
    static const std::size_t verticeNum = ArraySize;
    GLfloat vertices[verticeNum][ARRAY_2D];
    GLfloat colors[verticeNum][ARRAY_COLOR];
public:
    Shape2D (
        GLfloat _vertices[verticeNum][ARRAY_2D], 
        GLfloat _colors[verticeNum][ARRAY_COLOR]
    ) {
        for(int i = 0; i < (int) verticeNum; i++) {
            for(int j = 0; j < ARRAY_COLOR; j++) {
                if(j < ARRAY_2D) {
                    vertices[i][j] = _vertices[i][j];
                }
                colors[i][j] = _colors[i][j];
            }
        }
//        copyArray(_vertices, vertices, verticeNum, ARRAY_2D);
//        copyArray(_colors, colors, verticeNum, ARRAY_COLOR);
    }
    
    Shape2D (
        GLfloat _vertices[verticeNum][ARRAY_2D]
    ) {
        
        //Fun new form of declaration.
        float LO {0};

        float r = static_cast <float> (LO + (rand()) / static_cast <float> (RAND_MAX / (1 - LO)));
        float g = static_cast <float> (LO + (rand()) / static_cast <float> (RAND_MAX / (1 - LO)));
        float b = static_cast <float> (LO + (rand()) / static_cast <float> (RAND_MAX / (1 - LO)));
        
        #ifdef DEBUG
        std::cout << r << " " << g << " " << b;
        #endif
        
        for(int i = 0; i < (int) verticeNum; i++) {
            colors[i][0] = r / i;
            colors[i][1] = g / i;
            colors[i][2] = b / i;

            for(int j = 0; j < ARRAY_COLOR; j++) {
                vertices[i][j] = _vertices[i][j];
            }
        }
    }
    
    void drawShape() {
        for(int i = 0; i < (int) verticeNum; i++) {
            glColor3f(colors[i][0], colors[i][1], colors[i][2]);
            glVertex3f(vertices[i][0], vertices[i][1], 0.f);
        }
    }
};




template<std::size_t ArraySize>
Shape2D<ArraySize> equilateralShape(float radius) {
    GLfloat vertices[ArraySize][ARRAY_2D];
    float arc = 2 * M_PI / ArraySize;
    std::cout << arc << std::endl;
    float position = arc;
    vertices[0][0] = radius;
    vertices[0][1] = 0.f;
    std::cout << vertices[0][0] << " " << vertices[0][1] << std::endl;
    for(int i = 1; i < ArraySize; i++) {
        vertices[i][0] = cos(position) * radius;
        vertices[i][1] = sin(position) * radius;
        
        std::cout << vertices[i][0] << " " << vertices[i][1] << std::endl;
        position += arc;
    }
    return Shape2D<ArraySize>(vertices);
}

#endif