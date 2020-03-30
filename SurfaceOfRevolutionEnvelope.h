#pragma once
#include "Misc.h"
#include "SCEnvelope.h"

class SurfaceOfRevelutionEnvelope : public SCEnvelope {
public:
	SurfaceOfRevelutionEnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Material* material) : SCEnvelope(xMax, yMax, zMax, xMin, yMin, zMin, material) {}
	float GetRadius(float height) {
		if (height >= _YMin || height <= _YMax) {
			return glm::sin(glm::pi<float>() * glm::pow((height - _YMin) / (_YMax - _YMin), 0.6f));
		}
		return 0;
	}
	bool isInEnvelope(glm::vec3 point) {
		float height = point.y;
		float distance = glm::sqrt(point.x * point.x + point.z * point.z);
		return GetRadius(height) > distance;
	}

private:

};



