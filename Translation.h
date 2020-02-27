#ifndef TRANSLATION_H
#define TRANSLATION_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Translation : public ComponentBase {
public:
	Translation(glm::mat4 value) { _Value = value; }
	void SetPosition(glm::vec3 position) {
		_Value = glm::translate(_Value, position);
	}

	void RotateAroundAxis(float angle, glm::vec3 axis) {
		_Value = glm::rotate(_Value, glm::radians(angle), axis);
	}
	glm::mat4 _Value;
	
};
#endif TRANSLATION_H
