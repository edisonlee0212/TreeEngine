#ifndef INTERNALCOMPONENTS_H
#define INTERNALCOMPONENTS_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct LocalToParent : ComponentBase
{
public:
    glm::mat4 Value;
};

struct LocalToWorld : ComponentBase
{
public:
	glm::mat4 Value;
};

struct Rotation : ComponentBase {
public:
	glm::vec4 Value;
};

struct Translation : ComponentBase
{
public:
	glm::vec3 Value;
};

struct Scale : ComponentBase
{
public:
	glm::vec3 Value;
};

#endif INTERNALCOMPONENTS_H
