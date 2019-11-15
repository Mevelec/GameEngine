#include "hzpch.h"
#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GameEngine {
	Transform::Transform()
		: position({ 0.0f, 0.0f, 0.0f }),
		rotation({1.0f, 0.0f, 0.0f, 0.0f}),
		dimensions(1.0f),
		forward({ 0.0f, 0.0f, 1.0f }),
		right({ 1.0f, 0.0f, 0.0f }),
		up({0.0f, 1.0f, 0.0f})
	{
		this->update();
	}
// -- ORIGINE --------------------------------------------------------------

// -- ROTATION -------------------------------------------------------------
	void Transform::rotate(const glm::vec3& angles)
	{
		this->rotation = glm::quat(glm::vec3(
			glm::radians(angles.x),
			glm::radians(angles.y),
			glm::radians(angles.z)
		)) * this->rotation;

		this->update();
	}

	void Transform::rotate(const glm::quat& rotation)
	{
		this->rotation = rotation * this->rotation;
		this->update();
	}

	// Rotate the camera every frame so it keeps looking at the target
	void Transform::lookAt(const glm::vec3& position)
	{
		this->transform = glm::lookAt(this->position, position, this->up);
	}

	// Same as above, but setting the worldUp parameter to Vector3.left in this example turns the camera on its side
	void Transform::lookAt(const glm::vec3& position, const glm::vec3& up)
	{

	}

// -- TRANSLATE ------------------------------------------------------------
	void Transform::translate(const glm::vec3& translateV)
	{
		this->position += translateV;
		this->update();
	}


// --           -------------------------------------------------------------
	const glm::mat4& Transform::getTransform() const
	{
		return this->transform;
	}

	void Transform::update()
	{
		this->transform = glm::translate(glm::mat4(1.0f), this->position) *
			glm::toMat4(this->rotation) *
			glm::scale(glm::mat4(1.0f), this->dimensions);
	}
}