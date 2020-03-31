#pragma once
#include "Misc.h"
class AssimpImporter {
public:
	static void LoadScene(Scene* destination, std::string const& path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            Debug::Error( "ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
            return;
        }
        // retrieve the directory path of the filepath
        std::string directory = path.substr(0, path.find_last_of('/'));
        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            aiMesh* amesh = scene->mMeshes[i];
            Mesh* mesh = new Mesh();
            ReadMesh(amesh, mesh);
            destination->mMeshes.push_back(mesh);
        }

        for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
            aiMaterial* amaterial = scene->mMaterials[i];
            Material* material = new Material();
            auto loadedTextures = &destination->mTextures;
            ReadMaterial(directory, amaterial, material, loadedTextures);
            destination->mMaterials.push_back(material);
        }
        ProcessNode(directory, scene->mRootNode, destination->mRootNode, scene);
	}
private:
    static void ProcessNode(std::string directory, aiNode* node, SceneNode* sceneNode, const aiScene* scene) {
        auto transform = node->mTransformation;
        sceneNode->mTransformation = glm::mat4(transform.a1, transform.a2, transform.a3, transform.a4, transform.b1, transform.b2, transform.b3, transform.b4, transform.c1, transform.c2, transform.c3, transform.c4, transform.d1, transform.d2, transform.d3, transform.d4);
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            sceneNode->mMeshesIndices.push_back(node->mMeshes[i]);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            auto n = new SceneNode(sceneNode);
            sceneNode->mChildren.push_back(n);
            ProcessNode(directory, node->mChildren[i], n, scene);
        }
    }

    static void ReadMesh(aiMesh* src, Mesh* dest) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // Walk through each of the mesh's vertices
        for (unsigned int i = 0; i < src->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = src->mVertices[i].x;
            vector.y = src->mVertices[i].y;
            vector.z = src->mVertices[i].z;
            vertex.Position = vector;
            // normals
            vector.x = src->mNormals[i].x;
            vector.y = src->mNormals[i].y;
            vector.z = src->mNormals[i].z;
            vertex.Normal = vector;
            // texture coordinates
            if (src->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = src->mTextureCoords[0][i].x;
                vec.y = src->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            // tangent
            vector.x = src->mTangents[i].x;
            vector.y = src->mTangents[i].y;
            vector.z = src->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = src->mBitangents[i].x;
            vector.y = src->mBitangents[i].y;
            vector.z = src->mBitangents[i].z;
            vertex.Bitangent = vector;
            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's _Faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < src->mNumFaces; i++)
        {
            aiFace face = src->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        dest->Set(&vertices, &indices);
    }

    static void ReadMaterial(std::string directory, aiMaterial* src, Material* dest, std::vector<Texture*>* texturesLoaded) {
        auto textures = &dest->textures;
        std::vector<Texture*> diffuseMaps = LoadMaterialTextures(directory, texturesLoaded, src, aiTextureType_DIFFUSE, Material_Type::DIFFUSE);
        textures->insert(textures->end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture*> specularMaps = LoadMaterialTextures(directory, texturesLoaded, src, aiTextureType_SPECULAR, Material_Type::SPECULAR);
        textures->insert(textures->end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture*> normalMaps = LoadMaterialTextures(directory, texturesLoaded, src, aiTextureType_HEIGHT, Material_Type::NORMAL);
        textures->insert(textures->end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture*> heightMaps = LoadMaterialTextures(directory, texturesLoaded, src, aiTextureType_AMBIENT, Material_Type::HEIGHT);
        textures->insert(textures->end(), heightMaps.begin(), heightMaps.end());
    }

    static inline std::vector<Texture*> LoadMaterialTextures(std::string directory, std::vector<Texture*>* texturesLoaded, aiMaterial* mat, aiTextureType type, Material_Type typeName) {
        std::vector<Texture*> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (unsigned int j = 0; j < texturesLoaded->size(); j++)
            {
                if (std::strcmp(texturesLoaded->at(j)->Path().c_str(), str.C_Str()) == 0)
                {
                    textures.push_back(texturesLoaded->at(j));
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if (!skip)
            {   // if texture hasn't been loaded already, load it
                Texture* texture = new Texture(typeName); 
                texture->LoadTexture(str.C_Str(), directory);
                textures.push_back(texture);
                texturesLoaded->push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }
};
