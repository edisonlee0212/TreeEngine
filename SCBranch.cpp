#include "SCBranch.h"
#include "Default.h"
#include "BezierCurve.h"
SCBranch::SCBranch(Material* mat, glm::vec3 position, SCBranch* parent, bool isTrunk, int growIteration, float initialRadius)
	: mat(mat),
	position(position),
	parent(parent),
	isTrunk(isTrunk),
	growIteration(growIteration),
	radius(initialRadius),
	growDir(glm::vec3(0.0f)),
	hasLeaves(false),
	mChildren(std::vector<SCBranch*>()),
	transform(glm::mat4(0.0f))
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

float SCBranch::CalculateRadius(int maxGrowIteration, float n, float minRadius) {
	if (mChildren.size() == 0) return radius;
	float radVal = 0.0f;
	for (auto child : mChildren) {
		radVal += glm::pow(child->CalculateRadius(maxGrowIteration, n), n);
	}
	if (mChildren.empty()) radius = minRadius;
	else radius = glm::pow(radVal, 1.0f / n);
	transform = glm::translate(glm::mat4(1.0f), position);
	transform = glm::scale(transform, glm::vec3(radius / 2.0f));
	return radius;
}

SCBranch* SCBranch::Grow(float growDist, bool growTrunk, glm::vec3 tropism, float distDec, float minDist, float decimationDistChild, float decimationDistParent) {
	if (growDir == glm::vec3(0.0f)) return nullptr;
	float actualDist = growDist - distDec * growIteration;
	if (actualDist < minDist) actualDist = minDist;
	glm::vec3 newPos = position + glm::normalize(glm::normalize(growDir) + tropism) * actualDist;

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
	BezierCurve curve = BezierCurve(fromPos, fromPos + distance / 3.0f * fromDir, position - distance / 3.0f * direction, position);
	float posStep = 1.0f / (float)amount;
	glm::vec3 dirStep = (direction - fromDir) / (float)amount;
	float radiusStep = (radius - fromRadius) / (float)amount;

	for (int i = 1; i < amount; i++) {
		mRings.push_back(SCBranchRingMesh(
			curve.GetPoint(posStep * (i - 1)), curve.GetPoint(posStep * i),
			fromDir + (float)(i - 1) * dirStep, fromDir + (float)i * dirStep,
			fromRadius + (float)(i - 1) * radiusStep, fromRadius + (float)i * radiusStep));
	}
	if (amount > 1)mRings.push_back(SCBranchRingMesh(curve.GetPoint(1.0f - posStep), position, direction - dirStep, direction, radius - radiusStep, radius));
	else mRings.push_back(SCBranchRingMesh(fromPos, position, fromDir, direction, fromRadius, radius));
	isSubdivided = true;

	for (auto i : mChildren) {
		i->Subdivision(position, direction, radius);
	}
}

void SCBranch::CalculateMesh(glm::vec3 rootPos, std::vector<Vertex>* vertices, int resolution) {
	for (auto i : mRings) {
		i.AppendPoints(vertices, resolution);
	}
	if (mChildren.empty() && !mRings.empty()) {
		std::vector<Vertex> endRing;
		float angleStep = 360.0f / (float)(resolution);
		Vertex archetype;
		for (int i = 0; i < resolution; i++) {
			archetype.Position = mRings.back().GetPoint(angleStep * i, false);
			endRing.push_back(archetype);
		}
		Vertex center = Vertex();
		center.Position = mRings.back().EndPosition;
		center.TexCoords = glm::vec2(1.0f, 1.0f);
		for (size_t i = 0; i < (size_t)resolution - 1; i++) {
			endRing[i].TexCoords = glm::vec2(0.0f, 0.0f);
			endRing[i + 1].TexCoords = glm::vec2(0.0f, 1.0f);
			vertices->push_back(endRing[i]);
			vertices->push_back(endRing[i + 1]);
			vertices->push_back(center);
		}
		vertices->push_back(endRing[(size_t)resolution - 1]);
		vertices->push_back(endRing[0]);
		vertices->push_back(center);
	}
	for (auto i : mChildren) {
		i->CalculateMesh(rootPos, vertices, resolution);
	}
}

void SCBranch::GenerateOrgan(std::vector<glm::mat4>* matrices, int maxGrowIteration, int maxLeaf) {
	for (auto i : mChildren) i->GenerateOrgan(matrices, maxGrowIteration);
	if (isTrunk) return;
	int leafAmount = (float)maxLeaf * growIteration / maxGrowIteration;
	if (leafAmount == 0) leafAmount = rand() / (RAND_MAX) * 2.0f;
	for (int i = 0; i < leafAmount; i++) {
		glm::mat4 matrix = glm::mat4(1.0f);
		float random = (float)rand();
		random /= RAND_MAX;
		if (random == 1.0f) random = 0.9f;
		auto ring = mRings[(size_t)(random * mRings.size())];
		auto position = ring.GetPoint(random * 360.0f, false);
		position = ring.EndPosition + (position - ring.EndPosition) * 3.0f;

		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, 2 * glm::pi<float>() * random, ring.EndAxis);
		matrix = glm::scale(matrix, glm::vec3(0.05f));
		matrices->push_back(matrix);
	}
}