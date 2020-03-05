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

	
	auto cubeModel = LoadCubeModel();
	
	TreeSkeleton skeleton = TreeSkeleton();
	skeleton.AddBranch(1.0f, glm::vec3(-3.0f, 2.0f, 0.0f), 1);
	
	auto mainBranch = skeleton.AddBranch(0.9f, glm::vec3(0.0f, 4.0f, 0.0f), 0);
	//mainBranch->AddBranch(1.0f, glm::vec3(-3.0f, 6.0f, 0.0f), 1);
	mainBranch = mainBranch->AddBranch(0.5f, glm::vec3(1.0f, 6.0f, 1.0f), 0);

	
	skeleton.GenerateSurface();
	CatmullClarkModel* model = new CatmullClarkModel(skeleton.GetPoints(), skeleton.GetFaces());
	entity->mesh = model->GetCurrentMesh();
	entity->ToDraw = true;
	
	float width = 0.9f;
	float x = -3.0f;
	//LoadNanoSuit(glm::vec3(0.0f, -1.75f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f));

	while (!glfwWindowShouldClose(world->managers->windowManager->window()))
	{
		world->Update();
		if (world->managers->inputManager->GetKeyUp(GLFW_KEY_COMMA) && x < -2.0f) {
			x += 1.0f;
			delete model;
			TreeSkeleton skeleton = TreeSkeleton();
			skeleton.AddBranch(width, glm::vec3(x, 2.0f, 0.0f), 1);
			auto mainBranch = skeleton.AddBranch(0.9f, glm::vec3(0.0f, 4.0f, 0.0f), 0);
			mainBranch = mainBranch->AddBranch(0.5f, glm::vec3(1.0f, 6.0f, 1.0f), 0);
			skeleton.GenerateSurface();
			model = new CatmullClarkModel(skeleton.GetPoints(), skeleton.GetFaces());
			entity->mesh = model->GetCurrentMesh();
		}else if (world->managers->inputManager->GetKeyUp(GLFW_KEY_PERIOD) && x > -9.0f) {
			x -= 1.0f;
			delete model;
			TreeSkeleton skeleton = TreeSkeleton();
			skeleton.AddBranch(width, glm::vec3(x, 2.0f, 0.0f), 1);
			auto mainBranch = skeleton.AddBranch(0.9f, glm::vec3(0.0f, 4.0f, 0.0f), 0);
			mainBranch = mainBranch->AddBranch(0.5f, glm::vec3(1.0f, 6.0f, 1.0f), 0);
			skeleton.GenerateSurface();
			model = new CatmullClarkModel(skeleton.GetPoints(), skeleton.GetFaces());
			entity->mesh = model->GetCurrentMesh();
		}else if (world->managers->inputManager->GetKeyUp(GLFW_KEY_EQUAL) && width < 1.0f) {
			width += 0.1f;
			delete model;
			TreeSkeleton skeleton = TreeSkeleton();
			skeleton.AddBranch(width, glm::vec3(x, 2.0f, 0.0f), 1);
			auto mainBranch = skeleton.AddBranch(0.9f, glm::vec3(0.0f, 4.0f, 0.0f), 0);
			mainBranch = mainBranch->AddBranch(0.5f, glm::vec3(1.0f, 6.0f, 1.0f), 0);
			skeleton.GenerateSurface();
			model = new CatmullClarkModel(skeleton.GetPoints(), skeleton.GetFaces());
			entity->mesh = model->GetCurrentMesh();
		}
		else if (world->managers->inputManager->GetKeyUp(GLFW_KEY_MINUS) && width > 0.3f) {
			width -= 0.1f;
			delete model;
			TreeSkeleton skeleton = TreeSkeleton();
			skeleton.AddBranch(width, glm::vec3(x, 2.0f, 0.0f), 1);
			auto mainBranch = skeleton.AddBranch(0.9f, glm::vec3(0.0f, 4.0f, 0.0f), 0);
			mainBranch = mainBranch->AddBranch(0.5f, glm::vec3(1.0f, 6.0f, 1.0f), 0);
			skeleton.GenerateSurface();
			model = new CatmullClarkModel(skeleton.GetPoints(), skeleton.GetFaces());
			entity->mesh = model->GetCurrentMesh();
		}
		else if (world->managers->inputManager->GetKeyUp(GLFW_KEY_9)) {
			model->Abbreviation();
			entity->mesh = model->GetCurrentMesh();
		}
		else if (world->managers->inputManager->GetKeyUp(GLFW_KEY_0)) {
			model->Subdivision();
			entity->mesh = model->GetCurrentMesh();
		}


	}
	TreeEngineEnd();
	return 0;
}



CatmullClarkModel* LoadCubeModel() {
	std::vector<Point*> _Points = std::vector<Point*>();
	std::vector<Face*> _Faces = std::vector<Face*>();

	Point* p0 = new Point(glm::vec3(-0.5f, 0.5f, -0.5f));//
	Point* p1 = new Point(glm::vec3(-0.5f, 0.5f, 0.5f));//
	Point* p2 = new Point(glm::vec3(0.5f, 0.5f, -0.5f));
	Point* p3 = new Point(glm::vec3(0.5f, 0.5f, 0.5f));
	Point* p4 = new Point(glm::vec3(-0.5f, -0.5f, -0.5f));//
	Point* p5 = new Point(glm::vec3(-0.5f, -0.5f, 0.5f));//
	Point* p6 = new Point(glm::vec3(0.5f, -0.5f, -0.5f));
	Point* p7 = new Point(glm::vec3(0.5f, -0.5f, 0.5f));

	_Points.push_back(p0);
	_Points.push_back(p1);
	_Points.push_back(p2);
	_Points.push_back(p3);
	_Points.push_back(p4);
	_Points.push_back(p5);
	_Points.push_back(p6);
	_Points.push_back(p7);
	Face* f0 = new Face(p1, p0, p2, p3);
	f0->AttachPoints();
	Face* f1 = new Face(p0, p1, p5, p4);
	f1->AttachPoints();
	Face* f2 = new Face(p2, p0, p4, p6);
	f2->AttachPoints();
	Face* f3 = new Face(p7, p5, p1, p3);
	f3->AttachPoints();
	Face* f4 = new Face(p6, p7, p3, p2);
	f4->AttachPoints();
	Face* f5 = new Face(p7, p6, p4, p5);
	f5->AttachPoints();
	
	f0->f0 = f1;
	f0->f1 = f2;
	f0->f2 = f4;
	f0->f3 = f3;

	f5->f0 = f4;
	f5->f1 = f2;
	f5->f2 = f1;
	f5->f3 = f3;

	f1->f0 = f0;
	f1->f1 = f3;
	f1->f2 = f5;
	f1->f3 = f2;

	f4->f0 = f5;
	f4->f1 = f3;
	f4->f2 = f0;
	f4->f3 = f2;

	f2->f0 = f0;
	f2->f1 = f1;
	f2->f2 = f5;
	f2->f3 = f4;

	f3->f0 = f5;
	f3->f1 = f1;
	f3->f2 = f0;
	f3->f3 = f4;

	_Faces.push_back(f0);
	_Faces.push_back(f1);
	
	_Faces.push_back(f2);
	
	_Faces.push_back(f5);
	_Faces.push_back(f3);
	_Faces.push_back(f4);
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