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
	Point* p0 = new Point(glm::vec3(0.0f, 0.0f, 0.0f));
	Point* p1 = new Point(glm::vec3(0.0f, 0.0f, 1.0f));
	Point* p2 = new Point(glm::vec3(0.0f, 1.0f, 0.0f));
	Point* p3 = new Point(glm::vec3(0.0f, 1.0f, 1.0f));
	Point* p4 = new Point(glm::vec3(1.0f, 0.0f, 0.0f));
	Point* p5 = new Point(glm::vec3(1.0f, 0.0f, 1.0f));
	Point* p6 = new Point(glm::vec3(1.0f, 1.0f, 0.0f));
	Point* p7 = new Point(glm::vec3(1.0f, 1.0f, 1.0f));

	skeleton->points.push_back(p0);
	skeleton->points.push_back(p1);
	skeleton->points.push_back(p2);
	skeleton->points.push_back(p3);
	skeleton->points.push_back(p4);
	skeleton->points.push_back(p5);
	skeleton->points.push_back(p6);
	skeleton->points.push_back(p7);

	Face* f0 = new Face(0, p0, p2, p3, p1);
	f0->AttachPoints();
	Face* f1 = new Face(1, p1, p5, p4, p0);
	f1->AttachPoints();
	Face* f2 = new Face(2, p0, p4, p6, p2);
	f2->AttachPoints();
	Face* f3 = new Face(3, p4, p5, p7, p6);
	f3->AttachPoints();
	Face* f4 = new Face(4, p6, p7, p3, p2);
	f4->AttachPoints();
	Face* f5 = new Face(5, p1, p3, p7, p5);
	f5->AttachPoints();

	f0->f3 = f1;
	f1->f3 = f0;
	
	f0->f0 = f2;
	f1->f2 = f2;
	f2->f3 = f0;
	f2->f0 = f1;

	f3->f0 = f1;
	f3->f3 = f2;
	f2->f1 = f3;
	f1->f1 = f3;

	f4->f2 = f0;
	f4->f3 = f2;
	f4->f0 = f3;
	f0->f1 = f4;
	f2->f2 = f4;
	f3->f2 = f4;

	f5->f0 = f0;
	f5->f3 = f1;
	f5->f1 = f4;
	f5->f2 = f3;
	f0->f2 = f5;
	f1->f0 = f5;
	f3->f1 = f5;
	f4->f1 = f5;

	skeleton->faces.push_back(f0);
	skeleton->faces.push_back(f1);
	skeleton->faces.push_back(f2);
	skeleton->faces.push_back(f3);
	skeleton->faces.push_back(f4);
	skeleton->faces.push_back(f5);
	skeleton->CatmullClark();
	skeleton->CatmullClark();
	// skeleton->CatmullClark();
	Entity* entity = world->managers->entityManager->CreateEntity();
	entity->material = new Material();
	entity->material->shader = new Shader("default.vs", "default.fs");
	Texture texture;
	//texture.LoadTexture("border.jpg", "");
	texture.LoadTexture("direction.jpg", "");
	entity->material->textures.push_back(texture);
	vector<Vertex> vertices;
	vector<unsigned int> triangles;
	for (auto i : skeleton->faces) {
		Vertex v0;
		v0.Position = i->pp0();
		v0.TexCoords = glm::vec2(0.0f, 0.0f);
		Vertex v1;
		v1.Position = i->pp1();
		v1.TexCoords = glm::vec2(1.0f, 0.0f);
		Vertex v2;
		v2.Position = i->pp2();
		v2.TexCoords = glm::vec2(1.0f, 1.0f);
		Vertex v3;
		v3.Position = i->pp2();
		v3.TexCoords = glm::vec2(1.0f, 1.0f);
		Vertex v4;
		v4.Position = i->pp3();
		v4.TexCoords = glm::vec2(0.0f, 1.0f);
		Vertex v5;
		v5.Position = i->pp0();
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