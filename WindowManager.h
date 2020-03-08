#ifndef WINDOW_H
#define	WINDOW_H
#include <glfw-3.3/include/GLFW/glfw3.h>
class WindowManager
{
public:
    static GLFWwindow* CreateWindow(int, int);
    static int GetWidth() { return Width; }
    static int GetHeight() { return Height; }
    static GLFWwindow* GetWindow() { return window; }
    static void Resize(int, int);
private:
    static int Width;
    static int Height;
	static GLFWwindow* window;
};

int WindowManager::Height;
int WindowManager::Width;
GLFWwindow* WindowManager::window;

void WindowManager::Resize(int width, int height) {
    Width = width;
    Height = height;
    glViewport(0, 0, width, height);
}
GLFWwindow* WindowManager::CreateWindow(int width, int height) {
    // glfw: initialize and configure
    // ------------------------------

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(width, height, "Tree Engine", NULL, NULL);
    Width = width;
    Height = height;
    if (window == NULL)
    {
        xdebug("Failed to create GLFW window");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    return window;
}


#endif WINDOW_H


