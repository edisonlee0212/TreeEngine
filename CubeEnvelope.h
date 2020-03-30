#pragma once
#include "Misc.h"
#include "SCEnvelope.h"
class CubeEnvelope : public SCEnvelope {
public: 
	CubeEnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Material* material) : SCEnvelope(xMax, yMax, zMax, xMin, yMin, zMin, material) {

	}
	bool isInEnvelope(glm::vec3 point) {
		return true;
	}
};


