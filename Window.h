#ifndef WINDOW_H
#define	WINDOW_H
#include <glfw-3.3/include/GLFW/glfw3.h>
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Window
{
public:
	Window(int, int);
	~Window();
    int Width;
    int Height;
	GLFWwindow* window(){
		return _Window;
	}
    void Resize(int, int);
private:
	GLFWwindow* _Window;
};


void Window::Resize(int width, int height) {
    Width = width;
    Height = height;
    glViewport(0, 0, width, height);
}

Window::Window(int width = SCR_WIDTH, int height = SCR_HEIGHT)
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
    _Window = glfwCreateWindow(width, height, "Tree Engine", NULL, NULL);
    Width = width;
    Height = height;
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


