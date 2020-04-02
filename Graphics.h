#pragma once
#include "Misc.h"
#include "Camera.h"

#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"

class Graphics {
public:
	static unsigned int Triangles;
	static unsigned int DrawCall;
	static void DrawMeshInstanced(Mesh* mesh, Material* material, glm::mat4* matrices, Camera* camera, size_t count);
	static void DrawMesh(Mesh* mesh, glm::mat4 matrix, Material* material, Camera* camera);
};