#ifndef DEFAULT_H
#define DEFAULT_H
class Default {
public:
	static class Textures {
	public:
		static Texture* MissingTexture;
		static Texture* UV;
	};
	
	static class Primitives {
	public:
		static Mesh* Sphere;
		static Mesh* Cube;
		static Mesh* Quad;
		static Mesh* Cylinder;
		static Mesh* Cone;
	};

	static void Load() {
		Textures::MissingTexture = new Texture();
		Textures::MissingTexture->LoadTexture("src/Materials/Textures/texture-missing.png", "");
		Textures::UV = new Texture();
		Textures::UV->LoadTexture("src/Materials/Textures/uv-test.png", "");

		Scene* scene = new Scene();
		AssimpImporter::LoadScene(scene, "src/Materials/Primitives/sphere.obj");
		Primitives::Sphere = new Mesh();
		Mesh* mesh = scene->mMeshes[0];
		Primitives::Sphere->Set(&mesh->vertices, &mesh->triangles);
		Primitives::Sphere->RecalculateNormal();
		delete scene;

		scene = new Scene();
		AssimpImporter::LoadScene(scene, "src/Materials/Primitives/cube.obj");
		Primitives::Cube = new Mesh();
		mesh = scene->mMeshes[0];
		Primitives::Cube->Set(&mesh->vertices, &mesh->triangles);
		Primitives::Cube->RecalculateNormal();
		delete scene;

		scene = new Scene();
		AssimpImporter::LoadScene(scene, "src/Materials/Primitives/quad.obj");
		Primitives::Quad = new Mesh();
		mesh = scene->mMeshes[0];
		Primitives::Quad->Set(&mesh->vertices, &mesh->triangles);
		Primitives::Quad->RecalculateNormal();
		delete scene;

		scene = new Scene();
		AssimpImporter::LoadScene(scene, "src/Materials/Primitives/cone.obj");
		Primitives::Cone = new Mesh();
		mesh = scene->mMeshes[0];
		Primitives::Cone->Set(&mesh->vertices, &mesh->triangles);
		Primitives::Cone->RecalculateNormal();
		delete scene;

		scene = new Scene();
		AssimpImporter::LoadScene(scene, "src/Materials/Primitives/cylinder.obj");
		Primitives::Cylinder = new Mesh();
		mesh = scene->mMeshes[0];
		Primitives::Cylinder->Set(&mesh->vertices, &mesh->triangles);
		Primitives::Cylinder->RecalculateNormal();
		delete scene;
	}
};

Texture* Default::Textures::MissingTexture;
Texture* Default::Textures::UV;
Mesh* Default::Primitives::Sphere;
Mesh* Default::Primitives::Cube;
Mesh* Default::Primitives::Quad;
Mesh* Default::Primitives::Cone;
Mesh* Default::Primitives::Cylinder;
#endif DEFAULT_H
