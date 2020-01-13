#ifndef RENDERER_H
#define RENDERER_H
#include <vector>
#include "Debug.h"
#include "Shader.h"
#include <glad/include/glad/glad.h>
#include <stb/stb_image.h>
class Renderer
{
public:
	Renderer(Shader *);
	~Renderer();
	void render();
	void setVertices(int, float *);
	void addTexture(int, const char*, const char *);
	Shader* shader();
private:
	unsigned int _VBO, _VAO;
	unsigned int _textureAmount;
	std::vector<unsigned int> _textures;
	unsigned int _vertexAmount;
	float* _vertices;
	Shader * m_shader;
};




#endif