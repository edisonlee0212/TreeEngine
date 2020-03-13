#ifndef ENVELOPE_H
#define ENVELOPE_H

class Envelope {
public:
	Envelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Mesh* mesh, Material* material) : _XMax(xMax), _YMax(yMax), _ZMax(zMax), _XMin(xMin), _YMin(yMin), _ZMin(zMin){
		_PointsSet = new AttractionPointsSet(mesh, material);
	}
	~Envelope() {
		delete _PointsSet;
	}

	void Draw() {
		_PointsSet->DrawAttractionPoints();
	}

	virtual glm::vec3 GetPoint(float height, float angle) = 0;
	virtual void GenerateMesh(Mesh* mesh) = 0;
	virtual bool isInEnvelope(glm::vec3 point) = 0;
	void SelectPoints(int amount) {
		std::vector<glm::vec3> retVal;
		_PointsSet->Clear();
		int size = 0;
		while (size < amount) {
			glm::vec3 point = glm::vec3(_XMin + (_XMax - _XMin) * (float)rand() / (RAND_MAX),
				_YMin + (_YMax - _YMin) * (float)rand() / (RAND_MAX),
				_ZMin + (_ZMax - _ZMin) * (float)rand() / (RAND_MAX));
			if (isInEnvelope(point)) {
				_PointsSet->AddPoints(point);
				size++;
			}
		}
	}
protected:
	float _XMax, _YMax, _ZMax, _XMin, _YMin, _ZMin;
	AttractionPointsSet* _PointsSet;
};

#endif ENVELOPE_H

