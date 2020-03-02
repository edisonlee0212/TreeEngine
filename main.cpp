#include "TreeEngine.h"

int main()
{
	TreeEngineStart();
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	LoadCube();
	TreeEngineLoop();
	TreeEngineEnd();
	return 0;
}

void LoadCube() {
	Skeleton* skeleton = new Skeleton();
	Face* f0 = new Face();
	f0->p0 = glm::vec3(0.0f, 0.0f, 0.0f);
	f0->p1 = glm::vec3(0.0f, 1.0f, 0.0f);
	f0->p2 = glm::vec3(0.0f, 1.0f, 1.0f);
	f0->p3 = glm::vec3(0.0f, 0.0f, 1.0f);
	/*
	Face* f1 = new Face();
	f1->p0 = glm::vec3();
	f1->p1 = glm::vec3();
	f1->p2 = glm::vec3();
	f1->p3 = glm::vec3();
	Face* f2 = new Face();
	f2->p0 = glm::vec3();
	f2->p1 = glm::vec3();
	f2->p2 = glm::vec3();
	f2->p3 = glm::vec3();
	Face* f3 = new Face();
	f3->p0 = glm::vec3();
	f3->p1 = glm::vec3();
	f3->p2 = glm::vec3();
	f3->p3 = glm::vec3();
	Face* f4 = new Face();
	f4->p0 = glm::vec3();
	f4->p1 = glm::vec3();
	f4->p2 = glm::vec3();
	f4->p3 = glm::vec3();
	Face* f5 = new Face();
	f5->p0 = glm::vec3(1, 0, 0);
	f5->p1 = glm::vec3(1, 1, 0);
	f5->p2 = glm::vec3(1, 1, 1);
	f5->p3 = glm::vec3(1, 0, 1);*/
	skeleton->faces.push_back(f0);
	/*skeleton->faces.push_back(f1);
	skeleton->faces.push_back(f2);
	skeleton->faces.push_back(f3);
	skeleton->faces.push_back(f4);
	skeleton->faces.push_back(f5);*/
	skeleton->CatmullClark();
	skeleton->CatmullClark();
	Entity * entity = world->managers->entityManager->CreateEntity();
	entity->material = new Material();
	entity->material->shader = new Shader("nanosuit.vs", "nanosuit.fs");
	Texture texture;
	texture.LoadTexture("uv-test.jpg", "");
	entity->material->textures.push_back(texture);
	vector<Vertex> vertices;
	vector<unsigned int> triangles;
	for (auto i : skeleton->faces) {
		Vertex v0;
		v0.Position = i->p0;
		v0.TexCoords = glm::vec2(0.0f, 0.0f);
		Vertex v1;
		v1.Position = i->p1;
		v1.TexCoords = glm::vec2(1.0f, 0.0f);
		Vertex v2;
		v2.Position = i->p2;
		v2.TexCoords = glm::vec2(1.0f, 1.0f);
		Vertex v3;
		v3.Position = i->p2;
		v3.TexCoords = glm::vec2(1.0f, 1.0f);
		Vertex v4;
		v4.Position = i->p3;
		v4.TexCoords = glm::vec2(0.0f, 1.0f);
		Vertex v5;
		v5.Position = i->p0;
		v5.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(v0);
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);
		vertices.push_back(v5);
		triangles.push_back(i->index * 6);
		triangles.push_back(i->index * 6 + 1);
		triangles.push_back(i->index * 6 + 2);
		triangles.push_back(i->index * 6 + 3);
		triangles.push_back(i->index * 6 + 4);
		triangles.push_back(i->index * 6 + 5);
	}
	entity->mesh = new Mesh(vertices, triangles);
	glm::mat4 model = glm::mat4(1.0f);
	entity->GetTransform()->SetPosition(glm::vec3(0.0f, -1.75f, 0.0f));
	entity->ToDraw = true;
}


void LoadNanoSuit() {
	Entity* entity = world->managers->entityManager->CreateEntity();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.1f));	// it's a bit too big for our scene, so scale it down
	entity->GetTransform()->SetPosition(glm::vec3(0.0f, -1.75f, 0.0f));
	entity->GetTransform()->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	Shader* modelShader = new Shader("nanosuit.vs", "nanosuit.fs");

	world->managers->modelManager->LoadModel(entity, modelShader, "Models/nanosuit/nanosuit.obj");

}