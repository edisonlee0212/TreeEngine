#ifndef WINDOW_H
#define	WINDOW_H
#include <glfw-3.3/include/GLFW/glfw3.h>
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Window
{
public:
	Window(int, int, const char *);
	~Window();

	GLFWwindow* window(){
		return m_window;
	}
private:
	GLFWwindow* m_window;
};



#endif WINDOW_H


