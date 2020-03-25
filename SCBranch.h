#ifndef SCBRANCH_H
#define SCBRANCH_H
#include "SCBranchMesh.h"
class SCBranch {
public:
	Material* mat;
	glm::vec3 pos;
	glm::vec3 growDir;
	int growIteration;
	float radius;
	SCBranch* parent;
	std::vector<SCBranch*> mChildren;
	glm::mat4 transform;
	bool hasLeaves;
	bool isTrunk;
	std::vector<glm::vec3> mBranchPosChain;
	std::vector<float> mBranchRadiusChain;
	bool isSubdivided;
	SCBranch(Material* mat, glm::vec3 pos, SCBranch* parent, bool isTrunk, int growIteration, float initialRadius = 0.01f)
		: mat(mat),
		pos(pos),
		parent(parent),
		isTrunk(isTrunk),
		growIteration(growIteration),
		radius(initialRadius),
		growDir(glm::vec3(0.0f)),
		hasLeaves(false),
		mChildren(std::vector<SCBranch*>())
	{
		isSubdivided = false;
	}

	~SCBranch() {
		for (auto i : mChildren) {
			delete i;
		}
	}
	void Draw() {
		Graphics::DrawMesh(Default::Primitives::Cube, transform, mat, World::camera);
		for (auto i : mChildren) i->Draw();
	}

	void CollectPoint(std::vector<glm::mat4>* matrices) {
		if (!isSubdivided) {
			//Debug::Log("[" + std::to_string(pos.x) + "][" + std::to_string(pos.y) + "][" + std::to_string(pos.z) + "]");
			/*glm::vec3 fromDir = glm::vec3(0.0f, 1.0f, 0.0f);
			if(parent != nullptr) fromDir= pos - parent->pos;
			float angle = glm::acos(glm::dot(glm::normalize(fromDir), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))));
			glm::vec3 axis = glm::normalize(glm::cross(fromDir, glm::vec3(0.0f, 1.0f, 0.0f)));
			transform = glm::rotate(transform, angle, axis);*/
			matrices->push_back(transform);
			for (auto i : mChildren) i->CollectPoint(matrices);
		}
		else {
			auto size = mBranchPosChain.size();
			glm::mat4 transform = glm::mat4(1.0f);
			for (int i = 0; i < size; i++) {
				transform = glm::translate(glm::mat4(1.0f), mBranchPosChain[i]);
				transform = glm::scale(transform, glm::vec3(mBranchRadiusChain[i] / 2.0f));
				matrices->push_back(transform);
			}
			for (auto i : mChildren) i->CollectPoint(matrices);
		}
	}

	float CalculateRadius(int maxGrowIteration, float n = 3.0f) {
		if (mChildren.size() == 0) return radius;
		float radVal = 0.0f;
		for (auto child : mChildren) {
			radVal += glm::pow(child->CalculateRadius(maxGrowIteration, n), n);

		}
		radius = glm::pow(radVal, 1.0f / n);
		transform = glm::translate(glm::mat4(1.0f), pos);
		transform = glm::scale(transform, glm::vec3(radius / 2.0f));
		return radius;
	}

	SCBranch* Grow(float growDist, bool growTrunk, glm::vec3 tropism, float distDec = 0.015f, float minDist = 0.1f, float decimationDistChild = 0.05f, float decimationDistParent = 0.05f) {
		if (growDir == glm::vec3(0.0f)) return nullptr;
		float actualDist = growDist - distDec * growIteration;
		if (actualDist < minDist) actualDist = minDist;
		glm::vec3 newPos = pos + glm::normalize(glm::normalize(growDir) + tropism) * actualDist / (float)(mChildren.size() + 1);
		growDir = glm::vec3(0.0f);
		for (auto child : mChildren) {
			if (glm::distance(child->pos, newPos) <= decimationDistChild) return nullptr;
		}
		if (parent && glm::distance(parent->pos, newPos) <= decimationDistParent) return nullptr;

		auto newBranch = new SCBranch(mat, newPos, this, growTrunk, growTrunk ? growIteration : growIteration + 1);
		mChildren.push_back(newBranch);
		return newBranch;
	}

	void Relocation() {
		for (auto i : mChildren) {
			i->Relocation();
			glm::vec3 dir = pos - i->pos;
			i->pos += dir / 2.0f;
		}
	}

	void Subdivision(glm::vec3 fromPos, float fromRadius) {
		auto distance = glm::distance(fromPos, pos);
		int amount = distance / ((fromRadius + radius) / 2.0f);

		glm::vec3 posStep = (pos - fromPos) / (float)amount;
		float radiusStep = (radius - fromRadius) / (float)amount;

		for (int i = 1; i < amount; i++) {
			mBranchPosChain.push_back(fromPos + (float)i * posStep);
			mBranchRadiusChain.push_back(fromRadius + (float)i * radiusStep);
		}

		mBranchPosChain.push_back(pos);
		mBranchRadiusChain.push_back(radius);

		isSubdivided = true;

		for (auto i : mChildren) {
			i->Subdivision(pos, radius);
		}
	}

	void CalculateMesh(glm::vec3 rootPos, std::vector<Vertex>* vertices, std::vector<unsigned int>* triangles) {
		

		for (auto i : mChildren) {
			i->CalculateMesh(rootPos, vertices, triangles);
		}
	}
};
#endif SCBRANCH_H
