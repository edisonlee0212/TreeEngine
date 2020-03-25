#ifndef SCENVELOPE_H
#define SCENVELOPE_H

class SCEnvelope {
public:
	SCEnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Material* material) :
		_XMax(xMax),
		_YMax(yMax),
		_ZMax(zMax),
		_XMin(xMin),
		_YMin(yMin),
		_ZMin(zMin),
		_PointMat(material),
		_PointsGenerated(false)
	{

	}
	~SCEnvelope() {

	}

	void Draw() {
		if (_PointPositions.size() > 0) {
			Graphics::DrawMeshInstanced(Default::Primitives::Sphere, _PointMat, &_PointMatrices[0], World::camera, _PointMatrices.size());
		}
	}
	bool PointsGenerated() { return _PointsGenerated; }
	virtual bool isInEnvelope(glm::vec3 point) = 0;
	virtual void GeneratePoints(int amount) {
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
		_PointsGenerated = true;
	}

	void AddPoint(glm::vec3 point) {
		glm::mat4 matrix = glm::translate(glm::mat4(1.0f), point);
		matrix = glm::scale(matrix, glm::vec3(0.01f));
		_PointPositions.push_back(point);
		_PointMatrices.push_back(matrix);
	}
	void DeletePointSwapBack(int index) {
		_PointPositions[index] = _PointPositions.back();
		_PointMatrices[index] = _PointMatrices.back();
		_PointPositions.pop_back();
		_PointMatrices.pop_back();
	}
	std::vector<glm::vec3>* GetPointPositions() {
		return &_PointPositions;
	}
	void Clear() {
		_PointPositions.clear();
		_PointMatrices.clear();
		_PointsGenerated = false;
	}

protected:
	float _XMax, _YMax, _ZMax, _XMin, _YMin, _ZMin;
	bool _PointsGenerated;
	std::vector<glm::vec3> _PointPositions;
	std::vector<glm::mat4> _PointMatrices;
	Material* _PointMat;
};

#endif SCENVELOPE_H

