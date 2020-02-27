#ifndef WINDOW_H
#define	WINDOW_H
#include <glfw-3.3/include/GLFW/glfw3.h>
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Window
{
public:
	Window();
	~Window();

	GLFWwindow* window(){
		return _Window;
	}
    void FramebufferResizeCallback(GLFWwindow* window, int width, int height);
    void Update();
private:
	GLFWwindow* _Window;
};

void Window::FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void Window::Update() {

}

Window::Window()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    // glfw window creation
    // --------------------
    _Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tree Engine", NULL, NULL);
    if (_Window == NULL)
    {
        xdebug("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(_Window);
}

Window::~Window() {
    glfwTerminate();
}

#endif WINDOW_H


