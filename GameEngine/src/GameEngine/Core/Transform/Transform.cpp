#include "hzpch.h"
#include "Transform.h"



namespace GameEngine {
	Transform::Transform()
		: position({0, 0, 0}),
		scale({1, 1, 1}),
		rotation(glm::fquat(1, 0, 0, 0)),

		forward({ 0, 0, 1}),
		up({0, -1, 0})
	{
		this->right = glm::vec3(-1, 0, 0);
		this->update();
	}


	void Transform::update()
	{
		this->transform = glm::lookAt(this->position, this->position + this->forward, this->up);
		/*
		this->transform = glm::mat4_cast(this->rotation) *
			glm::translate(glm::mat4(1.0f), this->position) *
			glm::scale(glm::mat4(1.0f), this->scale);*/
	}


	// TRANSFORMS
	void Transform::translate(glm::vec3 direction)
	{

		//this->position += direction * this->forward;

		if (direction.x)
			this->position += direction.x * this->right;
		if (direction.y)
			this->position += direction.y * this->up;
		if (direction.z)
			this->position += direction.z * this->forward;

		this->update();
	}

	// ROTATE
	void Transform::rotate(glm::vec3 rotation)
	{
		// Fuck quaternions
		glm::fquat pitchQuat(cos(glm::radians(rotation.x / 2.0f)), cross(this->forward, this->up * (float)sin(glm::radians(rotation.x / 2.0f))));
		glm::fquat yawQuat(cos(glm::radians(rotation.y / 2.0f)), this->up * (float)sin(glm::radians(rotation.y / 2.0f)));
		glm::fquat rollQuat(cos(glm::radians(rotation.z / 2.0f)), this->forward * (float)sin(glm::radians(rotation.z / 2.0f)));

		glm::fquat key_quat = yawQuat * pitchQuat * rollQuat;
		this->rotation = key_quat * this->rotation;

		this->forward = key_quat * this->forward * glm::conjugate(key_quat);
		//this->up = key_quat * this->up * glm::conjugate(key_quat);
		this->right = glm::cross(this->forward, this->up);


		this->update();
	}
}