#pragma once
#include "Misc.h"
#include "Graphics.h"
struct Element {};
struct Point : Element {
public:
	Point(glm::vec3 position) : position(position) {}
	glm::vec3 position = glm::vec3(0.0f);
	std::vector<Element*> _Faces;
};
struct Face : Element {
public:
	bool broken;
	Face(Point* p0, Point* p1, Point* p2, Point* p3) : p0(p0), p1(p1), p2(p2), p3(p3) {
		broken = false;
		f0 = nullptr;
		f1 = nullptr;
		f2 = nullptr;
		f3 = nullptr;
	}
	void AttachPoints() {
		p0->_Faces.push_back(this);
		p1->_Faces.push_back(this);
		p2->_Faces.push_back(this);
		p3->_Faces.push_back(this);
	}
	glm::vec3 fp() {
		return (pp0() + pp1() + pp2() + pp3()) / 4.0f;
	}

	glm::vec3 ep0() { return (pp0() + pp1()) / 2.0f; }
	glm::vec3 ep1() { return (pp1() + pp2()) / 2.0f; }
	glm::vec3 ep2() { return (pp2() + pp3()) / 2.0f; }
	glm::vec3 ep3() { return (pp3() + pp0()) / 2.0f; }
	~Face() {
		for (size_t i = 0; i < p0->_Faces.size(); i++) {
			Face* face = (Face*)p0->_Faces.at(i);
			if (face == this) {
				p0->_Faces.at(i) = p0->_Faces.back();
				p0->_Faces.pop_back();
			}
		}
		for (size_t i = 0; i < p1->_Faces.size(); i++) {
			Face* face = (Face*)p1->_Faces.at(i);
			if (face == this) {
				p1->_Faces.at(i) = p1->_Faces.back();
				p1->_Faces.pop_back();
			}
		}
		for (size_t i = 0; i < p2->_Faces.size(); i++) {
			Face* face = (Face*)p2->_Faces.at(i);
			if (face == this) {
				p2->_Faces.at(i) = p2->_Faces.back();
				p2->_Faces.pop_back();
			}
		}
		for (size_t i = 0; i < p3->_Faces.size(); i++) {
			Face* face = (Face*)p3->_Faces.at(i);
			if (face == this) {
				p3->_Faces.at(i) = p3->_Faces.back();
				p3->_Faces.pop_back();
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

	Face* nf0;
	Face* nf1;
	Face* nf2;
	Face* nf3;
};

class CatmullClarkModel
{
public:
	CatmullClarkModel(std::vector<Point*> _Points, std::vector<Face*> _Faces) : _CurrentLevel(0), _GeneratedMaxLevel(0), _Points(_Points), _Faces(_Faces) {
		Mesh* mesh = new Mesh();
		GenerateMesh(mesh);
		_GeneratedMeshes.push_back(mesh);
	}

	~CatmullClarkModel() {
		for (auto i : _Points) delete i;
		//for (auto i : _Faces) delete i;
		for (auto i : _GeneratedMeshes) delete i;
		_Points.clear();
		_Faces.clear();
		_GeneratedMeshes.clear();
	}

	Mesh* Subdivision() {
		_CurrentLevel++;
		if (_CurrentLevel <= _GeneratedMaxLevel) return _GeneratedMeshes[_CurrentLevel];
		_GeneratedMaxLevel++;

		std::vector<Face*> newFaces;
		std::vector<Point*> newPoints;

		for (size_t index = 0; index < _Faces.size(); index++) {
			auto i = _Faces[index];
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

			if (p0 == nullptr || p1 == nullptr || p4 == nullptr || p3 == nullptr) {
				printf("hello");
			}

			int ni = index * 4;

			Face* f0 = new Face(p0, p1, p4, p3);
			Face* f1 = new Face(p1, p2, p5, p4);
			Face* f2 = new Face(p4, p5, p8, p7);
			Face* f3 = new Face(p3, p4, p7, p6);

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

			i->nf0 = f0;
			i->nf1 = f1;
			i->nf2 = f2;
			i->nf3 = f3;

		}

		for (size_t i = 0; i < _Faces.size(); i++) {
			Face* mainFace = _Faces[i];
			Face* f0 = mainFace->f0;
			Face* f1 = mainFace->f1;
			Face* f2 = mainFace->f2;
			Face* f3 = mainFace->f3;
			Face* nf0 = mainFace->nf0;
			Face* nf1 = mainFace->nf1;
			Face* nf2 = mainFace->nf2;
			Face* nf3 = mainFace->nf3;
			if (f0 != nullptr) {
				if (mainFace == mainFace->f0->f0) {
					nf0->f0 = f0->nf1;
					nf1->f0 = f0->nf0;
				}
				else if (mainFace == mainFace->f0->f1) {
					nf0->f0 = f0->nf2;
					nf1->f0 = f0->nf1;
				}
				else if (mainFace == mainFace->f0->f2) {
					nf0->f0 = f0->nf3;
					nf1->f0 = f0->nf2;
				}
				else if (mainFace == mainFace->f0->f3)
				{
					nf0->f0 = f0->nf0;
					nf1->f0 = f0->nf3;
				}
			}
			if (f1 != nullptr) {
				if (mainFace == mainFace->f1->f0) {
					nf1->f1 = f1->nf1;
					nf2->f1 = f1->nf0;
				}
				else if (mainFace == mainFace->f1->f1) {
					nf1->f1 = f1->nf2;
					nf2->f1 = f1->nf1;
				}
				else if (mainFace == mainFace->f1->f2) {
					nf1->f1 = f1->nf3;
					nf2->f1 = f1->nf2;
				}
				else if (mainFace == mainFace->f1->f3)
				{
					nf1->f1 = f1->nf0;
					nf2->f1 = f1->nf3;
				}
			}
			if (f2 != nullptr) {
				if (mainFace == mainFace->f2->f0) {
					nf3->f2 = f2->nf0;
					nf2->f2 = f2->nf1;
				}
				else if (mainFace == mainFace->f2->f1) {
					nf3->f2 = f2->nf1;
					nf2->f2 = f2->nf2;
				}
				else if (mainFace == mainFace->f2->f2) {
					nf3->f2 = f2->nf2;
					nf2->f2 = f2->nf3;
				}
				else if (mainFace == mainFace->f2->f3)
				{
					nf3->f2 = f2->nf3;
					nf2->f2 = f2->nf0;
				}
			}
			if (f3 != nullptr) {
				if (mainFace == mainFace->f3->f0) {
					nf0->f3 = f3->nf0;
					nf3->f3 = f3->nf1;
				}
				else if (mainFace == mainFace->f3->f1) {
					nf0->f3 = f3->nf1;
					nf3->f3 = f3->nf2;
				}
				else if (mainFace == mainFace->f3->f2) {
					nf0->f3 = f3->nf2;
					nf3->f3 = f3->nf3;
				}
				else if (mainFace == mainFace->f3->f3)
				{
					nf0->f3 = f3->nf3;
					nf3->f3 = f3->nf0;
				}
			}
		}

		for (size_t i = 0; i < _Faces.size(); i++) {
			Face* mainFace = _Faces[i];
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

		for (auto i : _Points) {

			auto connectedFaces = i->_Faces;
			int facesCount = connectedFaces.size();
			if (facesCount <= 1) continue;
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


		for (auto i : _Faces) {
			delete i;
		}

		_Faces.clear();
		for (auto i : newFaces) {
			i->AttachPoints();
			_Faces.push_back(i);
		}

		for (auto i : newPoints) {
			_Points.push_back(i);
		}

		Mesh* mesh = new Mesh();
		GenerateMesh(mesh);
		_GeneratedMeshes.push_back(mesh);
		return mesh;
	}

	Mesh* Abbreviation() {
		if (_CurrentLevel > 0) _CurrentLevel--;
		return _GeneratedMeshes[_CurrentLevel];
	}

	Mesh* GetCurrentMesh() {
		return _GeneratedMeshes[_CurrentLevel];
	}

private:
	std::vector<Point*> _Points;
	std::vector<Face*> _Faces;
	std::vector<Mesh*> _GeneratedMeshes;
	int _GeneratedMaxLevel;
	int _CurrentLevel;

	void GenerateMesh(Mesh* mesh) {
		auto vertices = &mesh->vertices;
		auto triangles = &mesh->triangles;
		int index = 0;
		for (auto i : _Faces) {
			Vertex v0;
			v0.Position = i->pp0();
			v0.TexCoords = glm::vec2(0.0f, 0.0f);
			Vertex v1;
			v1.Position = i->pp1();
			v1.TexCoords = glm::vec2(1.0f, 0.0f);
			Vertex v2;
			v2.Position = i->pp2();
			v2.TexCoords = glm::vec2(1.0f, 1.0f);
			Vertex v3;
			v3.Position = i->pp2();
			v3.TexCoords = glm::vec2(1.0f, 1.0f);
			Vertex v4;
			v4.Position = i->pp3();
			v4.TexCoords = glm::vec2(0.0f, 1.0f);
			Vertex v5;
			v5.Position = i->pp0();
			v5.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices->push_back(v0);
			vertices->push_back(v1);
			vertices->push_back(v2);
			vertices->push_back(v3);
			vertices->push_back(v4);
			vertices->push_back(v5);
			triangles->push_back(index * 6);
			triangles->push_back(index * 6 + 1);
			triangles->push_back(index * 6 + 2);
			triangles->push_back(index * 6 + 3);
			triangles->push_back(index * 6 + 4);
			triangles->push_back(index * 6 + 5);
			index++;
		}
	}
};
