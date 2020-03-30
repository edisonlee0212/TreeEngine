#pragma once
class WindowManager
{
public:
    
    static GLFWwindow* CreateWindow(int, int);
    static int GetWidth() { return Width; }
    static int GetHeight() { return Height; }
    static GLFWwindow* GetWindow() { return window; }
    static void ResizeCallback(GLFWwindow*, int, int);
    
private:
    static int Width;
    static int Height;
	static GLFWwindow* window;
};
int WindowManager::Height;
int WindowManager::Width;
GLFWwindow* WindowManager::window;

void WindowManager::ResizeCallback(GLFWwindow* window, int width, int height) {
    Width = width;
    Height = height;
    glViewport(0, 0, width, height);
}
GLFWwindow* WindowManager::CreateWindow(int width, int height) {
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(width, height, "Tree Engine", NULL, NULL);
    WindowManager::Width = width;
    WindowManager::Height = height;
    if (window == NULL)
    {
        Debug::Error("Failed to create GLFW window");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    return window;
}

