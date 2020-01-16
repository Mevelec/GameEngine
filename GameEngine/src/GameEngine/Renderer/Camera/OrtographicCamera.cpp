#include "hzpch.h"
#include "OrtographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	OrtographicCamera::OrtographicCamera(float aspectRatio, glm::vec3 position)
	{
		this->position = position;
		this->forward = glm::vec3(0, 0, 1);
		this->up = glm::vec3(0, 1, 0);

		this->aspectRatio = aspectRatio;

		this->projectionMat = glm::ortho(-aspectRatio * this->zoomLevel, 
			aspectRatio * this->zoomLevel, -this->zoomLevel, this->zoomLevel, 0.0f, 1000.0f);

		this->update();
	}

	OrtographicCamera::OrtographicCamera(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
		this->forward = glm::vec3(0, 0, 1);
		this->up = glm::vec3(0, 1, 0);

		this->projectionMat = glm::ortho(-aspectRatio * this->zoomLevel,
			aspectRatio * this->zoomLevel, -this->zoomLevel, this->zoomLevel, 0.0f, 1000.0f);

		this->update();
	}


	OrtographicCamera::~OrtographicCamera()
	{
	}

	void OrtographicCamera::onWindowResized(WindowResizeEvent& e) {
		this->aspectRatio = (float)e.getWidth() / (float)e.getHeight();
		this->projectionMat = glm::ortho(-aspectRatio * this->zoomLevel,
			aspectRatio * this->zoomLevel, -this->zoomLevel, this->zoomLevel, -1000.0f, 0.0f);
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}

	void OrtographicCamera::update()
	{

		Camera::update();

		this->viewMat = glm::inverse(this->getTransform());
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}


}

