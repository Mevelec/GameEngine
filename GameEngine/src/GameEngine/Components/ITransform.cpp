#include "hzpch.h"
#include "ITransform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GameEngine {
	ITransform::ITransform()
		: position({ 0.0f, 0.0f, 0.0f }),
		dimensions(1.0f),
		forward({ 0.0f, 0.0f, 1.0f }),
		right({ 0.0f, 0.0f, 1.0f }),
		up({0.0f, 1.0f, 0.0f})
	{
	}

	const glm::vec3 ITransform::getRotation() const
	{
		return glm::eulerAngles(this->rotation);
	}

// -- ORIGINE --------------------------------------------------------------

// -- ROTATION -------------------------------------------------------------
	void ITransform::rotate(const glm::vec3& angles)
	{

		//glm::rotate(this->transform, glm::radians(angles.y))
		/*this->rotation = glm::normalize(
			glm::quat(glm::vec3(
				glm::radians(angles.x),
				glm::radians(angles.y),
				glm::radians(angles.z)
			)) * this->rotation
		);*/

		this->update();
	}

	void ITransform::rotate(const glm::quat& rotation)
	{
		this->rotation = glm::normalize(rotation * this->rotation);

		this->update();
	}

	// Rotate the camera every frame so it keeps looking at the target
	void ITransform::lookAt(const glm::vec3& position)
	{
		this->transform = glm::lookAt(this->position, position, this->up);
	}

	// Same as above, but setting the worldUp parameter to Vector3.left in this example turns the camera on its side
	void ITransform::lookAt(const glm::vec3& position, const glm::vec3& up)
	{

	}

// -- TRANSLATE ------------------------------------------------------------
	void ITransform::translate(const glm::vec3& translateV)
	{
		this->position += translateV;
		this->update();
	}


// --           -------------------------------------------------------------
	const glm::mat4& ITransform::getTransform() const
	{
		return this->transform;
	}

	void ITransform::update()
	{
		this->transform = glm::translate(glm::mat4(1.0f), -this->position) *
			glm::mat4_cast(this->rotation) *
			glm::scale(glm::mat4(1.0f), this->dimensions);
	}
}