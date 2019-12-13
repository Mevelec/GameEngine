#include "hzpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float clipNear, float clipFar)
		: fov(fov), clipNear(clipNear), clipFar(clipFar)
	{
		this->projectionMat = glm::perspective(fov, aspect, clipNear, clipFar);
		this->viewMat = this->getTransform();
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}


	PerspectiveCamera::~PerspectiveCamera()
	{
	}

	void PerspectiveCamera::update()
	{
		Camera::update();

		this->viewMat = this->getTransform();
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}


}

