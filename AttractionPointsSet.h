#ifndef ATTRACTIONPOINTSSET_H
#define ATTRACTIONPOINTSSET_H

class AttractionPointsSet
{
public:
	AttractionPointsSet(Mesh* mesh, Material* material) : _PointMesh(mesh), _PointMat(material){}
	void AddPoints(glm::vec3 point) {
		glm::mat4 matrix = glm::translate(glm::mat4(1.0f), point);
		matrix = glm::scale(matrix, glm::vec3(0.01f));
		_PointMatrices.push_back(matrix);
	}
	void DrawAttractionPoints() {
		Graphics::DrawMeshInstanced(_PointMesh, _PointMat, &_PointMatrices[0], World::camera, _PointMatrices.size());
	}

	void Clear() {
		_PointMatrices.clear();
	}

private:
	std::vector<glm::mat4> _PointMatrices;
	Mesh* _PointMesh;
	Material* _PointMat;
};


#endif ATTRACTIONPOINTSSET_H
