#ifndef WINDOW_H
#define	WINDOW_H
#include <glfw-3.3/include/GLFW/glfw3.h>
class WindowManager
{
public:
	WindowManager(int, int);
	~WindowManager();
    int Width;
    int Height;
	GLFWwindow* window(){
		return _Window;
	}
    void Resize(int, int);
private:
	GLFWwindow* _Window;
};


void WindowManager::Resize(int width, int height) {
    Width = width;
    Height = height;
    glViewport(0, 0, width, height);
}

WindowManager::WindowManager(int width, int height)
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

WindowManager::~WindowManager() {
    glfwTerminate();
}

#endif WINDOW_H


