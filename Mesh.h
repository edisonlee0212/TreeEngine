#ifndef MESH_H
#define MESH_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/include/glad/glad.h>
#include <cstddef>

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

class Mesh : SharedComponentBase{
public:
    /*  Mesh Data  */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> triangles;
    std::size_t hash_code() { return _VAO; }

    /*  Functions  */
    // constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> triangles) : vertices(vertices), triangles(triangles), SharedComponentBase()
    {
        _VAO = 0;
        _EBO = 0;
        _VBO = 0;
    }

    unsigned int VAO() {
        if (_VAO == 0) SetupMesh();
        return _VAO;
    }

    Mesh() {
        vertices = std::vector<Vertex>();
        triangles = std::vector<unsigned int>();
    } 

    void Set(std::vector<Vertex>* vertices, std::vector<unsigned int>* triangles) {
        this->vertices.clear();
        this->triangles.clear();
        int size = triangles->size() / 3;
        for (int i = 0; i < size; i++) {
            this->vertices.push_back(vertices->at(triangles->at(3 * i)));
            this->vertices.push_back(vertices->at(triangles->at(3 * i + 1)));
            this->vertices.push_back(vertices->at(triangles->at(3 * i + 2)));
            this->triangles.push_back(3 * i);
            this->triangles.push_back(3 * i + 1);
            this->triangles.push_back(3 * i + 2);
        }
        SetupMesh();
    }

    void RecalculateNormal() {
        if (_VAO == 0) return;
        size_t size = vertices.size();
        for (size_t i = 0; i < size / 3; i++) {
            auto v1 = vertices[3 * i];
            auto v2 = vertices[3 * i + 1];
            auto v3 = vertices[3 * i + 2];
            v1.Normal = v2.Normal = v3.Normal = glm::cross(v1.Position - v2.Position, v1.Position - v3.Position);
            vertices[3 * i] = v1;
            vertices[3 * i + 1] = v2;
            vertices[3 * i + 2] = v3;
        }
        SetupMesh();
    }

private:
    /*  Render data  */
    unsigned int _VBO, _EBO, _VAO;
    /*  Functions    */
    // initializes all the buffer objects/arrays
    void SetupMesh()
    {
        if (_VAO != 0) {
            glDeleteVertexArrays(1, &_VAO);
            glDeleteBuffers(1, &_VBO);
            glDeleteBuffers(1, &_EBO);
        }
        // create buffers/arrays
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);

        glBindVertexArray(_VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned int), &triangles[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        
        glBindVertexArray(0);
    }
};


#endif MESH_H
