#pragma once
#include "Misc.h"
#include "World.h"
#include "Graphics.h"
#include "Default.h"
class SCEnvelope {
public:
	SCEnvelope(float xMax, float yMax, float zMax, float xMin, float yMin, float zMin, Material* material);

	~SCEnvelope();

	void Draw();

	bool PointsGenerated();

	virtual bool isInEnvelope(glm::vec3 point) = 0;

	virtual void GeneratePoints(int amount);

	void AddPoint(glm::vec3 point);

	void DeletePointSwapBack(int index);

	std::vector<glm::vec3>* GetPointPositions();

	void Clear();

protected:
	float _XMax, _YMax, _ZMax, _XMin, _YMin, _ZMin;
	bool _PointsGenerated;
	std::vector<glm::vec3> _PointPositions;
	std::vector<glm::mat4> _PointMatrices;
	Material* _PointMat;
};

