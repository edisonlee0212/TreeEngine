#pragma once
#include "SCEnvelope.h"
class CoilEnvelope :
	public SCEnvelope
{
public:
	CoilEnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Material* pointMaterial) : SCEnvelope(xMax, yMax, zMax, xMin, yMin, zMin, pointMaterial) {

	}

	bool isInEnvelope(glm::vec3 point);
};

