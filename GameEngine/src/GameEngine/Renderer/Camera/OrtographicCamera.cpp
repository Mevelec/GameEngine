#include "hzpch.h"
#include "OrtographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	OrtographicCamera::OrtographicCamera(float left, float right, float bottom, float top)
	{
		this->projectionMat = glm::ortho(left, right, bottom, top, -1000.0f, 0.0f);
		this->viewMat = this->getTransform();
		this->viewProjectionMat = this->projectionMat * this->viewMat;

		this->update();
	}


	OrtographicCamera::~OrtographicCamera()
	{
	}

	void OrtographicCamera::update()
	{

		ICamera::update();

		this->viewMat = glm::inverse(this->getTransform());
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}


}

