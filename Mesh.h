#pragma once
#include "Misc.h"
#include "SharedComponentBase.h"

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
    std::vector<Vertex>* vertices;
    std::vector<unsigned int>* triangles;
    std::size_t hash_code() { return _VAO; }

    /*  Functions  */

    unsigned int VAO();

    Mesh();
    
    ~Mesh();

    void Clear();

    void Set(std::vector<Vertex>* vertices, std::vector<unsigned int>* triangles);

    void RecalculateNormal();

private:
    /*  Render data  */
    unsigned int _VBO, _EBO, _VAO;
    /*  Functions    */
    // initializes all the buffer objects/arrays
    void SetupMesh();
};