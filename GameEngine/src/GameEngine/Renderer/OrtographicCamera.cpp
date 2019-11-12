#include "hzpch.h"
#include "OrtographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	OrtographicCamera::OrtographicCamera(float left, float right, float bottom, float top)
		: projectionMat(glm::ortho(left, right, bottom, top, -1.0f, 0.0f)), viewMat(1.0f)
	{
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}


	OrtographicCamera::~OrtographicCamera()
	{
	}

	void OrtographicCamera::update()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0, 0, 1 ));
		
		this->viewMat = glm::inverse(transform);
		this->viewProjectionMat = this->projectionMat * this->viewMat;
	}


}

