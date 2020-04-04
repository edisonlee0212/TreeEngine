#include "SCBranch.h"
#include "Default.h"
SCBranch::SCBranch(Material* mat, glm::vec3 position, SCBranch* parent, bool isTrunk, int growIteration, float initialRadius)
	: mat(mat),
	position(position),
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

SCBranch::~SCBranch() {
	for (auto i : mChildren) {
		delete i;
	}
}
void SCBranch::Draw() {
	Graphics::DrawMesh(Default::Primitives::Cube, transform, mat, World::MainCamera);
	for (auto i : mChildren) i->Draw();
}

void SCBranch::CollectPoint(std::vector<glm::mat4>* matrices) {
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
		auto size = mRings.size();
		glm::mat4 transform = glm::mat4(1.0f);
		for (int i = 0; i < size; i++) {
			transform = glm::translate(glm::mat4(1.0f), mRings[i].EndPosition);
			transform = glm::scale(transform, glm::vec3(mRings[i].EndRadius / 2.0f));
			matrices->push_back(transform);
		}
		for (auto i : mChildren) i->CollectPoint(matrices);
	}
}

float SCBranch::CalculateRadius(int maxGrowIteration, float n) {
	if (mChildren.size() == 0) return radius;
	float radVal = 0.0f;
	for (auto child : mChildren) {
		radVal += glm::pow(child->CalculateRadius(maxGrowIteration, n), n);

	}
	radius = glm::pow(radVal, 1.0f / n);
	transform = glm::translate(glm::mat4(1.0f), position);
	transform = glm::scale(transform, glm::vec3(radius / 2.0f));
	return radius;
}

SCBranch* SCBranch::Grow(float growDist, bool growTrunk, glm::vec3 tropism, float distDec, float minDist, float decimationDistChild, float decimationDistParent) {
	if (growDir == glm::vec3(0.0f)) return nullptr;
	float actualDist = growDist - distDec * growIteration;
	if (actualDist < minDist) actualDist = minDist;
	glm::vec3 newPos = position + glm::normalize(glm::normalize(growDir) + tropism) * actualDist / (float)(mChildren.size() + 1);

	growDir = glm::vec3(0.0f);
	for (auto child : mChildren) {
		if (glm::distance(child->position, newPos) <= decimationDistChild) return nullptr;
	}
	if (parent && glm::distance(parent->position, newPos) <= decimationDistParent) return nullptr;

	auto newBranch = new SCBranch(mat, newPos, this, growTrunk, growTrunk ? growIteration : growIteration + 1);
	mChildren.push_back(newBranch);
	return newBranch;
}

void SCBranch::Relocation() {
	for (auto i : mChildren) {
		i->Relocation();
		glm::vec3 dir = position - i->position;
		i->position += dir / 2.0f;
	}
}

void SCBranch::Subdivision(glm::vec3 fromPos, glm::vec3 fromDir, float fromRadius) {
	auto distance = glm::distance(fromPos, position);
	int amount = distance / ((fromRadius + radius) / 2.0f);
	auto direction = glm::normalize(position - fromPos);
	glm::vec3 posStep = (position - fromPos) / (float)amount;
	glm::vec3 dirStep = (direction - fromDir) / (float)amount;
	float radiusStep = (radius - fromRadius) / (float)amount;

	for (int i = 1; i < amount; i++) {
		mRings.push_back(SCBranchRingMesh(
			fromPos + (float)(i - 1) * posStep, fromPos + (float)i * posStep,
			fromDir + (float)(i - 1)* dirStep, fromDir + (float)i * dirStep,
			fromRadius + (float)(i - 1) * radiusStep,fromRadius + (float)i * radiusStep));
	}
	if(amount > 1)mRings.push_back(SCBranchRingMesh(position - posStep, position, direction - dirStep, direction, radius - radiusStep, radius));

	isSubdivided = true;

	for (auto i : mChildren) {
		i->Subdivision(position, direction, radius);
	}
}

void SCBranch::CalculateMesh(glm::vec3 rootPos, std::vector<Vertex>* vertices) {
	for (auto i : mRings) {
		i.AppendPoints(vertices);
	}

	for (auto i : mChildren) {
		i->CalculateMesh(rootPos, vertices);
	}
}