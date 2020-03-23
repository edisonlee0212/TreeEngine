#ifndef SCBRANCH_H
#define SCBRANCH_H
class SCTree;
class SCBranch {
public:
	SCTree* tree;
	glm::vec3 pos;
	glm::vec3 growDir;
	int growIteration;
	float radius;
	SCBranch* parent;
	std::vector<SCBranch*> mChildren;

	bool hasLeaves;
	bool isTrunk;

	SCBranch(SCTree* tree, glm::vec3 pos, SCBranch* parent, bool isTrunk, int growIteration, float initialRadius = 0.01f)
		: tree(tree),
		pos(pos),
		parent(parent),
		isTrunk(isTrunk),
		growIteration(growIteration),
		radius(initialRadius),
		growDir(glm::vec3(0.0f)),
		hasLeaves(false),
		mChildren(std::vector<SCBranch*>())
	{

	}

	SCBranch* Grow(float growDist, bool growTrunk, glm::vec3 tropism) {
		return nullptr;
	}
};
#endif SCBRANCH_H
