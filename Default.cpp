#include "Default.h"

std::string* Default::ShaderIncludes::MainCamera;
std::string* Default::ShaderIncludes::Lights;
std::string* Default::ShaderIncludes::Material;

Texture* Default::Textures::MissingTexture;
Texture* Default::Textures::UV;
Mesh* Default::Primitives::Sphere;
Mesh* Default::Primitives::Cube;
Mesh* Default::Primitives::Quad;
Mesh* Default::Primitives::Cone;
Mesh* Default::Primitives::Cylinder;

void Default::Load() {

	ShaderIncludes::MainCamera = new std::string(FileSystem::LoadFileAsString(FileSystem::GetPath("Shaders/Include/MainCamera.inc")));

	std::string add = "#define MAX_MATERIALS_AMOUNT " + std::to_string(ShaderIncludes::MaxMaterialsAmount) + "\n";
	ShaderIncludes::Material = new std::string(add + FileSystem::LoadFileAsString(FileSystem::GetPath("Shaders/Include/Material.inc")));

	add =
		"#define DIRECTIONAL_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxDirectionalLightAmount) +
		"\n#define POINT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxPointLightAmount) +
		"\n#define SPOT_LIGHTS_AMOUNT " + std::to_string(ShaderIncludes::MaxSpotLightAmount) + "\n";
	ShaderIncludes::Lights = new std::string(add + FileSystem::LoadFileAsString(FileSystem::GetPath("Shaders/Include/Lights.inc")));

	Textures::MissingTexture = new Texture(Material_Type::DIFFUSE);
	Textures::MissingTexture->LoadTexture(FileSystem::GetPath("Textures/texture-missing.png"), "");
	Textures::UV = new Texture(Material_Type::DIFFUSE);
	Textures::UV->LoadTexture(FileSystem::GetPath("Textures/uv-test.png"), "");

	Scene* scene = new Scene();
	AssimpImporter::LoadScene(scene, FileSystem::GetPath("Primitives/sphere.obj"));
	Primitives::Sphere = new Mesh();
	Mesh* mesh = scene->mMeshes[0];
	Primitives::Sphere->Set(mesh->vertices, mesh->triangles);
	Primitives::Sphere->RecalculateNormal();
	delete scene;

	scene = new Scene();
	AssimpImporter::LoadScene(scene, FileSystem::GetPath("Primitives/cube.obj"));
	Primitives::Cube = new Mesh();
	mesh = scene->mMeshes[0];
	Primitives::Cube->Set(mesh->vertices, mesh->triangles);
	Primitives::Cube->RecalculateNormal();
	delete scene;

	scene = new Scene();
	AssimpImporter::LoadScene(scene, FileSystem::GetPath("Primitives/quad.obj"));
	Primitives::Quad = new Mesh();
	mesh = scene->mMeshes[0];
	Primitives::Quad->Set(mesh->vertices, mesh->triangles);
	Primitives::Quad->RecalculateNormal();
	delete scene;

	scene = new Scene();
	AssimpImporter::LoadScene(scene, FileSystem::GetPath("Primitives/cone.obj"));
	Primitives::Cone = new Mesh();
	mesh = scene->mMeshes[0];
	Primitives::Cone->Set(mesh->vertices, mesh->triangles);
	Primitives::Cone->RecalculateNormal();
	delete scene;

	scene = new Scene();
	AssimpImporter::LoadScene(scene, FileSystem::GetPath("Primitives/cylinder.obj"));
	Primitives::Cylinder = new Mesh();
	mesh = scene->mMeshes[0];
	Primitives::Cylinder->Set(mesh->vertices, mesh->triangles);
	Primitives::Cylinder->RecalculateNormal();
	delete scene;
}