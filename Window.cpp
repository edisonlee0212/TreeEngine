#include "Window.h"
#include "Debug.h"

Window::Window(int width = SCR_WIDTH, int height = SCR_HEIGHT, const char * title = "Tree")
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
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (m_window == NULL)
    {
        xdebug("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);
    

}

Window::~Window() {
    glfwTerminate();
}

