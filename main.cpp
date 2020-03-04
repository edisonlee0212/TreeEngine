#include "TreeEngine.h"

int main()
{
	TreeEngineStart();
	Entity* entity = world->managers->entityManager->CreateEntity();
	entity->material = new Material();
	entity->material->shader = new Shader("default.vs", "default.fs");
	Texture texture;
	texture.LoadTexture("treesurface.jpg", "");
	entity->material->textures.push_back(texture);

	/*
	auto cubeModel = LoadCubeModel();
	cubeModel->Subdivision();
	cubeModel->Subdivision();
	entity->mesh = cubeModel->GetCurrentMesh();
	entity->ToDraw = true;
	*/


	TreeSkeleton skeleton = TreeSkeleton();
	std::vector<Face*> faces = std::vector<Face*>();
	std::vector<Point*> points = std::vector<Point*>();
	skeleton.GenerateSurface(&faces);
	CatmullClarkModel* model = new CatmullClarkModel(points, faces);
	entity->mesh = model->GetCurrentMesh();
	entity->ToDraw = true;
	
	
	//LoadNanoSuit(glm::vec3(0.0f, -1.75f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f));

	TreeEngineLoop();
	TreeEngineEnd();
	return 0;
}



CatmullClarkModel* LoadCubeModel() {
	std::vector<Point*> _Points = std::vector<Point*>();
	std::vector<Face*> _Faces = std::vector<Face*>();
	Point* p0 = new Point(glm::vec3(-0.5f, -0.5f, -0.5f));//
	Point* p1 = new Point(glm::vec3(-0.5f, -0.5f, 0.5f));//
	Point* p2 = new Point(glm::vec3(-0.5f, 0.5f, -0.5f));
	Point* p3 = new Point(glm::vec3(-0.5f, 0.5f, 0.5f));
	Point* p4 = new Point(glm::vec3(0.5f, -0.5f, -0.5f));//
	Point* p5 = new Point(glm::vec3(0.5f, -0.5f, 0.5f));//
	Point* p6 = new Point(glm::vec3(0.5f, 0.5f, -0.5f));
	Point* p7 = new Point(glm::vec3(0.5f, 0.5f, 0.5f));


	_Points.push_back(p0);
	_Points.push_back(p1);
	_Points.push_back(p2);
	_Points.push_back(p3);
	_Points.push_back(p4);
	_Points.push_back(p5);
	_Points.push_back(p6);
	_Points.push_back(p7);
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
	
	_Faces.push_back(f0);
	_Faces.push_back(f1);
	
	_Faces.push_back(f2);
	
	_Faces.push_back(f3);
	_Faces.push_back(f4);
	_Faces.push_back(f5);
	CatmullClarkModel* model = new CatmullClarkModel(_Points, _Faces);
	
	return model;
}


void LoadNanoSuit(glm::vec3 position, glm::vec3 scale) {
	Entity* entity = world->managers->entityManager->CreateEntity();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.1f));	// it's a bit too big for our scene, so scale it down
	entity->GetTransform()->SetPosition(position);
	entity->GetTransform()->SetScale(scale);
	Shader* modelShader = new Shader("default.vs", "default.fs");

	world->managers->modelManager->LoadModel(entity, modelShader, "Models/nanosuit/nanosuit.obj");

}