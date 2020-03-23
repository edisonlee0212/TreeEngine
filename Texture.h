#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/include/glad/glad.h>
#include <stb/stb_image.h>
#include <vector>
class Texture : public SharedComponentBase {
public:
	Texture() : SharedComponentBase(){
        _ID = 0;
	}

    ~Texture() {
        if (_ID != 0) {
            glDeleteTextures(1, &_ID);
        }
    }
    std::size_t hash_code() { return _ID; }
	unsigned int ID() { return _ID; }
    std::string Path() { return _Path; }
    std::string Type() { return _Type; }
    void LoadTexture(const char* path, const std::string& directory)
    {
        if (_ID != 0) {
            glDeleteTextures(1, &_ID);
            _ID = 0;
        }
        std::string filename = std::string(path);
        if(!directory._Equal(""))
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
            std::cout << "Texture failed to load at path: " << filename << std::endl;
            stbi_image_free(data);
        }
    }
private:
	unsigned int _ID;
    std::string _Type;
    std::string _Path;
};
Texture* defaultTexture;
#endif TEXTURE_H
