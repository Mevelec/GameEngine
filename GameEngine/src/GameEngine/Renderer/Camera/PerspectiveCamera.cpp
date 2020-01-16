#include "hzpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float clipNear, float clipFar, glm::vec3 position)
		: fov(fov), clipNear(clipNear), clipFar(clipFar)
	{
		this->position = position;
		this->forward = glm::vec3(0, 0, 1);
		this->up = glm::vec3(0, 1, 0);

		this->aspectRatio = aspect;

		this->projectionMat = glm::perspective(fov, aspect, clipNear, clipFar);
		this->update();
	}

	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float clipNear, float clipFar)
		: fov(fov), clipNear(clipNear), clipFar(clipFar)
	{
		this->forward = glm::vec3(0, 0, 1);
		this->up = glm::vec3(0, 1, 0);

		this->aspectRatio = aspect;

		this->projectionMat = glm::perspective(fov, aspect, clipNear, clipFar);
		this->update();
	}


	PerspectiveCamera::~PerspectiveCamera()
	{
	}

	void PerspectiveCamera::onWindowResized(WindowResizeEvent& e) {
		this->aspectRatio = (float)e.getWidth() / (float)e.getHeight();
		this->projectionMat = glm::perspective(this->fov, this->aspectRatio, this->clipNear, this->clipFar);
		this->viewProjectionMat = this->projectionMat * this->viewMat;

	}

	void PerspectiveCamera::update()
	{
		Camera::update();
		auto a = this->position;
		auto b = this->forward;
		auto c = this->right;

		this->viewMat = (this->getTransform());
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}


}

