#ifndef MODELMANAGER_H
#define MODELMANAGER_H


#include <glad/include/glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class ModelManager
{
public:
    ModelManager()
    {
        entities = std::vector<Entity*>();
    }

    static void LoadModel(Entity*, Shader* shader, string const&, bool);
private:
    static std::vector<Entity*> entities;
    static void ProcessNode(string, Shader* shader, Entity*, vector<Texture>*, aiNode*, const aiScene*);
    static Entity* ReadMesh(string, Shader* shader, vector<Texture>* texturesLoaded, aiMesh* mesh, const aiScene* scene);
    static std::vector<Texture> LoadMaterialTextures(string, vector<Texture>* texturesLoaded, aiMaterial* mat, aiTextureType type, string typeName);
};

std::vector<Entity*> ModelManager::entities = std::vector<Entity*>();

void ModelManager::LoadModel(Entity* root, Shader* shader, string const& path, bool gamma = false) {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    // retrieve the directory path of the filepath
    string directory = path.substr(0, path.find_last_of('/'));
    vector<Texture>* texturesLoaded = new vector<Texture>();
    ProcessNode(directory, shader, root, texturesLoaded, scene->mRootNode, scene);
}

void ModelManager::ProcessNode(string directory, Shader* shader, Entity* _Parent, vector<Texture>* texturesLoaded, aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        auto entity = ReadMesh(directory, shader, texturesLoaded, mesh, scene);
        entities.push_back(entity);
        entity->_Parent = _Parent;
        entity->GetTransform()->SetLocalToWorld(entity->_Parent->GetTransform()->GetLocalToWorld() * entity->GetTransform()->GetLocalToParent());
        entity->ToDraw = true;
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(directory, shader, _Parent, texturesLoaded, node->mChildren[i], scene);
    }
}

Entity* ModelManager::ReadMesh(string directory, Shader* shader, vector<Texture>* texturesLoaded, aiMesh* mesh, const aiScene* scene) {
    Entity* entity = World::entityManager->CreateEntity();
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    // Walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's _Faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    entity->mesh = new Mesh(vertices, indices);
    entity->material = new Material();
    entity->material->shader = shader;
    vector<Texture>* textures = &(entity->material->textures);
    vector<Texture> diffuseMaps = LoadMaterialTextures(directory, texturesLoaded, material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures->insert(textures->end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = LoadMaterialTextures(directory, texturesLoaded, material, aiTextureType_SPECULAR, "texture_specular");
    textures->insert(textures->end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = LoadMaterialTextures(directory, texturesLoaded, material, aiTextureType_HEIGHT, "texture_normal");
    textures->insert(textures->end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = LoadMaterialTextures(directory, texturesLoaded, material, aiTextureType_AMBIENT, "texture_height");
    textures->insert(textures->end(), heightMaps.begin(), heightMaps.end());
    return entity;
}
vector<Texture> ModelManager::LoadMaterialTextures(string directory, vector<Texture>* texturesLoaded, aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < texturesLoaded->size(); j++)
        {
            if (std::strcmp(texturesLoaded->at(j).Path().c_str(), str.C_Str()) == 0)
            {
                textures.push_back(texturesLoaded->at(j));
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.LoadTexture(str.C_Str(), directory);
            textures.push_back(texture);
            texturesLoaded->push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}


#endif MODELMANAGER_H