#ifndef TRANSLATION_H
#define TRANSLATION_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Translation : public ComponentBase {
public:
	Translation(glm::mat4 value) :value(value) {}
	void SetPosition(glm::vec3 position) {
		value = glm::translate(value, position);
	}

	void SetScale(glm::vec3 scale) {
		value = glm::scale(value, scale);
	}

	void RotateAroundAxis(float angle, glm::vec3 axis) {
		value = glm::rotate(value, glm::radians(angle), axis);
	}
	glm::mat4 value;

};
#endif TRANSLATION_H
