#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/include/glad/glad.h>
#include <stb/stb_image.h>
#include <vector>
class Texture : public ComponentBase {
public:
	Texture(const char* path) : ComponentBase(){
		// texture 1
		// ---------
		glGenTextures(1, &_Index);
		glBindTexture(GL_TEXTURE_2D, _Index);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			xdebug("Failed to load texture");
		}
		stbi_image_free(data);
	}
	unsigned int _Index;
};
#endif TEXTURE_H
