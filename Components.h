#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct LocalToParent : ComponentBase
{
public:
    glm::mat4 value;
};

struct LocalToWorld : ComponentBase
{
public:
	glm::mat4 value;
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

#endif COMPONENTS_H
