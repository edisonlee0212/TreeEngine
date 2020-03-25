#ifndef SCBRANCHMESH_H
#define SCBRANCHMESH_H
class SCBranchMeshRing {
public:

};

class SCBranchMesh
{
public:
	glm::vec3 startPos;
	glm::vec3 endPos;
	float startRadius;
	float endRadius;
	SCBranchMesh(glm::vec3 startPos, glm::vec3 endPos, float startRadius, float endRadius) {

	}
};

#endif SCBRANCHMESH_H