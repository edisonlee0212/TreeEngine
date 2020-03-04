#ifndef TREESKELETON_H
#define TREESKELETON_H

#include <vector>

struct TreeNode {
	TreeNode(float thickness, glm::vec3 position, glm::vec3 fromPosition) {
		transform = Transform();
		transform.SetPosition(position);
		transform.SetScale(glm::vec3(thickness));
		transform.LookAt(position);
		p0 = nullptr;
		p1 = nullptr;
		p2 = nullptr;
		p3 = nullptr;
		p4 = nullptr;
		p5 = nullptr;
		p6 = nullptr;
		p7 = nullptr;
		f0 = nullptr;
		f1 = nullptr;
		f2 = nullptr;
		f3 = nullptr;
		f4 = nullptr;
		f5 = nullptr;
	}
	void ConstructBox5(Point* fp0, Point* fp1, Point* fp2, Point* fp3, Face* ff0, Face* ff1, Face* ff2, Face* ff3) {
		//Need to add 8 connections
		p0 = fp3;
		p1 = fp0;
		p2 = new Point(glm::vec3(-0.5f, 0.5f, -0.5f));
		p3 = new Point(glm::vec3(-0.5f, 0.5f, 0.5f));
		p4 = fp2;
		p5 = fp1;
		p6 = new Point(glm::vec3(0.5f, 0.5f, -0.5f));
		p7 = new Point(glm::vec3(0.5f, 0.5f, 0.5f));
		f0 = new Face(0, p0, p2, p3, p1);
		f0->AttachPoints();
		f1 = new Face(1, p1, p5, p4, p0);
		f1->AttachPoints();
		f2 = new Face(2, p0, p4, p6, p2);
		f2->AttachPoints();
		f3 = new Face(3, p4, p5, p7, p6);
		f3->AttachPoints();
		f4 = new Face(4, p6, p7, p3, p2);
		f4->AttachPoints();

		f0->f3 = f1;
		f1->f3 = f0;

		f0->f0 = f2;
		f1->f2 = f2;
		f2->f3 = f0;
		f2->f0 = f1;

		f3->f0 = f1;
		f3->f3 = f2;
		f2->f1 = f3;
		f1->f1 = f3;

		f4->f2 = f0;
		f4->f3 = f2;
		f4->f0 = f3;
		f0->f1 = f4;
		f2->f2 = f4;
		f3->f2 = f4;


		f5->f0 = f0;
		f5->f3 = f1;
		f5->f1 = f4;
		f5->f2 = f3;

		f0->f2 = f5;
		f1->f0 = f5;
		f3->f1 = f5;
		f4->f1 = f5;
	}

	void ConstructBox6() {
		float scale = transform.GetScale().x;
		glm::vec3 position = transform.GetPosition();
		p0 = new Point(glm::vec3(-0.5f, -0.5f, -0.5f) * scale + position);
		p1 = new Point(glm::vec3(-0.5f, -0.5f, 0.5f) * scale + position);
		p2 = new Point(glm::vec3(-0.5f, 0.5f, -0.5f) * scale + position);
		p3 = new Point(glm::vec3(-0.5f, 0.5f, 0.5f) * scale + position);
		p4 = new Point(glm::vec3(0.5f, -0.5f, -0.5f) * scale + position);
		p5 = new Point(glm::vec3(0.5f, -0.5f, 0.5f) * scale + position);
		p6 = new Point(glm::vec3(0.5f, 0.5f, -0.5f) * scale + position);
		p7 = new Point(glm::vec3(0.5f, 0.5f, 0.5f) * scale + position);
		f0 = new Face(0, p0, p2, p3, p1);
		f0->AttachPoints();
		f1 = new Face(1, p1, p5, p4, p0);
		f1->AttachPoints();
		f2 = new Face(2, p0, p4, p6, p2);
		f2->AttachPoints();
		f3 = new Face(3, p4, p5, p7, p6);
		f3->AttachPoints();
		f4 = new Face(4, p6, p7, p3, p2);
		f4->AttachPoints();
		f5 = new Face(5, p1, p3, p7, p5);
		f5->AttachPoints();
		f0->f3 = f1;
		f1->f3 = f0;

		f0->f0 = f2;
		f1->f2 = f2;
		f2->f3 = f0;
		f2->f0 = f1;

		f3->f0 = f1;
		f3->f3 = f2;
		f2->f1 = f3;
		f1->f1 = f3;

		f4->f2 = f0;
		f4->f3 = f2;
		f4->f0 = f3;
		f0->f1 = f4;
		f2->f2 = f4;
		f3->f2 = f4;

		f5->f0 = f0;
		f5->f3 = f1;
		f5->f1 = f4;
		f5->f2 = f3;
		f0->f2 = f5;
		f1->f0 = f5;
		f3->f1 = f5;
		f4->f1 = f5;
	}

