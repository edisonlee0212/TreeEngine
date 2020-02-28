#include "TreeEngine.h"

World* world;

void WindowResizeCallback(GLFWwindow*, int, int);
void MouseScrollCallback(GLFWwindow*, double, double);
void CursorPositionCallback(GLFWwindow*, double, double);
void MouseButtonCallback(GLFWwindow*, int, int, int);
void KeyCallback(GLFWwindow*, int, int, int, int);
void InitOpenGL(GLFWwindow*);

int main()
{
	Managers* managers = new Managers();
	world = new World(managers);
	world->CreateSystem<CameraSystem>();
	world->CreateSystem<RenderSystem>();

	InitOpenGL(managers->windowManager->window());
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
	Entity* entity = managers->entityManager->AddEntity();
	entity->_Mesh = new Mesh(sizeof(vertices), vertices);
	entity->_Shader = new Shader("vertex.vs", "fragment.fs");
	entity->_Texture = new Texture("uv-test.jpg");
	entity->_Translation = new Translation(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
	Entity* entity2 = managers->entityManager->AddEntity();
	entity2->_Mesh = new Mesh(sizeof(vertices), vertices);
	entity2->_Shader = new Shader("vertex.vs", "fragment.fs");
	entity2->_Texture = new Texture("cat.jpg");
	entity2->_Translation = new Translation(glm::translate(glm::mat4(1.0f), glm::vec3(2, 0, 0)));
	std::cout << entity->_Texture->_Index << " and " << entity2->_Texture->_Index << std::endl;
	// render loop
	// -----------
	while (!glfwWindowShouldClose(managers->windowManager->window()))
	{
		world->Update();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void InitOpenGL(GLFWwindow* window) {
	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);
	glfwSetKeyCallback(window, KeyCallback);
	//glfwSetInputMode(window->window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);
}

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

