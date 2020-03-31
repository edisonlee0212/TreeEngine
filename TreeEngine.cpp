#include "TreeEngine.h"
void TreeEngine::GLInit() {
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

void TreeEngine::Start() {
	_Looping = false;
	GLInit();
	Default::Load();
	world = new World();
	

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}
void TreeEngine::Loop() {
	if (_Looping) return;
	_Looping = true;
	while (_Looping && !glfwWindowShouldClose(WindowManager::GetWindow()))
	{
		world->Update();
	}
}
void TreeEngine::End() {
	delete world;
	glfwTerminate();
}