#include "Texture.h"


Texture::Texture(Material_Type type) : SharedComponentBase(), _Type(type) {
    _ID = 0;
}

Texture::~Texture() {
    if (_ID != 0) {
        glDeleteTextures(1, &_ID);
    }
}
std::size_t Texture::hash_code() { return _ID; }
unsigned int Texture::ID() { return _ID; }
std::string Texture::Path() { return _Path; }
Material_Type Texture::Type() { return _Type; }
void Texture::Clear() {
    if (_ID != 0) {
        glDeleteTextures(1, &_ID);
        _ID = 0;
    }
}
void Texture::LoadTexture(std::string path, const std::string& directory)
{
    Clear();
    std::string filename = path;
    if (!directory._Equal(""))
        filename = directory + '/' + filename;
    glGenTextures(1, &_ID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, _ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        Debug::Log("Texture failed to load at path: " + filename);
        stbi_image_free(data);
    }
}

void Texture::LoadCubeMap(std::vector<std::string> faces) {
    Clear();
    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _ID);

    int width, height, nrComponents;
    auto size = faces.size();
    if (size != 6) {
        Debug::Error("Texture::LoadCubeMap: Size error.");
        return;
    }
    for (unsigned int i = 0; i < size; i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}