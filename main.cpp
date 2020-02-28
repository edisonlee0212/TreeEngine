#include "TreeEngine.h"
Time* time;
Input* input;
World* world;
Camera* camera;
Window* window;

void WindowResizeCallback(GLFWwindow*, int, int);
void MouseScrollCallback(GLFWwindow*, double, double);
void CursorPositionCallback(GLFWwindow*, double, double);
void MouseButtonCallback(GLFWwindow*, int, int, int);
void KeyCallback(GLFWwindow*, int, int, int, int);
void InitOpenGL(Window*);

int main()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	window = new Window();
	time = new Time();
	input = new Input();
	world = new World(camera, time, window, input);
	world->CreateSystem(SystemType::CameraSystemType);
	world->CreateSystem(SystemType::RenderSystemType);
	InitOpenGL(window);
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
	Entity* entity = world->_EntityManager->AddEntity();
	entity->_Mesh = new Mesh(sizeof(vertices), vertices);
	entity->_Shader = new Shader("vertex.vs", "fragment.fs");
	entity->_Texture = new Texture("uv-test.jpg");
	entity->_Translation = new Translation(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
	Entity* entity2 = world->_EntityManager->AddEntity();
	entity2->_Mesh = new Mesh(sizeof(vertices), vertices);
	entity2->_Shader = new Shader("vertex.vs", "fragment.fs");
	entity2->_Texture = new Texture("cat.jpg");
	entity2->_Translation = new Translation(glm::translate(glm::mat4(1.0f), glm::vec3(2, 0, 0)));
	std::cout << entity->_Texture->_Index << " and " << entity2->_Texture->_Index << std::endl;
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window->window()))
	{
		world->Update();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void InitOpenGL(Window* window) {
	glfwSetFramebufferSizeCallback(window->window(), WindowResizeCallback);
	glfwSetScrollCallback(window->window(), MouseScrollCallback);
	glfwSetKeyCallback(window->window(), KeyCallback);
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
	input->CursorPositionCallback(window, xpos, ypos);
}
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	input->MouseButtonCallback(window, button, action, mods);
}

void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	input->MouseScrollCallback(window, xoffset, yoffset);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	input->KeyCallback(window, key, scancode, action, mods);
}

void WindowResizeCallback(GLFWwindow* window, int width, int height) {
	world->_Window->Resize(width, height);
}

