#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>

#include "Debug.h"
#include "Enums.h"
#include "Misc.h"
#include "ECSInternal.h"
#include "ModelManager.h"

#include "ECSExternal.h"

class World;

class TreeEngine {
public:
	void GLInit() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

		auto window = WindowManager::CreateWindow(800, 600);

		glfwSetFramebufferSizeCallback(window, WindowManager::ResizeCallback);
		glfwSetCursorPosCallback(window, Input::CursorPositionCallback);
		glfwSetScrollCallback(window, Input::MouseScrollCallback);
		glfwSetKeyCallback(window, Input::KeyCallback);
		glfwSetMouseButtonCallback(window, Input::MouseButtonCallback);
		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Debug::Error("Failed to initialize GLAD");
			exit(-1);
		}
	}

	void Start() {
		_Looping = false;
		GLInit();
		world = new World();
		world->CreateSystem<TRSToLocalToWorldSystem>();
		world->CreateSystem<TRSToLocalToParentSystem>();
		world->CreateSystem<LocalToParentSystem>();
		world->CreateSystem<CameraSystem>();
		world->CreateSystem<RenderSystem>();
		world->CreateSystem<ImGUISystem>();

		world->CreateSystem<SCTreeSystem>();

		Default::Load();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}
	void Loop() {
		if (_Looping) return;
		_Looping = true;
		while (_Looping && !glfwWindowShouldClose(WindowManager::GetWindow()))
		{
			world->Update();
		}
	}
	void End() {
		delete world;
		glfwTerminate();
	}
private:
	World* world;
	bool _Looping;
};

void LoadNanoSuit(glm::vec3, glm::vec3);


#pragma region USELESS

void LoadNanoSuit(glm::vec3 position, glm::vec3 scale) {
	Entity* entity = World::Entities->CreateEntity();
	Translation t;
	t.Value = position;
	Scale s;
	s.Value = scale;
	World::Entities->SetComponent<Translation>(entity, t);
	World::Entities->SetComponent<Scale>(entity, s);
	Shader* modelShader = new Shader("src/Materials/Shaders/Default.vert", "src/Materials/Shaders/Default.frag");
	ModelManager::LoadModel(entity, modelShader, "Models/nanosuit/nanosuit.obj");
}
#pragma endregion
