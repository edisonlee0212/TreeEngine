#ifndef SKELETON_H
#define SKELETON_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace std;

struct Element {

};

struct Point : Element {
public:
	Point(glm::vec3 position) : position(position) {}
	glm::vec3 position = glm::vec3(0.0f);
	vector<Element*> faces;
};

struct Face : Element {
public:
	bool broken;
	int index;
	Face(int index, Point* p0, Point* p1, Point* p2, Point* p3) : index(index), p0(p0), p1(p1), p2(p2), p3(p3) {
		broken = false;
		f0 = nullptr;
		f1 = nullptr;
		f2 = nullptr;
		f3 = nullptr;
	}
	void AttachPoints() {
		p0->faces.push_back(this);
		p1->faces.push_back(this);
		p2->faces.push_back(this);
		p3->faces.push_back(this);
	}
	glm::vec3 fp() {
		return (pp0() + pp1() + pp2() + pp3()) / 4.0f;
	}

	glm::vec3 ep0() { return (pp0() + pp1()) / 2.0f; }
	glm::vec3 ep1() { return (pp1() + pp2()) / 2.0f; }
	glm::vec3 ep2() { return (pp2() + pp3()) / 2.0f; }
	glm::vec3 ep3() { return (pp3() + pp0()) / 2.0f; }
	~Face() {
		for (int i = 0; i < p0->faces.size(); i++) {
			Face* face = (Face*)p0->faces.at(i);
			if (face->index == index) {
				p0->faces.at(i) = p0->faces.back();
				p0->faces.pop_back();
			}
		}
		for (int i = 0; i < p1->faces.size(); i++) {
			Face* face = (Face*)p1->faces.at(i);
			if (face->index == index) {
				p1->faces.at(i) = p1->faces.back();
				p1->faces.pop_back();
			}
		}
		for (int i = 0; i < p2->faces.size(); i++) {
			Face* face = (Face*)p2->faces.at(i);
			if (face->index == index) {
				p2->faces.at(i) = p2->faces.back();
				p2->faces.pop_back();
			}
		}
		for (int i = 0; i < p3->faces.size(); i++) {
			Face* face = (Face*)p3->faces.at(i);
			if (face->index == index) {
				p3->faces.at(i) = p3->faces.back();
				p3->faces.pop_back();
			}
		}
	}
	Point* p0;
	Point* p1;
	Point* p2;
	Point* p3;

	Point* e0;
	Point* e1;
	Point* e2;
	Point* e3;

	glm::vec3 pp0() { return p0->position; }
	glm::vec3 pp1() { return p1->position; }
	glm::vec3 pp2() { return p2->position; }
	glm::vec3 pp3() { return p3->position; }
	Face* f0;
	Face* f1;
	Face* f2;
	Face* f3;
};

