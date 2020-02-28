#ifndef TREEENGINE_H
#define TREEENGINE_H


#include <glad/include/glad/glad.h>

#include <glfw-3.3/include/GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#define XTEST 0 
#define XDEBUG 1
/* For testing */
#if XTEST
#define xtest(...)
#else
#define xtest(...)
#endif
#include "Debug.h"
#include "Enums.h"
#include "Input.h"
#include "World.h"

#endif TREEENGINE_H