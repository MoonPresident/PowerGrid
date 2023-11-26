#include <string>
#include <vector>

#include <glm.hpp>

#include "Shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    uint32_t id;
    std::string type;
};

//Todo:
//Make single VAO/VBO/EBO that is accessible everywhere for all things so
//that this can all be done in a single memcpy to the gpu. Or even streamed?

class Mesh {
public:
    using Vertices = std::vector<Vertex>;
    using Indices = std::vector<unsigned int>;
    using Textures = std::vector<Texture>;

    Mesh(Vertices vertices, Indices indices, Textures textures) {
        mVertices = vertices;
        mIndices = indices;
        mTextures = textures;

        setupMesh();
    }
    void Draw(Shader &shader);

private:
    uint32_t mVAO, mVBO, mEBO;

    void setupMesh() {
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);
        glGenBuffers(1, &mEBO);

        glBindVertexArray(mVAO)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data());
    
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    }

public:
    Vertices mVertices;
    Indices mIndices;
    Textures mTextures;
}