#include "glad/glad.h"
#include "glfw3.h"
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <array>
#include <thread>

#include "my_debug.h"

//Initial setup for window.
#define WINDOW_TITLE "BreakIn"
enum INITIAL {
    WIDTH = 960,
    HEIGHT = 960,
    X_OFF = 500,
    Y_OFF = 50
};

void basic_error_callback(int error, const char* description){
    fprintf(stderr, "%i: %s", error, description);
}

using namespace std::chrono;

int main(int argc, char** argv) {
    auto metric_startInit = steady_clock::now();
    //Init OpenGL
    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwSetErrorCallback(basic_error_callback);
    glfwWindowHint(GLFW_SAMPLES, 8); //Set up multisampling
    
    //Set OpenGL version.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    glfwWindowHint(GLFW_REFRESH_RATE, 120);
    GLFWwindow* window;
    if(/*fullscreen*/ 0) {
        const GLFWvidmode * mode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(
            mode->width,
            mode->height,
            WINDOW_TITLE,
            monitor, //<- does fullscreen
            nullptr
        );
    } else {
        window = glfwCreateWindow(
            INITIAL::WIDTH,
            INITIAL::HEIGHT,
            WINDOW_TITLE,
            nullptr, 
            nullptr
        );
        
        glfwSetWindowPos(window, INITIAL::X_OFF, INITIAL::Y_OFF);
    }

    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Glad crashed. Exiting." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    //Initalise buffers
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    GLuint vertShader, fragShader;
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();
    
    const char* vertShaderSource = "#version 430 core\n"
        "layout(location = 0) in vec2 aPos;\n"
        "layout(location = 1) in vec3 colorIn;\n"
        "layout(location = 2) uniform float xScale;\n"
        "layout(location = 3) uniform float yScale;\n"
        "out vec3 color;\n"
        "void main() {gl_Position = vec4(aPos.x * xScale, aPos.y * yScale, 0.0, 1.0);\n"
        "color = colorIn;}";
    glShaderSource(vertShader, 1, &vertShaderSource, nullptr);
    glCompileShader(vertShader);
    glAttachShader(program, vertShader);
    
    const char* fragShaderSource = "#version 430 core\n"
        "in vec3 color;\n"
        "out vec4 FragColor;\n"
        "void main() {FragColor = vec4(color, 1.0f);}";
    glShaderSource(fragShader, 1, &fragShaderSource, nullptr);
    glCompileShader(fragShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    check_program(program);

    /*****************************
    * Initialise data 
    *****************************/
    //Data:
    //6 vertices for the paddle
    //6 vertices for the ball
    //6 vertices per brick
    constexpr size_t rows = 6;
    constexpr size_t cols = 10;
    uint64_t bricks[1 + (rows * cols) / 64]; 
    //5 floats per vertex, 6 vertices per item, paddle + ball + row * cols
    constexpr size_t vertices = 5 * 6 * (2 + rows * cols);
    GLfloat vertexData[vertices];

    auto memcpySquare = [&vertexData](size_t v, GLfloat* data) {
        constexpr size_t vertices = 5 * 6;
        constexpr size_t bytes = vertices * sizeof(float); 
        memcpy(vertexData + vertices * v, data, bytes);
    };
    

    // Ball values
    constexpr GLfloat ballWidth = 0.025f;
    GLfloat ballVector[] = { 0.f, -0.03f };
    GLfloat ballCoords[] = { 0.f, 0.f };

    //Paddle values
    GLfloat paddleX = 0.0f;
    constexpr GLfloat paddleY = -0.925f;
    constexpr GLfloat paddleHalfHeight = 0.025f;
    constexpr GLfloat paddleTop = paddleY + paddleHalfHeight;
    constexpr GLfloat paddleBottom = paddleY - paddleHalfHeight;
    constexpr GLfloat paddleRGB[] = { 1.f, 0.5f, 0.f };
    constexpr GLfloat paddleHalfWidth = 0.15f;

    //Block values
    constexpr GLfloat yBase = 0.95f;
    constexpr GLfloat yInterval = 0.1f;
    constexpr GLfloat squareHeight = 0.05f;
    constexpr GLfloat xBase = 0.825f;
    constexpr GLfloat xInterval = 0.2f;
    constexpr GLfloat squareWidth = 0.15f;

    GLfloat top[rows];
    GLfloat bottom[rows];
    GLfloat left[cols];
    GLfloat right[cols];

    for(size_t i = 0; i < rows; i++) {
        GLfloat offsetY = i * yInterval;
        top[i] = yBase - offsetY;
        bottom[i] = yBase - squareHeight - offsetY;

        for(size_t j = 0; j < cols; j++) {
            GLfloat offsetX = j * xInterval;
            left[j] = xBase - offsetX;
            right[j] = xBase + squareWidth - offsetX;


            GLfloat square[] = {
                right[j], top[i],    0.2f, 0.4f, 0.2f,
                left[j],  top[i],    0.2f, 0.4f, 0.2f,
                right[j], bottom[i], 0.2f, 0.4f, 0.2f,
                right[j], bottom[i], 0.2f, 0.4f, 0.2f,
                left[j],  top[i],    0.2f, 0.4f, 0.2f,
                left[j],  bottom[i], 0.2f, 0.4f, 0.2f,
            };
            memcpySquare(i * cols + j, square);
        }
    }

    std::array<bool, rows * cols> blockExists;
    blockExists.fill(true);

    glUseProgram(program);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto frameTimestamp = steady_clock::now();
    milliseconds frameBound(1000);
    auto fps = 0;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    double mouseXPos = 1.f, mouseYPos = 1.f;
    glfwSetCursorPos(window, mouseXPos, mouseYPos);

    int winWidth, winHeight;
    glfwGetWindowSize(window, &winWidth, &winHeight);
    double xScale = 1.0 * winHeight / winWidth;
    double yScale = 1.0 * winWidth / winHeight;

    if(xScale > yScale) {
        xScale = 1.f;
    } else {
        yScale = 1.f;
    }
    
    auto metric_endInit = steady_clock::now();

    
    std::array<microseconds, 3> metrics;
    metrics.fill(milliseconds(0));
    int metricDivisor = 1;

    //This captures the escape key.
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    while(
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
        glfwWindowShouldClose(window) == 0) 
    {
        std::array<time_point<steady_clock>, 4> perf;
        auto stamp = [&](size_t i) {
            perf[i] = steady_clock::now();
        };

        stamp(0);

        if(frameBound > duration_cast<milliseconds>(steady_clock::now() - frameTimestamp)) {
            fps++;
        } else {
            frameTimestamp = steady_clock::now();
            std::cout << "fps: " << fps << "\n";
            fps = 0; 

            std::cout << "x: " << ballCoords[0] << ", \ty: " << ballCoords[1] << "\n";
        }

        //Poll inputs
        glfwPollEvents();
        glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

        stamp(1);

        paddleX = static_cast<float>(mouseXPos) / winWidth;
        
        GLfloat paddleLeft = paddleX - paddleHalfWidth;
        GLfloat paddleRight = paddleX + paddleHalfWidth;
        // paddle[ 0] = paddleLeft;
        // paddle[ 5] = paddleRight;
        // paddle[10] = paddleLeft;
        // paddle[15] = paddleLeft;
        // paddle[20] = paddleRight;
        // paddle[25] = paddleRight;

        GLfloat paddle[] = {
            paddleLeft,  paddleBottom, paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleRight, paddleBottom, paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleLeft,  paddleTop,    paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleLeft,  paddleTop,    paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleRight, paddleBottom, paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleRight, paddleTop,    paddleRGB[0], paddleRGB[1], paddleRGB[2],
        };

        //update ball
        auto prevX = ballCoords[0];
        auto prevY = ballCoords[1];
        ballCoords[0] = ballCoords[0] + ballVector[0];
        ballCoords[1] = ballCoords[1] + ballVector[1];
        
        bool paddleCollision = ballCoords[1] < paddleTop 
            && ballCoords[0] < paddleRight 
            && ballCoords[0] > paddleLeft;
        bool sideWallCollision = ballCoords[0] > 1.f || ballCoords[0] < -1.f; 
        bool backWallCollision = ballCoords[1] > 1.f;
        bool gameOver = ballCoords[1] < -1.f;


        //Collision checks
        if(paddleCollision) {
            std::cout << "PADDLE\n";
            auto angle = (ballCoords[0] - paddleLeft) / (paddleHalfWidth);
            ballVector[0] = 0.024f * (angle - 1.f);
            ballVector[1] = 0.006f + 0.024f * (1.f - std::abs(1.f - angle));
        } else if(sideWallCollision) {
            std::cout << "SIDE\n";
            ballVector[0] = -ballVector[0];
        } else if (backWallCollision) {
            std::cout << "BACK\n";
            ballVector[1] = -ballVector[1];
        } else if (gameOver) {
            ballVector[1] = -ballVector[1];
            //GAME OVER!
            std::cout << "GAME OVER\n";
            break;
        } else {
            
            //Check for collision with block
            int rowOverlap = -1;
            int colOverlap = -1;
            auto top = yBase + ballWidth + yInterval;
            auto height = 2 * ballWidth + squareHeight;
            auto bottom = yBase - ballWidth - squareHeight + yInterval;
            auto left = xBase - ballWidth + xInterval;
            auto width = 2 * ballWidth + squareWidth;
            auto right = xBase + ballWidth + squareWidth + xInterval;

            for(size_t i = 0; rowOverlap == -1 && i < rows; i++) {
                top -= yInterval;
                bottom -= yInterval;

                if(ballCoords[1] < top && ballCoords[1] > top - height) {
                    rowOverlap = i;
                }
            }

            for(size_t i = 0; colOverlap == -1 && i < cols; i++) {
                left -= xInterval;
                right -= xInterval;

                if(ballCoords[0] > left && ballCoords[0] < left + width) {
                    colOverlap = i;
                }
            }

            if(rowOverlap > -1 && colOverlap > -1 
                    && blockExists[rowOverlap * cols + colOverlap]) {
                std::cout << "BLOCK: " << rowOverlap << ", " << colOverlap << "\n";
                blockExists[rowOverlap * cols + colOverlap] = false;

                GLfloat m = ballVector[1] / ballVector[0];
                GLfloat c = ballCoords[1] - m * ballCoords[0];

                //y = mx + c
                auto leftInt = m * left + c;
                auto rightInt = m * right + c;

                if((ballVector[0] > 0.f && left < ballCoords[0]  && left > prevX) ||
                        (ballVector[0] < 0.f && right < prevX && right > ballCoords[0])) {
                    ballVector[0] = -ballVector[0];
                } else {
                    ballVector[1] = -ballVector[1];
                }

                
                std::cout << ballVector[0] << ", " << ballVector[1] << "\n";
                std::cout << top << ", " << bottom << ", " << prevX << ", " << ballCoords[0] << "\n";
                std::cout << leftInt << ", " << rightInt << ", " << m << ", " << c << "\n";


                GLfloat square[] = {
                    -100.f, -100.f, 0.2f, 0.4f, 0.2f,
                    -100.f, -100.f, 0.2f, 0.4f, 0.2f,
                    -100.f, -100.f, 0.2f, 0.4f, 0.2f,
                    -100.f, -100.f, 0.2f, 0.4f, 0.2f,
                    -100.f, -100.f, 0.2f, 0.4f, 0.2f,
                    -100.f, -100.f, 0.2f, 0.4f, 0.2f,
                };

                memcpySquare(rowOverlap * cols + colOverlap, square);
            }
        }

         
        GLfloat ball[] = {
            ballCoords[0] - ballWidth, ballCoords[1] + ballWidth, 1.f, 0.5f, 0.f,
            ballCoords[0] + ballWidth, ballCoords[1] + ballWidth, 1.f, 0.5f, 0.f,
            ballCoords[0] - ballWidth, ballCoords[1] - ballWidth, 1.f, 0.5f, 0.f,
            ballCoords[0] - ballWidth, ballCoords[1] - ballWidth, 1.f, 0.5f, 0.f,
            ballCoords[0] + ballWidth, ballCoords[1] + ballWidth, 1.f, 0.5f, 0.f,
            ballCoords[0] + ballWidth, ballCoords[1] - ballWidth, 1.f, 0.5f, 0.f,
        };

        memcpySquare(rows * cols, paddle);
        memcpySquare(rows * cols + 1, ball);

        //draw triangles.
        glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);
        glUniform1f(2, xScale);
        glUniform1f(3, yScale);
        
        glDrawArrays(GL_TRIANGLES, 0, (rows * cols + 2) * 6);
        
        stamp(2);
        glfwSwapBuffers(window);
        stamp(3);

        auto duration = [&](size_t i) {
            return duration_cast<microseconds>(perf[i + 1] - perf[i]);
        };

        for(int i = 0; i < 3; i++) {
            metrics[i] += duration(i);
        }

        metricDivisor++;
    }

    metrics[0] /= metricDivisor;
    metrics[1] /= metricDivisor;
    metrics[2] /= metricDivisor;

    auto total = metrics[0] + metrics[1] + metrics[2];
    std::cout << "Total: " << total.count() << "\n";
    std::cout << "GLFW:  " << ((100.0 * metrics[0].count()) / total.count()) << "%" << " - " << metrics[0].count() << "\n";
    std::cout << "Phys:  " << ((100.0 * metrics[1].count()) / total.count()) << "%" << " - " << metrics[1].count() << "\n";
    std::cout << "OpGL:  " << ((100.0 * metrics[2].count()) / total.count()) << "%" << " - " << metrics[2].count() << "\n";
    
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    return 0;
}