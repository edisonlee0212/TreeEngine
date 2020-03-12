#ifndef TREESKELETON_H
#define TREESKELETON_H

#include <vector>

struct TreeNode {
	TreeNode(float thickness, glm::vec3 position, glm::vec3 fromPosition) {
		//transform = Transform();
		//transform.SetPosition(position);
		//transform.SetScale(glm::vec3(thickness));
		//transform.LookAt(position);
		translation.Value = position;
		scale.Value = glm::vec3(thickness);

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
	void ConstructBox5(std::vector<Point*>* points, Face* fromFace, int fromDirection) {
		//float scale = transform.GetScale().x;
		//glm::vec3 position = transform.GetPosition();
		
		p0 = new Point(glm::vec3(-0.5f, 0.5f, -0.5f) * scale.Value + translation.Value);
		p1 = new Point(glm::vec3(-0.5f, 0.5f, 0.5f) * scale.Value + translation.Value);
		p2 = new Point(glm::vec3(0.5f, 0.5f, -0.5f) * scale.Value + translation.Value);
		p3 = new Point(glm::vec3(0.5f, 0.5f, 0.5f) * scale.Value + translation.Value);
		points->push_back(p0);
		points->push_back(p1);
		points->push_back(p2);
		points->push_back(p3);
		switch (fromDirection)
		{
		case 0:
			p4 = fromFace->p1;
			p5 = fromFace->p0;
			p6 = fromFace->p2;
			p7 = fromFace->p3;
			break;
		case 1:
			p4 = fromFace->p3;
			p5 = fromFace->p2;
			p6 = fromFace->p0;
			p7 = fromFace->p1;
			break;
		case 2:
			p4 = fromFace->p2;
			p5 = fromFace->p1;
			p6 = fromFace->p3;
			p7 = fromFace->p0;
			break;
		case 3:
			p4 = fromFace->p2;
			p5 = fromFace->p1;
			p6 = fromFace->p3;
			p7 = fromFace->p0;
			break;
		case 4:
			p4 = fromFace->p3;
			p5 = fromFace->p2;
			p6 = fromFace->p0;
			p7 = fromFace->p1;
			break;
		default:
			break;
		}
		

		f0 = new Face(p1, p0, p2, p3);
		f0->AttachPoints();
		f1 = new Face(p0, p1, p5, p4);
		f1->AttachPoints();
		f2 = new Face(p2, p0, p4, p6);
		f2->AttachPoints();
		f3 = new Face(p7, p5, p1, p3);
		f3->AttachPoints();
		f4 = new Face(p6, p7, p3, p2);
		f4->AttachPoints();

		f0->f0 = f1;
		f0->f1 = f2;
		f0->f2 = f4;
		f0->f3 = f3;
		
		f1->f0 = f0;
		f1->f1 = f3;
		f1->f3 = f2;

		f2->f0 = f0;
		f2->f1 = f1;
		f2->f3 = f4;

		f3->f1 = f1;
		f3->f2 = f0;
		f3->f3 = f4;

		f4->f1 = f3;
		f4->f2 = f0;
		f4->f3 = f2;

		switch (fromDirection)
		{
		case 0:
			fromFace->f0->f0 = f1;
			fromFace->f1->f0 = f2;
			fromFace->f2->f2 = f4;
			fromFace->f3->f2 = f3;
			f1->f2 = fromFace->f0;
			f2->f2 = fromFace->f1;
			f4->f0 = fromFace->f2;
			f3->f0 = fromFace->f3;
			break;
		case 1:
			fromFace->f0->f0 = f4;
			fromFace->f1->f1 = f3;
			fromFace->f2->f2 = f1;
			fromFace->f3->f1 = f2;
			f1->f2 = fromFace->f2;
			f2->f2 = fromFace->f3;
			f4->f0 = fromFace->f0;
			f3->f0 = fromFace->f1;
			break;
		case 2:
			fromFace->f0->f1 = f3;
			fromFace->f1->f3 = f1;
			fromFace->f2->f1 = f2;
			fromFace->f3->f3 = f4;
			f1->f2 = fromFace->f1;
			f2->f2 = fromFace->f2;
			f4->f0 = fromFace->f3;
			f3->f0 = fromFace->f0;
			break;
		case 3:
			fromFace->f0->f3 = f3;
			fromFace->f1->f1 = f1;
			fromFace->f2->f3 = f2;
			fromFace->f3->f1 = f4;
			f1->f2 = fromFace->f1;
			f2->f2 = fromFace->f2;
			f4->f0 = fromFace->f3;
			f3->f0 = fromFace->f0;
			break;
		case 4:
			fromFace->f0->f0 = f4;
			fromFace->f1->f3 = f3;
			fromFace->f2->f2 = f1;
			fromFace->f3->f3 = f2;
			f1->f2 = fromFace->f2;
			f2->f2 = fromFace->f3;
			f4->f0 = fromFace->f0;
			f3->f0 = fromFace->f1;
			break;
		default:
			break;
		}
	}

	void ConstructBox6(std::vector<Point*>* points) {
		p0 = new Point(glm::vec3(-0.5f, 0.5f, -0.5f) * scale.Value + translation.Value);
		p1 = new Point(glm::vec3(-0.5f, 0.5f, 0.5f) * scale.Value + translation.Value);
		p2 = new Point(glm::vec3(0.5f, 0.5f, -0.5f) * scale.Value + translation.Value);
		p3 = new Point(glm::vec3(0.5f, 0.5f, 0.5f) * scale.Value + translation.Value);
		p4 = new Point(glm::vec3(-0.5f, -0.5f, -0.5f) * scale.Value + translation.Value);
		p5 = new Point(glm::vec3(-0.5f, -0.5f, 0.5f) * scale.Value + translation.Value);
		p6 = new Point(glm::vec3(0.5f, -0.5f, -0.5f) * scale.Value + translation.Value);
		p7 = new Point(glm::vec3(0.5f, -0.5f, 0.5f) * scale.Value + translation.Value);
		points->push_back(p0);
		points->push_back(p1);
		points->push_back(p2);
		points->push_back(p3);
		points->push_back(p4);
		points->push_back(p5);
		points->push_back(p6);
		points->push_back(p7);
		f0 = new Face(p1, p0, p2, p3);
		f0->AttachPoints();
		f1 = new Face(p0, p1, p5, p4);
		f1->AttachPoints();
		f2 = new Face(p2, p0, p4, p6);
		f2->AttachPoints();
		f3 = new Face(p7, p5, p1, p3);
		f3->AttachPoints();
		f4 = new Face(p6, p7, p3, p2);
		f4->AttachPoints();
		f5 = new Face(p7, p6, p4, p5);
		f5->AttachPoints();

		f0->f0 = f1;
		f0->f1 = f2;
		f0->f2 = f4;
		f0->f3 = f3;
		
		f5->f0 = f4;
		f5->f1 = f2;
		f5->f2 = f1;
		f5->f3 = f3;
		
		f1->f0 = f0;
		f1->f1 = f3;
		f1->f2 = f5;
		f1->f3 = f2;

		f4->f0 = f5;
		f4->f1 = f3;
		f4->f2 = f0;
		f4->f3 = f2;

		f2->f0 = f0;
		f2->f1 = f1;
		f2->f2 = f5;
		f2->f3 = f4;

		f3->f0 = f5;
		f3->f1 = f1;
		f3->f2 = f0;
		f3->f3 = f4;

	}

	Translation translation;
	Scale scale;
	Rotation rotation;

	//Transform transform;
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
	TreeBranch(std::vector<Point*>* points, float thickNess, TreeBranch* _Parent, glm::vec3 position, int fromDirection = -1)
		: _Points(points)
		, _ThickNess(thickNess)
		, _Parent(_Parent)
		, _SelfNode(TreeNode(thickNess, position,
			_Parent == nullptr ? position : _Parent->GetSelfNode()->translation.Value))
		, _FromDirection(fromDirection)
	{
		_Chain = std::vector<TreeNode*>();
		std::vector<TreeBranch>();
		_Occupied0 = false;
		_Occupied1 = false;
		_Occupied2 = false;
		_Occupied3 = false;
		_Occupied4 = false;
		//Build _Chain to _Parent
		if (_Parent != nullptr) {
			glm::vec3 parentPosition;
			switch (fromDirection)
			{
			case 0:
				parentPosition = _Parent->GetSelfNode()->translation.Value + glm::vec3(0.0f, 1.0f, 0.0f) * thickNess;
				break;
			case 1:
				parentPosition = _Parent->GetSelfNode()->translation.Value + glm::vec3(-1.0f, 0.0f, 0.0f) * thickNess;
				break;
			case 2:
				parentPosition = _Parent->GetSelfNode()->translation.Value + glm::vec3(0.0f, 0.0f, -1.0f) * thickNess;
				break;
			case 3:
				parentPosition = _Parent->GetSelfNode()->translation.Value + glm::vec3(1.0f, 0.0f, 0.0f) * thickNess;
				break;
			case 4:
				parentPosition = _Parent->GetSelfNode()->translation.Value + glm::vec3(0.0f, 0.0f, 1.0f) * thickNess;
				break;
			default:
				break;
			}

			float distance = glm::distance(position, parentPosition);
			ConstructChain(distance, parentPosition, thickNess, fromDirection);
		}
		else {
			_SelfNode.ConstructBox6(_Points);
		}
		
	}

	void GatherFaces(vector<Face*>* faces) {
		if (_SelfNode.f0 != nullptr)faces->push_back(_SelfNode.f0);
		if (_SelfNode.f1 != nullptr)faces->push_back(_SelfNode.f1);
		if (_SelfNode.f2 != nullptr)faces->push_back(_SelfNode.f2);
		if (_SelfNode.f3 != nullptr)faces->push_back(_SelfNode.f3);
		if (_SelfNode.f4 != nullptr)faces->push_back(_SelfNode.f4);
		if (_SelfNode.f5 != nullptr)faces->push_back(_SelfNode.f5);

		for (auto i : _Chain) {
			if (i->f0 != nullptr)faces->push_back(i->f0);
			if (i->f1 != nullptr)faces->push_back(i->f1);
			if (i->f2 != nullptr)faces->push_back(i->f2);
			if (i->f3 != nullptr)faces->push_back(i->f3);
			if (i->f4 != nullptr)faces->push_back(i->f4);
			if (i->f5 != nullptr)faces->push_back(i->f5);
		}

		for (auto i : _ChildBranches) {
			i->GatherFaces(faces);
		}
	}

	TreeNode* GetSelfNode() { return &_SelfNode; }

	TreeBranch* AddBranch(float thickNess, glm::vec3 position, int direction) {
		if (direction < 0 || direction > 4) return nullptr;
		switch (direction)
		{
		case 0:
			if (_Occupied0) return nullptr;
			_Occupied0 = true;
			break;
		case 1:
			if (_Occupied1) return nullptr;
			_Occupied1 = true;
			break;
		case 2:
			if (_Occupied2) return nullptr;
			_Occupied2 = true;
			break;
		case 3:
			if (_Occupied3) return nullptr;
			_Occupied3 = true;
			break;
		case 4:
			if (_Occupied4) return nullptr;
			_Occupied4 = true;
			break;
		default:
			break;
		}
		TreeBranch* branch = new TreeBranch(_Points, thickNess, this, position, direction);
		_ChildBranches.push_back(branch);
		return branch;
	}
private:
	void ConstructChain(float distance, glm::vec3 parentPosition, float thickNess, int fromDirection) {
		int size = distance / thickNess - 1;
		glm::vec3 positionDifference = (_SelfNode.translation.Value - parentPosition) / (float) (size + 1);
		glm::vec3 scaleDifference = (_SelfNode.scale.Value - _Parent->GetSelfNode()->scale.Value) / (float)(size+1);

		TreeNode* lastNode = new TreeNode(thickNess, parentPosition + positionDifference, parentPosition);

		switch (fromDirection)
		{
		case 0:
			lastNode->ConstructBox5(_Points, _Parent->GetSelfNode()->f0, fromDirection);
			delete _Parent->GetSelfNode()->f0;
			_Parent->GetSelfNode()->f0 = nullptr;
			break;
		case 1:
			lastNode->ConstructBox5(_Points, _Parent->GetSelfNode()->f1, fromDirection);
			delete _Parent->GetSelfNode()->f1;
			_Parent->GetSelfNode()->f1 = nullptr;
			break;
		case 2:
			lastNode->ConstructBox5(_Points, _Parent->GetSelfNode()->f2, fromDirection);
			delete _Parent->GetSelfNode()->f2;
			_Parent->GetSelfNode()->f2 = nullptr;
			break;
		case 3:
			lastNode->ConstructBox5(_Points, _Parent->GetSelfNode()->f3, fromDirection);
			delete _Parent->GetSelfNode()->f3;
			_Parent->GetSelfNode()->f3 = nullptr;
			break;
		case 4:
			lastNode->ConstructBox5(_Points, _Parent->GetSelfNode()->f4, fromDirection);
			delete _Parent->GetSelfNode()->f4;
			_Parent->GetSelfNode()->f4 = nullptr;
			break;
		default:
			break;
		}
		_Chain.push_back(lastNode);
		for (int i = 0; i < size; i++) {
			TreeNode* chainNode = new TreeNode(thickNess, parentPosition + (float)(i + 1) * positionDifference, parentPosition + (float)i * positionDifference);
			chainNode->ConstructBox5(_Points, lastNode->f0, 0);
			delete lastNode->f0;
			lastNode->f0 = nullptr;
			_Chain.push_back(chainNode);
			lastNode = chainNode;
		}
		_SelfNode.ConstructBox5(_Points, lastNode->f0, 0);
		delete lastNode->f0;
		lastNode->f0 = nullptr;
	}
	std::vector<Point*>* _Points;
	float _ThickNess;
	TreeNode _SelfNode;
	std::vector<TreeBranch*> _ChildBranches;
	bool _Occupied0;
	bool _Occupied1;
	bool _Occupied2;
	bool _Occupied3;
	bool _Occupied4;
	std::vector<TreeNode*> _Chain;
	TreeBranch* _Parent;
	int _FromDirection;
};

class TreeSkeleton {
public:
	TreeSkeleton() : _Points(std::vector<Point*>()), _RootBranch(TreeBranch(&_Points, 1.0f, nullptr, glm::vec3(0.0f, 0.0f, 0.0f))) {
	}

	TreeBranch* AddBranchToBranch(TreeBranch* branch, float thickNess, glm::vec3 position, int direction) {
		return branch->AddBranch(thickNess, position, direction);
	}

	TreeBranch* AddBranch(float thickNess, glm::vec3 position, int direction) {
		return _RootBranch.AddBranch(thickNess, position, direction);
	}

	void GenerateSurface() {
		_RootBranch.GatherFaces(&_Faces);
	}
	std::vector<Point*> GetPoints() {
		return _Points;
	}

	std::vector<Face*> GetFaces() {
		return _Faces;
	}
private:
	std::vector<Point*> _Points;
	std::vector<Face*> _Faces;
	TreeBranch _RootBranch;
};

#endif TREESKELETON_H
