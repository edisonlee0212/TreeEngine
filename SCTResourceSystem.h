#ifndef SCTRESOURCESYSTEM_H
#define SCTRESOURCESYSTEM_H
#include "AttractionPointsSet.h"
#include "Envelope.h"
#include "SurfaceOfRevolutionEnvelope.h"
class SCTResourceSystem : public SystemBase {
public:
    SCTResourceSystem() : SystemBase() {
    }
    void OnCreate() {
        Mesh* mesh = LoadCube();
        Material* material = new Material();
        material->shader = new Shader("DefaultInstanced.vs", "DefaultInstanced.fs");
        Texture texture;
        texture.LoadTexture("border.jpg", "");
        material->textures.push_back(texture);
        envelope = new SurfaceOfRevelutionEnvelope(1.0f, 3.0f, 1.0f, -1.0f, 1.0f, -1.0f, mesh, material);
        envelope->SelectPoints(5000);
        Enable();
    }
    Mesh* LoadCube();
    void OnDestroy() {
        Disable();
    }
    void Update();
private:
    SurfaceOfRevelutionEnvelope* envelope;
};

void SCTResourceSystem::Update() {
    envelope->Draw();
}

Mesh* SCTResourceSystem::LoadCube() {
	std::vector<Point*> _Points = std::vector<Point*>();
	std::vector<Face*> _Faces = std::vector<Face*>();

	Point* p0 = new Point(glm::vec3(-0.5f, 0.5f, -0.5f));//
	Point* p1 = new Point(glm::vec3(-0.5f, 0.5f, 0.5f));//
	Point* p2 = new Point(glm::vec3(0.5f, 0.5f, -0.5f));
	Point* p3 = new Point(glm::vec3(0.5f, 0.5f, 0.5f));
	Point* p4 = new Point(glm::vec3(-0.5f, -0.5f, -0.5f));//
	Point* p5 = new Point(glm::vec3(-0.5f, -0.5f, 0.5f));//
	Point* p6 = new Point(glm::vec3(0.5f, -0.5f, -0.5f));
	Point* p7 = new Point(glm::vec3(0.5f, -0.5f, 0.5f));

	_Points.push_back(p0);
	_Points.push_back(p1);
	_Points.push_back(p2);
	_Points.push_back(p3);
	_Points.push_back(p4);
	_Points.push_back(p5);
	_Points.push_back(p6);
	_Points.push_back(p7);
	Face* f0 = new Face(p1, p0, p2, p3);
	f0->AttachPoints();
	Face* f1 = new Face(p0, p1, p5, p4);
	f1->AttachPoints();
	Face* f2 = new Face(p2, p0, p4, p6);
	f2->AttachPoints();
	Face* f3 = new Face(p7, p5, p1, p3);
	f3->AttachPoints();
	Face* f4 = new Face(p6, p7, p3, p2);
	f4->AttachPoints();
	Face* f5 = new Face(p7, p6, p4, p5);
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

	_Faces.push_back(f0);
	_Faces.push_back(f1);

	_Faces.push_back(f2);

	_Faces.push_back(f5);
	_Faces.push_back(f3);
	_Faces.push_back(f4);
	CatmullClarkModel* model = new CatmullClarkModel(_Points, _Faces);
	return model->GetCurrentMesh();
}

#endif SCTRESOURCESYSTEM_H
