#include "hzpch.h"
#include "ITransform.h"



namespace GameEngine {
	ITransform::ITransform()
		: position({0, 0, -1}),
		dimensions({1, 1, 1}),
		rotation(glm::fquat()),

		forward({ 0, 0, 1}),
		up({0, 1, 0})
	{
		this->update();
	}


	void ITransform::update()
	{
		this->transform = glm::mat4_cast(this->rotation) *
			glm::translate(glm::mat4(1.0f), this->position) *
			glm::scale(glm::mat4(1.0f), this->dimensions);
	}


	// TRANSFORMS
	void ITransform::translate(glm::vec3 direction)
	{
		this->position += direction;

		this->update();
	}

	// ROTATE
	void ITransform::rotate(glm::vec3 rotation)
	{
		glm::quat key_quat = glm::quat(glm::vec3(rotation.x, rotation.y, rotation.z));

		this->rotation = key_quat * this->rotation;
		this->rotation = glm::normalize(this->rotation);

		this->update();
	}
}