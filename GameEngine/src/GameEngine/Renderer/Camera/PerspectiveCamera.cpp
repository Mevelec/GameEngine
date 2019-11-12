#include "hzpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float clipNear, float clipFar)
		: fov(fov), clipNear(clipNear), clipFar(clipFar)
	{
		this->position = {0, 0, -2};
		this->forward = glm::vec3(0, 0, 1);
		this->up = glm::vec3(0, 1, 0);

		this->projectionMat = glm::perspective(fov, aspect, clipNear, clipFar);
		this->viewMat = glm::lookAt(this->position, this->position + this->forward, this->up);
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}


	PerspectiveCamera::~PerspectiveCamera()
	{
	}

	void PerspectiveCamera::update()
	{
		this->viewMat = glm::lookAt(this->position, this->position + this->forward, this->up);
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}


}

