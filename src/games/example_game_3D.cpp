#include "example_game_3D.h"

// #define SQRT_2 1.4142

#include "Camera.h"

#include "Text.h"

#include <numeric>
#include <array>

#include "TextureFactory.h"

#include "Shader.h"

#include "Cube.h"

// #ifndef STB_IMAGE_IMPLEMENTATION
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
// #endif

#define debug_getSquare
void getSquare(float square[], float width, int stride, int z_const = 0.f) {
    float half_width = width / 2;
    for(int i = 0; i < 4; i++) {
        square[stride * i    ] = half_width * ((i < 2) - (i >= 2));
        square[stride * i + 1] = half_width * (2 * (i % 2) - 1);
        square[stride * i + 2] = z_const;
    }
}

//#define debug_getCube
void getCube(float square[], float width, int stride) {
    float half_width = width / 2;
    for(int i = 0; i < 8; i++) {
        square[stride * i    ] = half_width * ((i < 4) - (i >= 4));
        square[stride * i + 1] = half_width * ((i % 4 < 2) - (i % 4 >= 2));
        square[stride * i + 2] = half_width * (2 * (i % 2) - 1);
    }
}

//#define debug_setVertexPointerFloat
void setVertexPointerFloat(std::vector<int> dataLayout) {
    //IMPORTANT: How to set up vertex attributes.
    /*
     * In order to pass things in with a vbo, you need to tell opengl what the data looks like.
     * In this case, the position is decribes as (x, y, x), each as 4 byte (32 bit) value.
     * this means a stride of 12, but and offset of zero as there is only vertices to worry about.
     * 
     * glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,    const void * pointer);
     */
    
    //Get total size, initialise offset variable and precalculate size in bytes for repeated use.
    int stride = std::accumulate(dataLayout.begin(), dataLayout.end(), 0);
    int offset = 0;
    int size = stride * sizeof(float);

    
    #ifdef debug_setVertexPointerFloat
    std::cout << "Stride: " << stride << std::endl;
    #endif
    
    //Loop
    for(int i = 0; i < dataLayout.size(); i++) {
        int step = dataLayout.at(i);
        
        #ifdef debug_setVertexPointerFloat
        std::cout << "Offset: " << offset << std::endl;
        std::cout << "Step: " << step << std::endl;
        #endif
        
        glVertexAttribPointer(i, step, GL_FLOAT, GL_FALSE, size, (void*) (offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += step;
    }
    
    #ifdef debug_setVertexPointerFloat
    std::cout << "Final Offset: " << offset << std::endl;
    #endif
}


ExampleGame3D::ExampleGame3D() = default;
ExampleGame3D::~ExampleGame3D() = default;

void ExampleGame3D::run() {
    floorEnabled = false;
    initExplorableSimulation();
    GLuint VAO, VBO, VAO1, VBO1, EBO, EBO1;

    float moveSpeed = 5.f;
    float jumpVelocity = 2.8f;

    const char* vertShaderPath = R"(C:\dev\PowerGrid\resources\shaders\transform_3d_vertex_shader.txt)";
    const char* fragShaderPath = R"(C:\dev\PowerGrid\resources\shaders\texture_2d_fragment_shader.txt)";
    std::vector<Shader> programs = { Shader(vertShaderPath, fragShaderPath) };
    
    Cube cub;
    auto mod = glm::mat4(1.0f);
    mod = glm::translate(mod, glm::vec3(1.f, 1.f, 1.f));
    mod = glm::rotate(mod, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));
    glUseProgram(cub.shader.ID);
    int mLoc = glGetUniformLocation(cub.shader.ID, "model");
    int vLoc = glGetUniformLocation(cub.shader.ID, "view");
    int pLoc = glGetUniformLocation(cub.shader.ID, "projection");
    int ambientLightLoc = glGetUniformLocation(cub.shader.ID, "ambientLight");
    int colorLoc = glGetUniformLocation(cub.shader.ID, "colorIn");
    int offsetLoc = glGetUniformLocation(cub.shader.ID, "aOffset");
    int lightPosLoc = glGetUniformLocation(cub.shader.ID, "lightPos");
    int lightColorLoc = glGetUniformLocation(cub.shader.ID, "lightColor");
    int viewPosLoc = glGetUniformLocation(cub.shader.ID, "viewPos");
    

    /**
     * LEARN OPENLGL TUTORIAL
     * 
     * Extra reading
     * https://stackoverflow.com/questions/19636054/opengl-drawarrays-or-drawelements
     * 
     * Projection matrix notes:
     * https://www.songho.ca/opengl/gl_projectionmatrix.html
     * https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process
    **/
    
    float scale = 0.7f;
    float rot = 0.1f;
    std::array<float, 48> vertices = {
        0.f, 0.f, 0.f,      1.f, 1.f, rot,
        0.f, 0.f, 0.f,      1.f, 0.f, rot,
        0.f, 0.f, 0.f,      0.f, 1.f, rot,
        0.f, 0.f, 0.f,      0.f, 0.f, rot,
        0.f, 0.f, 0.f,      1.f, 1.f, rot,
        0.f, 0.f, 0.f,      1.f, 0.f, rot,
        0.f, 0.f, 0.f,      0.f, 1.f, rot,
        0.f, 0.f, 0.f,      0.f, 0.f, rot,
    };
    getCube(vertices.data(), scale, 6);
    
    float offset = 0.7f;
    std::array<float, 24> vertices1 = {
        0.3f + offset,  0.3f + offset, 0.f,       0.f, 0.f, rot,
        0.3f + offset,  0.2f + offset, 0.f,       1.f, 0.f, rot,
        0.2f + offset,  0.2f + offset, 0.f,       1.f, 1.f, rot,
        0.2f + offset,  0.3f + offset, 0.f,       0.f, 1.f, rot,
    };
    std::array<unsigned int, 36> indices = { 
        0, 1, 2,    1, 2, 3,    4, 5, 6,    5, 6, 7,
        0, 1, 4,    1, 4, 5,    2, 3, 6,    3, 6, 7,
        0, 2, 4,    2, 4, 6,    1, 3, 5,    3, 5, 7
    };
    
    //Arrays:
    //You can check if arrays are generated or not using gllsVertexArray
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
    
    {
        std::vector<int> vboLayout = {3, 2, 1};
        setVertexPointerFloat(vboLayout);
    }
    
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1.data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
    
    {
        std::vector<int> vboLayout = {3, 2, 1};
        setVertexPointerFloat(vboLayout);
    }
    
    //A VAO is used to store the Vertex Attrib pointer so you don't have to recall it every time.
    //It lets you simply rebind a VAO instead of redoing a vertexattribpointer call. Cool.
    unsigned int texture;
    TextureFactory texFactory;
    texture = texFactory.getTexture("C:/dev/PowerGrid/resources/textures/stock_images/binocupede.jpg");
    
    if(texture)  {} else {
        std::cout << "Image loading gone wrong" << std::endl;
    }
    
    float yaw = -90.f;
    float pitch = 0.f;
    
    
    glm::vec3 force_vector(0.f, 0.f, 0.f); //x, y, z
    float pc_z_pos = 0.f;
    while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window.getWindow()) == 0) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        stepThrough();
        
        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(programs.front().ID);
        
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.01f), glm::vec3(0.5f, 1.0f, 0.f));
        int modelLoc = glGetUniformLocation(programs.front().ID, "model");
        int viewLoc = glGetUniformLocation(programs.front().ID, "view");
        int projectionLoc = glGetUniformLocation(programs.front().ID, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(camera.model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.projection));

        //The last element buffer object that gets bound while a VAO is bound gets stred as that VAO's element
        //Buffer object.
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glUseProgram(cub.shader.ID);
        glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mod));
        glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(camera.view));
        glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(camera.projection));
        glUniform1f(ambientLightLoc, 0.1f);
        glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(1.f, 1.f, 1.f, 1.f)));
        glUniform3fv(offsetLoc, 1, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(glm::vec3(1.2, 1.f, 2.f)));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(glm::vec3(1.f, 1.f, 1.0f)));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.cameraPos));
        cub.draw();


        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }  
    
    //Close up shop
    for(auto program: programs) {
        glDeleteProgram(program.ID);
    }
    
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    glfwTerminate();
    std::cout << "Program successfully terminated." << std::endl;
}