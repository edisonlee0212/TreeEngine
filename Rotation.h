#ifndef ROTATION_H
#define ROTATION_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Rotation : public ComponentBase {
public:
	glm::mat4 Value;
};
#endif ROTATION_H
