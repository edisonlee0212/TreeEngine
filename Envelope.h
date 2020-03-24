#ifndef ENVELOPE_H
#define ENVELOPE_H

class Envelope {
public:
	Envelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Material* material) :
		_XMax(xMax),
		_YMax(yMax),
		_ZMax(zMax),
		_XMin(xMin),
		_YMin(yMin),
		_ZMin(zMin),
		_PointMat(material)
	{

	}
	~Envelope() {

	}

	void Draw() {
		if (_PointPositions.size() > 0) {
			Graphics::DrawMeshInstanced(Default::Primitives::Sphere, _PointMat, &_PointMatrices[0], World::camera, _PointMatrices.size());
		}
	}

	virtual glm::vec3 GetPoint(float height, float angle) = 0;
	virtual void GenerateMesh(Mesh* mesh) = 0;
	virtual bool isInEnvelope(glm::vec3 point) = 0;
	void SelectPoints(int amount) {
		std::vector<glm::vec3> retVal;
		Clear();
		int size = 0;
		while (size < amount) {
			glm::vec3 point = glm::vec3(_XMin + (_XMax - _XMin) * (float)rand() / (RAND_MAX),
				_YMin + (_YMax - _YMin) * (float)rand() / (RAND_MAX),
				_ZMin + (_ZMax - _ZMin) * (float)rand() / (RAND_MAX));
			if (isInEnvelope(point)) {
				AddPoint(point);
				size++;
			}
		}
	}
	void AddPoint(glm::vec3 point) {
		glm::mat4 matrix = glm::translate(glm::mat4(1.0f), point);
		matrix = glm::scale(matrix, glm::vec3(0.01f));
		_PointPositions.push_back(point);
		_PointMatrices.push_back(matrix);
	}
	void DeletePoint(int index) {
		_PointPositions[index] = _PointPositions.back();
		_PointMatrices[index] = _PointMatrices.back();
		_PointPositions.pop_back();
		_PointMatrices.pop_back();
	}
	std::vector<glm::vec3>* GetPointPositions() {
		return &_PointPositions;
	}
	void Clear() {
		_PointMatrices.clear();
	}

protected:
	float _XMax, _YMax, _ZMax, _XMin, _YMin, _ZMin;

	std::vector<glm::vec3> _PointPositions;
	std::vector<glm::mat4> _PointMatrices;
	Material* _PointMat;
};

#endif ENVELOPE_H

