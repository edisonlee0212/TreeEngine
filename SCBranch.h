#ifndef SCBRANCH_H
#define SCBRANCH_H
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
		transform = glm::translate(glm::mat4(1.0f), pos);
		transform = glm::scale(transform, glm::vec3(0.02f, 0.02f, 0.02f));
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
		//Debug::Log("[" + std::to_string(pos.x) + "][" + std::to_string(pos.y) + "][" + std::to_string(pos.z) + "]");
		glm::vec3 fromDir = glm::vec3(0.0f, 1.0f, 0.0f);
		if(parent != nullptr) fromDir= pos - parent->pos;
		float angle = glm::acos(glm::dot(glm::normalize(fromDir), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))));
		glm::vec3 axis = glm::normalize(glm::cross(fromDir, glm::vec3(0.0f, 1.0f, 0.0f)));
		transform = glm::rotate(transform, angle, axis);
		matrices->push_back(transform);
		for (auto i : mChildren) i->CollectPoint(matrices);
	}

	SCBranch* Grow(float growDist, bool growTrunk, glm::vec3 tropism) {
		if (growDir == glm::vec3(0.0f)) return nullptr;
		glm::vec3 newPos = pos + glm::normalize(glm::normalize(growDir) + tropism) * growDist;
		for (auto child : mChildren) {
			if (glm::distance(child->pos, newPos) <= 0.05f) {
				growDir = glm::vec3(0.0f);
				return nullptr;
			}
		}
		if (parent != nullptr)
		{
			if (glm::distance(parent->pos, newPos) <= 0.05f) {
				growDir = glm::vec3(0.0f);
				return nullptr;
			}
		}
		auto newBranch = new SCBranch(mat, newPos, this, growTrunk, growIteration + 1);
		growDir = glm::vec3(0.0f);
		mChildren.push_back(newBranch);


		return newBranch;
	}
};
#endif SCBRANCH_H