	Transform transform;
	Point* p0;
	Point* p1;
	Point* p2;
	Point* p3;
	Point* p4;
	Point* p5;
	Point* p6;
	Point* p7;

	Face* f0;
	Face* f1;
	Face* f2;
	Face* f3;
	Face* f4;
	Face* f5;
};

class TreeBranch {
public:
	TreeBranch(float thickNess, TreeBranch* _Parent, glm::vec3 position, int fromDirection = -1)
		: _ThickNess(thickNess)
		, _Parent(_Parent)
		, _SelfNode(TreeNode(thickNess, position,
			_Parent == nullptr ? position : _Parent->GetSelfNode()->transform.GetPosition()))
		, _FromDirection(fromDirection)
	{
		_Chain = std::vector<TreeNode>();
		std::vector<TreeBranch>();
		for (auto i : _Occupied) i = false;
		//Build _Chain to _Parent
		if (_Parent != nullptr) {
			glm::vec3 parentPosition = _Parent->GetSelfNode()->transform.GetPosition();
			float distance = glm::distance(position, parentPosition);
			ConstructChain(distance, parentPosition, thickNess);
			_SelfNode.transform.LookAt(parentPosition);
			

		}
		_SelfNode.ConstructBox6();
	}

	void GatherFaces(vector<Face*>* faces) {
		if (_SelfNode.f0 != nullptr)faces->push_back(_SelfNode.f0);
		if (_SelfNode.f1 != nullptr)faces->push_back(_SelfNode.f1);
		if (_SelfNode.f2 != nullptr)faces->push_back(_SelfNode.f2);
		if (_SelfNode.f3 != nullptr)faces->push_back(_SelfNode.f3);
		if (_SelfNode.f4 != nullptr)faces->push_back(_SelfNode.f4);
		if (_SelfNode.f5 != nullptr)faces->push_back(_SelfNode.f5);
		for (auto i : _ChildBranches) {
			i.GatherFaces(faces);
		}
	}

	TreeNode* GetSelfNode() { return &_SelfNode; }

	TreeBranch* AddBranch(float thickNess, glm::vec3 position, int direction) {
		if (direction < 0 || direction > 4 || _Occupied[direction]) return nullptr;
		_Occupied[direction] = true;
		TreeBranch branch = TreeBranch(thickNess, this, position, direction);
		_ChildBranches.push_back(branch);
		return &branch;
	}
private:
	void ConstructChain(float distance, glm::vec3 parentPosition, float thickNess) {
		/*int size = distance / thickNess + 1;
		glm::vec3 positionDifference = (_SelfNode.transform.GetPosition() - parentPosition) / (float) size;
		for (int i = 0; i < size; i++) {

		}*/

	}
	float _ThickNess;
	TreeNode _SelfNode;
	std::vector<TreeBranch> _ChildBranches;
	bool _Occupied[5];
	std::vector<TreeNode> _Chain;
	TreeBranch* _Parent;
	int _FromDirection;
};

class TreeSkeleton {
public:
	TreeSkeleton() : _RootBranch(TreeBranch(1.0f, nullptr, glm::vec3(0.0f, 0.0f, 0.0f))) {
		auto branch = _RootBranch.AddBranch(1.0f, glm::vec3(0.0f, 2.0f, 0.0f), 0);
	}
	void GenerateSurface(vector<Face*>* faces) {
		_RootBranch.GatherFaces(faces);
	}
private:
	TreeBranch _RootBranch;
};

#endif TREESKELETON_H
