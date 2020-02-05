#include "hzpch.h"
#include "GameEngine/Renderer/Camera/OrtographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	OrtographicCamera::OrtographicCamera(float aspectRatio, glm::vec3 position)
	{
		this->aspectRatio = aspectRatio;
		this->position = position;
		this->up = glm::vec3(0, 1, 0);


		this->projectionMat = glm::ortho(-aspectRatio * this->zoomLevel, 
			aspectRatio * this->zoomLevel, -this->zoomLevel, this->zoomLevel, -1.0f, 100.0f);

		this->update();
	}

	OrtographicCamera::OrtographicCamera(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
		this->up = glm::vec3(0, 1, 0);

		this->projectionMat = glm::ortho(-aspectRatio * this->zoomLevel,
			aspectRatio * this->zoomLevel, -this->zoomLevel, this->zoomLevel, -1.0f, 100.0f);

		this->update();
	}


	OrtographicCamera::~OrtographicCamera()
	{
	}

	void OrtographicCamera::onWindowResized(WindowResizeEvent& e) {
		this->aspectRatio = (float)e.getWidth() / (float)e.getHeight();
		this->projectionMat = glm::ortho(-aspectRatio * this->zoomLevel,
			aspectRatio * this->zoomLevel, -this->zoomLevel, this->zoomLevel, -1.0f, 100.0f);
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}

	void OrtographicCamera::update()
	{

		Camera::update();

		this->viewMat = this->getTransform();
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}

	void OrtographicCamera::zoom(const float& value)
	{
		this->zoomLevel += value;

		this->projectionMat = glm::ortho(-aspectRatio * this->zoomLevel,
			aspectRatio * this->zoomLevel, -this->zoomLevel, this->zoomLevel, -1.0f, 100.0f);
		this->viewProjectionMat = this->projectionMat * this->viewMat;

		this->update();
	}

}

