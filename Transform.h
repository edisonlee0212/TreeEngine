#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct Transform {
public:
	Transform() {
		_LocalToWorld = glm::mat4(1.0f);
		_LocalToParent = glm::mat4(1.0f);
	}
	void SetLocalPosition(glm::vec3 position) {
		_LocalToParent = glm::translate(_LocalToParent, position);
		_NeedUpdate = true;
	}

	void LookAt(glm::vec3 position) {

	}

	void LookFrom(glm::vec3 position) {

	}

	void SetPosition(glm::vec3 position) {
		_LocalToWorld = glm::translate(_LocalToWorld, position);
	}

	glm::vec3 GetLocalPosition() {
	}

	glm::vec3 GetPosition() {
		return _LocalToWorld[3];
	}

	void SetLocalRotation(glm::vec4 rotation) {

	}

	glm::vec4 GetLocalRotation() {

	}

	void SetLocalScale(glm::vec3 scale) {
		_LocalToParent = glm::scale(_LocalToParent, scale);
		_NeedUpdate = true;
	}

	void SetScale(glm::vec3 scale){
		_LocalToWorld = glm::scale(_LocalToWorld, scale);
	}

	glm::vec3 GetLocalScale() {

	}


	glm::vec3 GetScale() {
		return glm::vec3(_LocalToWorld[0].x, _LocalToWorld[1].y, _LocalToWorld[2].z);
	}
	void SetLocalToWorld(glm::mat4 value) {
		_LocalToWorld = value;
	}

	void SetLocalToParent(glm::mat4 value) {
		_LocalToParent = value;
	}

	glm::mat4 GetLocalToWorld() {
		return _LocalToWorld;
	}

	glm::mat4 GetLocalToParent() {
		return _LocalToParent;
	}
private:
	glm::mat4 _LocalToWorld;
	glm::mat4 _LocalToParent;
	bool _NeedUpdate;
};
#endif TRANSFORM_H
