#include "CoilEnvelope.h"

bool CoilEnvelope::isInEnvelope(glm::vec3 point) {
	float h = point.y;
	glm::vec2 xz = glm::vec2(point.x, point.z);
	float circleA = (_XMax - _XMin) / 5.0f;
	glm::vec2 center = glm::vec2(circleA * glm::sin(6.0f * 3.14159f * h / (_YMax - _YMin)), circleA * glm::cos(6.0f * 3.14159f * h / (_YMax - _YMin)));
	return glm::distance(center, xz) < circleA;
}