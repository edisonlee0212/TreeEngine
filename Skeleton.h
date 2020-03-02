#ifndef SKELETON_H
#define SKELETON_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace std;
struct Face {
public:
	int index;
	glm::vec3 p0 = glm::vec3(0.0f);
	glm::vec3 p1 = glm::vec3(0.0f);
	glm::vec3 p2 = glm::vec3(0.0f);
	glm::vec3 p3 = glm::vec3(0.0f);
	Face* f0;
	Face* f1;
	Face* f2;
	Face* f3;
};
/*
struct Point {
public:
	Transform transform;
	Face f0;
	Face f1;
	Face f2;
	Face f3;
};


class Node {
	Node* parent;
	Transform transform;
	bool branch[5];
	Face face[5];
	std::vector<Point> chainToParent;
	std::vector<Node *> children;
	Node(Node* parent, Transform transform, int fromFace) : parent(parent), transform(transform){
		branch[0] = false;
		branch[1] = false;
		branch[2] = false;
		branch[3] = false;
		branch[4] = false;

	}
	void AddChild(Transform transform, int face) {
		branch[face] = true;
		children.push_back(new Node(this, transform, face));
	}
	~Node() {
		for (auto i : children) {
			delete i;
		}
	}
};*/
class Skeleton
{
public:
	std::vector<Face*> faces;
	void CatmullClark() {
		vector<Face*> newFaces;
		for (auto i : faces) {
			Face* f0 = new Face();
			f0->index = i->index * 4;
			Face* f1 = new Face();
			f1->index = i->index * 4 + 1;
			Face* f2 = new Face();
			f2->index = i->index * 4 + 2;
			Face* f3 = new Face();
			f3->index = i->index * 4 + 3;

			f0->p1 = f1->p0 = (i->p0 + i->p1) / 2.0f;
			f1->p2 = f2->p1 = (i->p1 + i->p2) / 2.0f;
			f2->p3 = f3->p2 = (i->p2 + i->p3) / 2.0f;
			f3->p0 = f0->p3 = (i->p3 + i->p0) / 2.0f;

			f0->p2 = f1->p3 = f2->p0 = f3->p1 = (i->p0 + i->p1 + i->p2 + i->p3) / 4.0f;

			f0->p0 = i->p0;
			f1->p1 = i->p1;
			f2->p2 = i->p2;
			f3->p3 = i->p3;

			f0->f1 = f1;
			f0->f2 = f3;
			f1->f3 = f0;
			f1->f2 = f2;
			f2->f0 = f1;
			f2->f3 = f3;
			f3->f0 = f0;
			f3->f1 = f2;

			newFaces.push_back(f0);
			newFaces.push_back(f1);
			newFaces.push_back(f2);
			newFaces.push_back(f3);
		}
		for (int i = 0; i < faces.size(); i++) {
			Face* mainFace = faces[i];
			Face* f0 = newFaces[i * 4];
			Face* f1 = newFaces[i * 4 + 1];
			Face* f2 = newFaces[i * 4 + 2];
			Face* f3 = newFaces[i * 4 + 3];
			if (mainFace->f0 != nullptr) {
				newFaces[mainFace->f0->index * 4 + 3]->f2 = f0;
				newFaces[mainFace->f0->index * 4 + 2]->f2 = f1;
			}
			if (mainFace->f1 != nullptr) {
				newFaces[mainFace->f1->index * 4]->f3 = f1;
				newFaces[mainFace->f1->index * 4 + 3]->f3 = f2;
			}
			if (mainFace->f2 != nullptr) {
				newFaces[mainFace->f2->index * 4]->f0 = f3;
				newFaces[mainFace->f2->index * 4 + 1]->f0 = f2;
			}
			if (mainFace->f3 != nullptr) {
				newFaces[mainFace->f3->index * 4 + 1]->f1 = f0;
				newFaces[mainFace->f3->index * 4 + 2]->f1 = f3;
			}
		}
		
		for (auto i : faces) {
			delete i;
		}

		for (auto i : newFaces) {
			faces.push_back(i);
		}
	}
};
#endif SKELETON_H
