#ifndef SURFACEOFREVOLUTIONENVELOPE_H
#define SURFACEOFREVOLUTIONENVELOPE_H

class SurfaceOfRevelutionEnvelope : public Envelope {
public:
	SurfaceOfRevelutionEnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin) : Envelope(xMax, yMax, zMax, xMin, yMin, zMin) {}
	glm::vec3 GetPoint(float height, float angle);
	float GetRadius(float height);
	void GenerateMesh(Mesh* mesh);
	bool isInEnvelope(glm::vec3 point);
private:

};

glm::vec3 SurfaceOfRevelutionEnvelope::GetPoint(float height, float angle) {
	float radius = GetRadius(height);
	glm::vec3 retVal = glm::vec3(radius * glm::sin(2.0f * glm::pi<float>() * angle / 360.0f), height, radius * glm::cos(2.0f * glm::pi<float>() * angle / 360.0f));
	return retVal;
}

float SurfaceOfRevelutionEnvelope::GetRadius(float height) {
	if (height >= _YMin || height <= _YMax) {
		return glm::sin(glm::pi<float>() * height / (_YMax - _YMin));
	}
	return 0;
}
void SurfaceOfRevelutionEnvelope::GenerateMesh(Mesh* mesh) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> triangles;


	mesh->Set(&vertices, &triangles);
}
bool SurfaceOfRevelutionEnvelope::isInEnvelope(glm::vec3 point) {
	float height = point.y;
	float distance = glm::sqrt(point.x * point.x + point.z * point.z);
	return GetRadius(height) > distance;
}

#endif SURFACEOFREVOLUTIONENVELOPE_H

