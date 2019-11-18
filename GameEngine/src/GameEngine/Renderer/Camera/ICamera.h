#pragma once

#include <glm/glm.hpp>
#include "GameEngine/Components/ITransform.h"

namespace GameEngine {

	class  ICamera : public ITransform
	{
	public:
		virtual void update() { ITransform::update(); };

		const glm::mat4& getProjectionMat() const { return this->projectionMat; };
		const glm::mat4& getViewMat() const { return this->viewMat; };
		const glm::mat4& getViewProjectionMat() const { return this->viewProjectionMat; };

	protected:
		glm::mat4 projectionMat;
		glm::mat4 viewMat;;
		glm::mat4 viewProjectionMat;
	};
}