class Skeleton
{
public:
	std::vector<Point*> points;
	std::vector<Face*> faces;
	void CatmullClark() {
		vector<Face*> newFaces;
		vector<Point*> newPoints;

		for (auto i : faces) {
			i->broken = true;
			Point* p0 = i->p0;
			Point* p1 = nullptr;
			Point* p2 = i->p1;
			Point* p3 = nullptr;
			Point* p4 = new Point((i->pp0() + i->pp1() + i->pp2() + i->pp3()) / 4.0f);
			Point* p5 = nullptr;
			Point* p6 = i->p3;
			Point* p7 = nullptr;
			Point* p8 = i->p2;

			if (i->f0 == nullptr || !i->f0->broken) {
				p1 = new Point((i->pp0() + i->pp1()) / 2.0f);
				newPoints.push_back(p1);
			}
			else if (i->f0->f0 == i) {
				p1 = i->f0->e0;
			}
			else if (i->f0->f1 == i) {
				p1 = i->f0->e1;
			}
			else if (i->f0->f2 == i) {
				p1 = i->f0->e2;
			}
			else if (i->f0->f3 == i) {
				p1 = i->f0->e3;
			}
			i->e0 = p1;

			if (i->f1 == nullptr || !i->f1->broken) {
				p5 = new Point((i->pp1() + i->pp2()) / 2.0f);
				newPoints.push_back(p5);
			}
			else if (i->f1->f0 == i) {
				p5 = i->f1->e0;
			}
			else if (i->f1->f1 == i) {
				p5 = i->f1->e1;
			}
			else if (i->f1->f2 == i) {
				p5 = i->f1->e2;
			}
			else if (i->f1->f3 == i) {
				p5 = i->f1->e3;
			}
			i->e1 = p5;
			newPoints.push_back(p4);
			if (i->f2 == nullptr || !i->f2->broken) {
				p7 = new Point((i->pp2() + i->pp3()) / 2.0f);
				newPoints.push_back(p7);
			}
			else if (i->f2->f0 == i) {
				p7 = i->f2->e0;
			}
			else if (i->f2->f1 == i) {
				p7 = i->f2->e1;
			}
			else if (i->f2->f2 == i) {
				p7 = i->f2->e2;
			}
			else if (i->f2->f3 == i) {
				p7 = i->f2->e3;
			}
			i->e2 = p7;
			if (i->f3 == nullptr || !i->f3->broken) {
				p3 = new Point((i->pp3() + i->pp0()) / 2.0f);
				newPoints.push_back(p3);
			}
			else if (i->f3->f0 == i) {
				p3 = i->f3->e0;
			}
			else if (i->f3->f1 == i) {
				p3 = i->f3->e1;
			}
			else if (i->f3->f2 == i) {
				p3 = i->f3->e2;
			}
			else if (i->f3->f3 == i) {
				p3 = i->f3->e3;
			}
			i->e3 = p3;

			int index = i->index * 4;

			Face* f0 = new Face(index, p0, p1, p4, p3);
			Face* f1 = new Face(index + 1, p1, p2, p5, p4);
			Face* f2 = new Face(index + 2, p4, p5, p8, p7);
			Face* f3 = new Face(index + 3, p3, p4, p7, p6);

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
				int index = mainFace->f0->index;
				if (mainFace == mainFace->f0->f0) {
					f0->f0 = newFaces[index + 1];
					f1->f0 = newFaces[index];
				}
				else if (mainFace == mainFace->f0->f1) {
					f0->f0 = newFaces[index + 2];
					f1->f0 = newFaces[index + 1];
				}
				else if (mainFace == mainFace->f0->f2) {
					f0->f0 = newFaces[index + 3];
					f1->f0 = newFaces[index + 2];
				}
				else if (mainFace == mainFace->f0->f3)
				{
					f0->f0 = newFaces[index];
					f1->f0 = newFaces[index + 3];
				}
			}
			if (mainFace->f1 != nullptr) {
				int index = mainFace->f1->index;
				if (mainFace == mainFace->f1->f0) {
					f1->f1 = newFaces[index + 1];
					f2->f1 = newFaces[index];
				}
				else if (mainFace == mainFace->f1->f1) {
					f1->f1 = newFaces[index + 2];
					f2->f1 = newFaces[index + 1];
				}
				else if (mainFace == mainFace->f1->f2) {
					f1->f1 = newFaces[index + 3];
					f2->f1 = newFaces[index + 2];
				}
				else if (mainFace == mainFace->f1->f3)
				{
					f1->f1 = newFaces[index];
					f2->f1 = newFaces[index + 3];
				}
			}
			if (mainFace->f2 != nullptr) {
				int index = mainFace->f2->index;
				if (mainFace == mainFace->f2->f0) {
					f2->f2 = newFaces[index + 1];
					f3->f2 = newFaces[index];
				}
				else if (mainFace == mainFace->f2->f1) {
					f2->f2 = newFaces[index + 2];
					f3->f2 = newFaces[index + 1];
				}
				else if (mainFace == mainFace->f2->f2) {
					f2->f2 = newFaces[index + 3];
					f3->f2 = newFaces[index + 2];
				}
				else if (mainFace == mainFace->f2->f3)
				{
					f2->f2 = newFaces[index];
					f3->f2 = newFaces[index + 3];
				}
			}
			if (mainFace->f3 != nullptr) {
				int index = mainFace->f3->index;
				if (mainFace == mainFace->f3->f0) {
					f3->f3 = newFaces[index + 1];
					f0->f3 = newFaces[index];
				}
				else if (mainFace == mainFace->f3->f1) {
					f3->f3 = newFaces[index + 2];
					f0->f3 = newFaces[index + 1];
				}
				else if (mainFace == mainFace->f3->f2) {
					f3->f3 = newFaces[index + 3];
					f0->f3 = newFaces[index + 2];
				}
				else if (mainFace == mainFace->f3->f3)
				{
					f3->f3 = newFaces[index];
					f0->f3 = newFaces[index + 3];
				}
			}
		}

