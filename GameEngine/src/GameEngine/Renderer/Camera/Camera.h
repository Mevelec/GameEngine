#pragma once
#include <glm/glm.hpp>
#include "GameEngine/Core/Transform/Transform.h"
#include "GameEngine/Events/ApplicationEvent.h"

namespace GameEngine {

	class  Camera : public Transform
	{
	public:
		virtual void update() { Transform::update(); };

		virtual void onWindowResized(WindowResizeEvent& e) = 0;

		const glm::mat4& getProjectionMat() const { return this->projectionMat; };
		const glm::mat4& getViewMat() const { return this->viewMat; };
		const glm::mat4& getViewProjectionMat() const { return this->viewProjectionMat; };

		virtual void zoom(const float& value) = 0;

	protected:
		glm::mat4 projectionMat;
		glm::mat4 viewMat;;
		glm::mat4 viewProjectionMat;

		float zoomLevel = 1;
	};
}