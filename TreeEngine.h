#ifndef TREEENGINE_H
#define TREEENGINE_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Debug.h"
#include "Enums.h"
#include "Path.h"
#include "Misc.h"
#include "ECSInternal.h"
#include "ModelManager.h"

#include "CatmullClarkModel.h"
#include "TreeSkeleton.h"

#include "ECSExternal.h"
World* world;


void WindowResizeCallback(GLFWwindow*, int, int);
void MouseScrollCallback(GLFWwindow*, double, double);
void CursorPositionCallback(GLFWwindow*, double, double);
void MouseButtonCallback(GLFWwindow*, int, int, int);
void KeyCallback(GLFWwindow*, int, int, int, int);

void LoadNanoSuit(glm::vec3, glm::vec3);
void LoadCubeModel();

void TreeEngineStart();
void TreeEngineLoop();
void TreeEngineEnd();

#pragma region CallbackFunctions
void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	Input::CursorPositionCallback(window, xpos, ypos);
}
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	Input::MouseButtonCallback(window, button, action, mods);
}
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	Input::MouseScrollCallback(window, xoffset, yoffset);
}
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Input::KeyCallback(window, key, scancode, action, mods);
}
void WindowResizeCallback(GLFWwindow* window, int width, int height) {
	WindowManager::Resize(width, height);
}
#pragma endregion

#pragma region USELESS
void LoadCubeModel() {
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
	Entity* entity = World::entityManager->CreateEntity();
	entity->material = new Material();
	entity->material->shader = new Shader("default.vs", "default.fs");
	Texture* texture = new Texture();
	texture->LoadTexture("treesurface.jpg", "");
	entity->material->textures.push_back(texture);
	entity->mesh = model->GetCurrentMesh();
	Scale s;
	s.Value = glm::vec3(1.0f);
	Translation t;
	t.Value = glm::vec3(0.0f);
	World::entityManager->SetComponent<Scale>(entity, s);
	World::entityManager->SetComponent<Translation>(entity, t);
	entity->ToDraw = true;
	return;
}
void LoadNanoSuit(glm::vec3 position, glm::vec3 scale) {
	Entity* entity = World::entityManager->CreateEntity();
	Translation t;
	t.Value = position;
	Scale s;
	s.Value = scale;
	World::entityManager->SetComponent<Translation>(entity, t);
	World::entityManager->SetComponent<Scale>(entity, s);
	Shader* modelShader = new Shader("src/Materials/Shaders/default.vs", "src/Materials/Shaders/default.fs");
	ModelManager::LoadModel(entity, modelShader, "Models/nanosuit/nanosuit.obj");
}
#pragma endregion

#pragma region TreeEngineDriver
void TreeEngineStart() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	auto window = WindowManager::CreateWindow(800, 600);
	
	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug::Error("Failed to initialize GLAD");
		exit(-1);
	}
	world = new World();
	world->CreateSystem<TRSToLocalToWorldSystem>();
	world->CreateSystem<TRSToLocalToParentSystem>();
	world->CreateSystem<LocalToParentSystem>();
	world->CreateSystem<CameraSystem>();
	world->CreateSystem<RenderSystem>();
	world->CreateSystem<ImGUISystem>();
	Default::Load();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
}
void TreeEngineLoop() {
	while (!glfwWindowShouldClose(WindowManager::GetWindow()))
	{
		world->Update();

		

		glfwSwapBuffers(WindowManager::GetWindow());
	}
}
void TreeEngineEnd() {
	delete world;
	
	glfwTerminate();
}
#pragma endregion

#endif TREEENGINE_H