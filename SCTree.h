#ifndef SCTREE_H
#define SCTREE_H
#include "SCBranch.h"
class SCTree {
public:
	SCBranch* mRoot;
	std::vector<SCBranch*> mGrowingBranches;
	bool isGrowing;
	int maxGrowIteration;
	glm::vec3 pos;
	Material* material;
	std::vector<glm::mat4> matrices;
	SCTree(glm::vec3 pos, Material* mat)
		: pos(pos),
		material(mat),
		mGrowingBranches(std::vector<SCBranch*>()),
		isGrowing(false),
		mRoot(new SCBranch(mat, pos, nullptr, true, 1)),
		maxGrowIteration(mRoot->growIteration)
	{

	}

	void Draw() {
		Graphics::DrawMeshInstanced(Default::Primitives::Cone, material, &matrices[0], World::camera, matrices.size());
	}

	void CollectPoints() {
		mRoot->CollectPoint(&matrices);
	}

	~SCTree() {
		delete mRoot;
	}

	void GrowTrunk(float growDist, float attractionDist, Envelope* envelope, glm::vec3 tropism) {
		float minDist = 9999999;
		bool found = false;
		int timeOut = 1000;
		SCBranch* currentBranch = mRoot;
		auto points = envelope->GetPointPositions();
		while (!found && timeOut > 0) {
			for (int i = 0; i < points->size() && !found; i++) {
				float dist = glm::distance(currentBranch->pos, points->at(i));
				currentBranch->growDir += glm::normalize(points->at(i) - currentBranch->pos);
				if (dist < minDist) {
					minDist = dist;
					if (minDist < attractionDist) found = true;
				}
			}
			if (!found) {
				auto newBranch = currentBranch->Grow(growDist, true, tropism);
				if (newBranch->growIteration > maxGrowIteration) maxGrowIteration = newBranch->growIteration;
				currentBranch = newBranch;
			}
			else
			{
				currentBranch->growDir = glm::vec3(0.0f);
				mGrowingBranches.push_back(currentBranch);
			}
			timeOut--;
		}
		if (timeOut < 0) {
			Debug::Log("Error generating the trunk");
		}
		isGrowing = true;
	}

	void GrowTreeIteration(float growDist, float attractionDist, float removeDist, Envelope* envelope, glm::vec3 tropism) {
		if (!isGrowing) {
			return;
		}
		auto pointList = envelope->GetPointPositions();

		for (int i = 0; i < pointList->size(); i++) {
			auto point = pointList->at(i);
			float minDist = 9999999;
			int minDistIndex = -1;
			int branchNum = mGrowingBranches.size();
			for (int i = 0; i < branchNum; i++) {
				float dist = glm::distance(point, mGrowingBranches[i]->pos);
				if (dist < minDist) {
					minDist = dist;
					minDistIndex = i;
				}
			}
			if (minDist <= attractionDist && minDistIndex >= 0) {
				mGrowingBranches[minDistIndex]->growDir += glm::normalize(point - mGrowingBranches[minDistIndex]->pos);
			}
		}

		bool addedNewBranch = false;
		int branchNum = mGrowingBranches.size();
		for (int i = 0; i < branchNum; i++) {
			SCBranch* newBranch = mGrowingBranches[i]->Grow(growDist, false, tropism);
			if (newBranch == nullptr) {
				mGrowingBranches.erase(mGrowingBranches.begin() + i);
				i--;
				branchNum--;
			}
			else
			{
				mGrowingBranches.push_back(newBranch);
				if (newBranch->growIteration > maxGrowIteration) maxGrowIteration = newBranch->growIteration;
				addedNewBranch = true;
			}
		}
		if (!addedNewBranch) {
			isGrowing = false;
		}
		for (int i = 0; i < pointList->size(); i++) {
			bool rm = false;
			for (int j = 0; j < mGrowingBranches.size() && !rm; j++) {
				if (glm::distance(pointList->at(i), mGrowingBranches[j]->pos) <= removeDist) {
					envelope->DeletePoint(i);
					rm = true;
					i--;
				}
			}
		}
	}
};

#endif SCTREE_H
