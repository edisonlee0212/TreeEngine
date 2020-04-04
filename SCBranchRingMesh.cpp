#include "SCBranchRingMesh.h"

SCBranchRingMesh::SCBranchRingMesh(glm::vec3 startPosition, glm::vec3 endPosition, glm::vec3 startAxis, glm::vec3 endAxis, float startRadius, float endRadius)
	: StartPosition(startPosition),
	EndPosition(endPosition),
	StartAxis(startAxis),
	EndAxis(endAxis),
	StartRadius(startRadius),
	EndRadius(endRadius)
{

}

void SCBranchRingMesh::AppendPoints(std::vector<Vertex>* vertices, int resolution) {
	std::vector<Vertex> startRing;
	std::vector<Vertex> endRing;
	float angleStep = 360.0f / (float)(resolution - 1);
	for (int i = 0; i < resolution - 1; i++) {
		startRing.push_back(GetPoint(angleStep * i, true));
	}
	for (int i = 0; i < resolution - 1; i++) {
		endRing.push_back(GetPoint(angleStep * i, false));
	}

	for (int i = 0; i < resolution - 2; i++) {
		startRing[i].TexCoords = glm::vec2(0.0f, 0.0f);
		startRing[i + 1].TexCoords = glm::vec2(1.0f, 0.0f);
		endRing[i].TexCoords = glm::vec2(0.0f, 1.0f);
		endRing[i + 1].TexCoords = glm::vec2(1.0f, 1.0f);
		vertices->push_back(startRing[i]);
		vertices->push_back(startRing[i + 1]);
		vertices->push_back(endRing[i]);
		vertices->push_back(endRing[i + 1]);
		vertices->push_back(endRing[i]);
		vertices->push_back(startRing[i + 1]);
	}
	startRing[resolution - 2].TexCoords = glm::vec2(0.0f, 0.0f);
	startRing[0].TexCoords = glm::vec2(1.0f, 0.0f);
	endRing[resolution - 2].TexCoords = glm::vec2(0.0f, 1.0f);
	endRing[0].TexCoords = glm::vec2(1.0f, 1.0f);
	vertices->push_back(startRing[resolution - 2]);
	vertices->push_back(startRing[0]);
	vertices->push_back(endRing[resolution - 2]);
	vertices->push_back(endRing[0]);
	vertices->push_back(endRing[resolution - 2]);
	vertices->push_back(startRing[0]);
}

inline Vertex SCBranchRingMesh::GetPoint(float angle, bool isStart) {
	Vertex retVal;

	glm::vec3 tmp = glm::vec3(0.0f);
	tmp.x = glm::sin(angle);
	tmp.y = 0;
	tmp.z = glm::cos(angle);
	
	glm::vec3 direction = glm::normalize(glm::cross(tmp, isStart ? this->StartAxis : this->EndAxis));

	retVal.Position = (isStart ? this->StartPosition : this->EndPosition) + direction * (isStart ? this->StartRadius : this->EndRadius);

	return retVal;
}