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
	SCTree(glm::vec3 pos, Material mat)
		: pos(pos),
		mGrowingBranches(std::vector<SCBranch*>()),
		isGrowing(false),
		mRoot(new SCBranch(this, pos, nullptr, true, 1)),
		maxGrowIteration(mRoot->growIteration)
	{

	}

	void GrowTrunk(float growDist, float attractionDist, Envelope* envelope, glm::vec3 tropism) {
		float minDist = 99999;
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
};

#endif SCTREE_H