		for (int i = 0; i < faces.size(); i++) {
			Face* mainFace = faces[i];
			Face* f0 = newFaces[i * 4];
			Face* f1 = newFaces[i * 4 + 1];
			Face* f2 = newFaces[i * 4 + 2];
			Face* f3 = newFaces[i * 4 + 3];

			glm::vec3 cfp = mainFace->fp();
			if (mainFace->f0 != nullptr) {
				glm::vec3 fp0 = mainFace->f0->fp();
				Point* ep0 = f0->p1;
				ep0->position = (ep0->position + (cfp + fp0) / 2.0f) / 2.0f;
			}
			if (mainFace->f1 != nullptr) {
				glm::vec3 fp1 = mainFace->f1->fp();
				Point* ep1 = f1->p2;
				ep1->position = (ep1->position + (cfp + fp1) / 2.0f) / 2.0f;
			}
			if (mainFace->f2 != nullptr) {
				glm::vec3 fp2 = mainFace->f2->fp();
				Point* ep2 = f2->p3;
				ep2->position = (ep2->position + (cfp + fp2) / 2.0f) / 2.0f;
			}
			if (mainFace->f3 != nullptr) {
				glm::vec3 fp3 = mainFace->f3->fp();
				Point* ep3 = f3->p0;
				ep3->position = (ep3->position + (cfp + fp3) / 2.0f) / 2.0f;
			}
		}
		/*
		for (auto i : points) {
			
			auto connectedFaces = i->faces;
			int facesCount = connectedFaces.size();
			if (facesCount == 0) continue;
			glm::vec3 facepavg = glm::vec3(0.0f);
			glm::vec3 edgepavg = glm::vec3(0.0f);
			for (int j = 0; j < facesCount; j++) {
				Face* face = (Face*)connectedFaces.at(j);
				facepavg += face->fp();
				if (i == face->p0) {
					edgepavg += (face->ep0() + face->ep3()) / 2.0f;
				}
				else if (i == face->p1) {
					edgepavg += (face->ep0() + face->ep1()) / 2.0f;
				}
				else if (i == face->p2) {
					edgepavg += (face->ep1() + face->ep2()) / 2.0f;
				}
				else if (i == face->p3) {
					edgepavg += (face->ep2() + face->ep3()) / 2.0f;
				}
			}
			facepavg /= facesCount;
			edgepavg /= facesCount;
			float m1 = ((float)facesCount - 3.0f) / (float)facesCount;
			float m2 = 1.0f / (float)facesCount;
			float m3 = 2.0f / (float)facesCount;
			i->position = i->position * m1 + facepavg * m2 + edgepavg * m3;
		}
		*/
		
		for (auto i : faces) {
			delete i;
		}

		faces.clear();
		for (auto i : newFaces) {
			i->AttachPoints();
			faces.push_back(i);
		}

		for (auto i : newPoints) {
			points.push_back(i);
		}
	}

};
#endif SKELETON_H
