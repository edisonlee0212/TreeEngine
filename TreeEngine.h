#ifndef TREEENGINE_H
#define TREEENGINE_H


#include <glad/include/glad/glad.h>

#include <glfw-3.3/include/GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

#define XTEST 0 
#define XDEBUG 1
/* For testing */
#if XTEST
#define xtest(...)
#else
#define xtest(...)
#endif
#include "Debug.h"
#include "Enums.h"

#include "ComponentBase.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

#include "Transform.h"
#include "Skeleton.h"
#include "Managers.h"

#include "SystemBase.h"
#include "TranslationSystem.h"
#include "RenderSystem.h"
#include "CameraSystem.h"

#include "World.h"
#include "CatmullModel.h"
World* world;


void WindowResizeCallback(GLFWwindow*, int, int);
void MouseScrollCallback(GLFWwindow*, double, double);
void CursorPositionCallback(GLFWwindow*, double, double);
void MouseButtonCallback(GLFWwindow*, int, int, int);
void KeyCallback(GLFWwindow*, int, int, int, int);
void TreeEngineStart();
void TreeEngineLoop();

void LoadNanoSuit();
Mesh* MakeMesh(std::vector<Face*>);
void LoadCube();

void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	world->managers->inputManager->CursorPositionCallback(window, xpos, ypos);
}
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	world->managers->inputManager->MouseButtonCallback(window, button, action, mods);
}

void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	world->managers->inputManager->MouseScrollCallback(window, xoffset, yoffset);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	world->managers->inputManager->KeyCallback(window, key, scancode, action, mods);
}

void WindowResizeCallback(GLFWwindow* window, int width, int height) {
	world->managers->windowManager->Resize(width, height);
}



void TreeEngineStart() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	world = new World();
	world->CreateSystem<CameraSystem>();
	world->CreateSystem<RenderSystem>();
	auto window = world->managers->windowManager->CreateWindow(800, 600);
	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);
}

void TreeEngineLoop() {
	while (!glfwWindowShouldClose(world->managers->windowManager->window()))
	{
		world->Update();
	}
}

void TreeEngineEnd() {
	delete world;
	glfwTerminate();
}
#endif TREEENGINE_H