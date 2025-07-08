#include "glad/glad.h"
#include "glfw3.h"
#include <iostream>
#include <chrono>
#include <array>

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

auto main(int argc, char** argv) -> int {
    //Init OpenGL
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(basic_error_callback);
    glfwWindowHint(GLFW_SAMPLES, 8); //Set up multisampling
    
    //Set OpenGL version.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_REFRESH_RATE, 120);

    GLFWwindow* window;
    if(/*fullscreen*/ false) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
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
    constexpr size_t rows = 6;
    constexpr size_t cols = 10;
    constexpr size_t verticesPerBlock = 5 * 6;

    //5 floats per vertex, 6 vertices per item, paddle + ball + row * cols
    constexpr size_t vertices = verticesPerBlock * (2 + rows * cols);
    std::array<GLfloat, vertices> vertexData;

    auto memcpySquare = [&vertexData](size_t v, GLfloat* data) {
        constexpr size_t bytes = verticesPerBlock * sizeof(float); 
        memcpy(vertexData.data() + verticesPerBlock * v, data, bytes);
    };
    

    // Ball values
    constexpr GLfloat ballWidth = 0.025f;
    std::pair<GLfloat, GLfloat>  ballVec = { 0.f, -0.03f };
    std::pair<GLfloat, GLfloat>  ballLoc = { 0.f, 0.f };

    //Paddle values
    GLfloat paddleX = 0.0f;
    constexpr GLfloat paddleY = -0.925f;
    constexpr GLfloat paddleHalfHeight = 0.025f;
    constexpr GLfloat paddleTop = paddleY + paddleHalfHeight;
    constexpr GLfloat paddleBottom = paddleY - paddleHalfHeight;
    constexpr auto paddleRGB = std::to_array<GLfloat>({ 1.f, 0.5f, 0.f });
    constexpr GLfloat paddleHalfWidth = 0.15f;

    //Block values
    constexpr GLfloat yBase = 0.95f;
    constexpr GLfloat yInterval = 0.1f;
    constexpr GLfloat squareHeight = 0.05f;
    constexpr GLfloat xBase = 0.825f;
    constexpr GLfloat xInterval = 0.2f;
    constexpr GLfloat squareWidth = 0.15f;

    std::array<GLfloat, rows> top;
    std::array<GLfloat, rows> bottom;
    std::array<GLfloat, cols> left;
    std::array<GLfloat, cols> right;

    for(size_t i = 0; i < rows; i++) {
        top[i] = yBase - i * yInterval;
        bottom[i] = top[i] - squareHeight;
    }

    for(size_t j = 0; j < cols; j++) {
        left[j] = xBase - j * xInterval;
        right[j] = left[j] + squareWidth;
    }
    
    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < cols; j++) {
            auto square = std::to_array<GLfloat>({
                right[j], top[i],    0.2f, 0.4f, 0.2f,
                left[j],  top[i],    0.2f, 0.4f, 0.2f,
                right[j], bottom[i], 0.2f, 0.4f, 0.2f,
                right[j], bottom[i], 0.2f, 0.4f, 0.2f,
                left[j],  top[i],    0.2f, 0.4f, 0.2f,
                left[j],  bottom[i], 0.2f, 0.4f, 0.2f,
            });

            memcpySquare(i * cols + j, square.data());
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
        xScale = 1.0;
    } else {
        yScale = 1.0;
    }

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
        }

        //Poll inputs
        glfwPollEvents();
        glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

        stamp(1);

        paddleX = static_cast<float>(mouseXPos) / winWidth;
        
        GLfloat paddleLeft = paddleX - paddleHalfWidth;
        GLfloat paddleRight = paddleX + paddleHalfWidth;

        auto paddle = std::to_array<GLfloat>({
            paddleLeft,  paddleBottom, paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleRight, paddleBottom, paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleLeft,  paddleTop,    paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleLeft,  paddleTop,    paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleRight, paddleBottom, paddleRGB[0], paddleRGB[1], paddleRGB[2],
            paddleRight, paddleTop,    paddleRGB[0], paddleRGB[1], paddleRGB[2],
        });

        //update ball
        auto prevX = ballLoc.first;
        auto prevY = ballLoc.second;
        ballLoc.first = ballLoc.first + ballVec.first;
        ballLoc.second = ballLoc.second + ballVec.second;
        
        bool paddleCollision = ballLoc.second < paddleTop 
            && ballLoc.first < paddleRight 
            && ballLoc.first > paddleLeft;
        bool sideWallCollision = ballLoc.first > 1.f || ballLoc.first < -1.f; 
        bool backWallCollision = ballLoc.second > 1.f;
        bool gameOver = ballLoc.second < -1.f;

        //Collision checks
        if(paddleCollision) {
            auto angle = (ballLoc.first - paddleLeft) / (paddleHalfWidth);
            ballVec.first = 0.024f * (angle - 1.f);
            ballVec.second = 0.006f + 0.024f * (1.f - std::abs(1.f - angle));
        } else if(sideWallCollision) {
            ballVec.first = -ballVec.first;
        } else if (backWallCollision) {
            ballVec.second = -ballVec.second;
        } else if (gameOver) {
            ballVec.second = -ballVec.second;
            //GAME OVER!
            std::cout << "GAME OVER\n";
            break;
        } else {
            
            //Check for collision with block
            int rowOverlap = -1;
            int colOverlap = -1;

            for(size_t i = 0; rowOverlap == -1 && i < rows; i++) {
                if(ballLoc.second - ballWidth < top[i] 
                        && ballLoc.second + ballWidth > bottom[i]) {
                    rowOverlap = i;
                }
            }

            for(size_t i = 0; colOverlap == -1 && i < cols; i++) {
                if(ballLoc.first - ballWidth < right[i] 
                        && ballLoc.first + ballWidth > left[i]) {
                    colOverlap = i;
                }
            }

            auto offset = rowOverlap * cols + colOverlap;

            if(rowOverlap > -1 && colOverlap > -1 && blockExists[offset]) {
                blockExists[offset] = false;

                auto rightCollision = ballVec.first < 0.f 
                        && right[colOverlap] < prevX - ballWidth 
                        && right[colOverlap] > ballLoc.first - ballWidth;
                auto leftCollision = ballVec.first > 0.f 
                        && left[colOverlap] < ballLoc.first + ballWidth
                        && left[colOverlap] > prevX + ballWidth;
                
                if(rightCollision || leftCollision) {
                    ballVec.first = -ballVec.first;
                } else {
                    ballVec.second = -ballVec.second;
                }
                
                for(int i = offset * verticesPerBlock; 
                        i < (offset + 1) * verticesPerBlock; 
                        i += 5) {
                    vertexData[i] = -100.f;
                    vertexData[i + 1] = -100.f;
                }
            }
        }

        auto ball = std::to_array<GLfloat>({
            ballLoc.first - ballWidth, ballLoc.second + ballWidth, 1.f, 0.5f, 0.f,
            ballLoc.first + ballWidth, ballLoc.second + ballWidth, 1.f, 0.5f, 0.f,
            ballLoc.first - ballWidth, ballLoc.second - ballWidth, 1.f, 0.5f, 0.f,
            ballLoc.first - ballWidth, ballLoc.second - ballWidth, 1.f, 0.5f, 0.f,
            ballLoc.first + ballWidth, ballLoc.second + ballWidth, 1.f, 0.5f, 0.f,
            ballLoc.first + ballWidth, ballLoc.second - ballWidth, 1.f, 0.5f, 0.f,
        });

        memcpySquare(rows * cols, paddle.data());
        memcpySquare(rows * cols + 1, ball.data());

        //draw triangles.
        glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData.data(), GL_DYNAMIC_DRAW);
        glUniform1f(2, xScale);
        glUniform1f(3, yScale);
        
        glDrawArrays(GL_TRIANGLES, 0, (rows * cols + 2) * 6);
        
        stamp(2);
        glfwSwapBuffers(window);
        stamp(3);

        for(int i = 0; i < 3; i++) {
            metrics[i] += duration_cast<microseconds>(perf[i + 1] - perf[i]);
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