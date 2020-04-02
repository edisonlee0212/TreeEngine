#include "SCEnvelope.h"

SCEnvelope::SCEnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Material* material) :
	_XMax(xMax),
	_YMax(yMax),
	_ZMax(zMax),
	_XMin(xMin),
	_YMin(yMin),
	_ZMin(zMin),
	_PointMat(material),
	_PointsGenerated(false)
{

}
SCEnvelope::~SCEnvelope() {

}

void SCEnvelope::Draw() {
	if (_PointPositions.size() > 0) {
		Graphics::DrawMeshInstanced(Default::Primitives::Sphere, _PointMat, &_PointMatrices[0], World::MainCamera, _PointMatrices.size());
	}
}
bool SCEnvelope::PointsGenerated() { return _PointsGenerated; }
void SCEnvelope::GeneratePoints(int amount) {
	Clear();
	int size = 0;
	while (size < amount) {
		glm::vec3 point = glm::vec3(_XMin + (_XMax - _XMin) * (float)rand() / (RAND_MAX),
			_YMin + (_YMax - _YMin) * (float)rand() / (RAND_MAX),
			_ZMin + (_ZMax - _ZMin) * (float)rand() / (RAND_MAX));
		if (isInEnvelope(point)) {
			AddPoint(point);
			size++;
		}
	}
	_PointsGenerated = true;
}

void SCEnvelope::AddPoint(glm::vec3 point) {
	glm::mat4 matrix = glm::translate(glm::mat4(1.0f), point);
	matrix = glm::scale(matrix, glm::vec3(0.01f));
	_PointPositions.push_back(point);
	_PointMatrices.push_back(matrix);
}
void SCEnvelope::DeletePointSwapBack(int index) {
	_PointPositions[index] = _PointPositions.back();
	_PointMatrices[index] = _PointMatrices.back();
	_PointPositions.pop_back();
	_PointMatrices.pop_back();
}
std::vector<glm::vec3>* SCEnvelope::GetPointPositions() {
	return &_PointPositions;
}
void SCEnvelope::Clear() {
	_PointPositions.clear();
	_PointMatrices.clear();
	_PointsGenerated = false;
}