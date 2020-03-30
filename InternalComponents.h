#pragma once
#include "Misc.h"
#include "ComponentBase.h"
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