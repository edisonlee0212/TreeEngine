#ifndef ENVELOPE_H
#define ENVELOPE_H

class Envelope {
public:
	Envelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin) : _XMax(xMax), _YMax(yMax), _ZMax(zMax), _XMin(xMin), _YMin(yMin), _ZMin(zMin){}
	virtual glm::vec3 GetPoint(float height, float angle) = 0;
	virtual void GenerateMesh(Mesh* mesh) = 0;
	virtual bool isInEnvelope(glm::vec3 point) = 0;
	virtual std::vector<glm::vec3> SelectPoints(int amount) {
		std::vector<glm::vec3> retVal;
		while (retVal.size() < amount) {
			glm::vec3 point = glm::vec3(_XMin + (_XMax - _XMin) * (float)rand() / (RAND_MAX),
				_YMin + (_YMax - _YMin) * (float)rand() / (RAND_MAX),
				_ZMin + (_ZMax - _ZMin) * (float)rand() / (RAND_MAX));
			if (isInEnvelope(point)) retVal.push_back(point);
		}
	}
protected:
	float _XMax, _YMax, _ZMax, _XMin, _YMin, _ZMin;
};

#endif ENVELOPE_H

