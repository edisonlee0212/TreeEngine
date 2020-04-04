#pragma once
#include "Misc.h"
#include "SCEnvelope.h"

class CylinderEnvelope : public SCEnvelope {
public:
	CylinderEnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Material* pointMaterial) : SCEnvelope(xMax, yMax, zMax, xMin, yMin, zMin, pointMaterial) {

	}
	bool isInEnvelope(glm::vec3 point) {
		float height = point.y;
		float distance = glm::sqrt(point.x * point.x + point.z * point.z);
		float radius = (_XMax - _XMin) / 2.0f;
		return radius > distance;
	}

};

