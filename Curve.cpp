#include "Curve.h"

void Curve::GetUniformCurve(size_t pointAmount, std::vector<glm::vec3>* points) {
	float step = 1.0f / (pointAmount - 1);
	for (size_t i = 0; i <= pointAmount; i++) {
		points->push_back(GetPoint(step * i));
	}
}