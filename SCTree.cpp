#include "SCTree.h"

SCTree::SCTree(glm::vec3 position, Material* pointMaterial, Material* meshMaterial)
	: position(position),
	pointMaterial(pointMaterial),
	meshMaterial(meshMaterial),
	mGrowingBranches(std::vector<SCBranch*>()),
	needsToGrow(false),
	mRoot(new SCBranch(pointMaterial, position, nullptr, true, 1)),
	maxGrowIteration(mRoot->growIteration),
	meshGenerated(false)
{

}

void SCTree::Draw() {
	
	if (matrices.size() > 0) {
		if (meshGenerated) {
			glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);
			matrix = glm::scale(matrix, glm::vec3(1.0f));
			Graphics::DrawMesh(mesh, matrix, meshMaterial, World::MainCamera);
		}
		else Graphics::DrawMeshInstanced(Default::Primitives::Cube, pointMaterial, &matrices[0], World::MainCamera, matrices.size());
	}
}

SCTree::~SCTree() {
	delete mRoot;
}

void SCTree::GrowTrunk(float growDist, float attractionDist, SCEnvelope* envelope, glm::vec3 tropism) {
	bool found = false;
	int timeOut = 1000;
	SCBranch* currentBranch = mRoot;
	auto pointsList = envelope->GetPointPositions();
	auto size = pointsList->size();
	while (!found && timeOut > 0) {
		for (int i = 0; i < size; i++) {
			auto point = pointsList->at(i);
			float dist = glm::distance(currentBranch->position, point);
			if (dist < attractionDist) {
				found = true;
				currentBranch->growDir = glm::vec3(0.0f);
				mGrowingBranches.push_back(currentBranch);
			}
			currentBranch->growDir += point - currentBranch->position;
		}
		if (!found) {
			auto newBranch = currentBranch->Grow(growDist, true, tropism);
			if (newBranch->growIteration > maxGrowIteration) maxGrowIteration = newBranch->growIteration;
			currentBranch = newBranch;
		}
		timeOut--;
	}
	if (timeOut < 0) {
		Debug::Log("Error generating the trunk");
	}
	needsToGrow = true;
}

void SCTree::Grow(float growDist, float attractionDist, float removeDist, SCEnvelope* envelope, glm::vec3 tropism,
	float distDec, float minDist, float decimationDistChild, float decimationDistParent) {
	auto pointsList = envelope->GetPointPositions();
	for (int i = 0; i < pointsList->size(); i++) {
		auto point = pointsList->at(i);
		float minDist = 9999999;
		int minIndex = -1;
		int size = mGrowingBranches.size();
		for (int i = 0; i < size; i++) {
			float dist = glm::distance(point, mGrowingBranches[i]->position);
			if (dist < minDist) {
				minDist = dist;
				minIndex = i;
			}
		}
		if (minDist <= attractionDist && minIndex >= 0) {
			mGrowingBranches[minIndex]->growDir += glm::normalize(point - mGrowingBranches[minIndex]->position);
		}
	}

	bool addedNewBranch = false;
	auto size = mGrowingBranches.size();
	for (int i = 0; i < size; i++) {
		SCBranch* newBranch = mGrowingBranches[i]->Grow(growDist, false, tropism, distDec, minDist, decimationDistChild, decimationDistParent);
		if (newBranch == nullptr) {
			mGrowingBranches.erase(mGrowingBranches.begin() + i);
			i--;
			size--;
		}
		else
		{
			mGrowingBranches.push_back(newBranch);
			if (newBranch->growIteration > maxGrowIteration) maxGrowIteration = newBranch->growIteration;
			addedNewBranch = true;
		}
	}

	size = pointsList->size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < mGrowingBranches.size(); j++) {
			if (glm::distance(pointsList->at(i), mGrowingBranches[j]->position) <= removeDist) {
				envelope->DeletePointSwapBack(i);
				size--;
				i--;
				break;
			}
		}
	}

	if (!addedNewBranch) {
		needsToGrow = false;
		Debug::Log("Grow complete.");

		envelope->Clear();

		NodeRelocation();
		Debug::Log("Node Relocation complete.");

		CalculateRadius();
		Debug::Log("Radius Calculation complete.");

		NodeSubdivision();
		Debug::Log("Node Subdivision complete.");

		CollectPoints();
		Debug::Log("Points Collection complete.");

		CalculateMesh();
		Debug::Log("Mesh Generation complete.");
		return;
	}

	CalculateRadius();
	CollectPoints();
}

void SCTree::CalculateMesh() {
	meshGenerated = false;
	if (mesh != nullptr) delete mesh;
	mesh = new Mesh();
	std::vector<Vertex>* vertices = new std::vector<Vertex>();
	std::vector<unsigned int>* triangles = new std::vector<unsigned int>();
	mRoot->CalculateMesh(position, vertices);
	int size = vertices->size();
	for (int i = 0; i < size; i++) {
		triangles->push_back(i);
	}
	mesh->Set(vertices, triangles);
	delete vertices;
	delete triangles;
	mesh->RecalculateNormal();
	meshGenerated = true;
}