#ifndef CYLINDERENVELOPE_H
#define CYLINDERENVELOPE_H
class CylinderEnvelope : public SCEnvelope {
public:
	CylinderEnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Material* material) : SCEnvelope(xMax, yMax, zMax, xMin, yMin, zMin, material) {

	}
	bool isInEnvelope(glm::vec3 point);
};

bool CylinderEnvelope::isInEnvelope(glm::vec3 point) {
	float height = point.y;
	float distance = glm::sqrt(point.x * point.x + point.z * point.z);
	float radius = (_XMax - _XMin) / 2.0f;
	return radius > distance;
}
#endif CYLINDERENVELOPE_H