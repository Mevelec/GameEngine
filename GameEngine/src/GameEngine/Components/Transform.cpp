#include "hzpch.h"
#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	Transform::Transform()
		: origine(0.0f),
		locationV(0.0f),
		rotationV(0.0f),
		scaleV(1.0f)
	{
		this->update();
	}
	void Transform::translate(const glm::vec3& translateV)
	{
		this->locationV += translateV;
		this->update();
	}
	const glm::mat4& Transform::getTransform() const
	{
		return this->transform;
	}

	void Transform::update()
	{
		this->transform = glm::translate(glm::mat4(1.0f), this->origine + this->locationV) *
			//this->rotation * 
			glm::scale(glm::mat4(1.0f), this->scaleV);

	}
}