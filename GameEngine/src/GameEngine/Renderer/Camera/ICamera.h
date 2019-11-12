#pragma once

#include <glm/glm.hpp>

namespace GameEngine {

	class  ICamera
	{
	public:
		virtual void update() = 0;

		inline const glm::vec3& getPositon() const { return this->position; };
		inline float getRotation() const { return this->rotation; };

		virtual void setPostion(const glm::vec3& position) = 0;
		virtual void setRotation(const float rotation) = 0;

		const glm::mat4& getProjectionMat() const { return this->projectionMat; };
		const glm::mat4& getViewMat() const { return this->viewMat; };
		const glm::mat4& getViewProjectionMat() const { return this->viewProjectionMat; };

	protected:
		glm::mat4 projectionMat;
		glm::mat4 viewMat;;
		glm::mat4 viewProjectionMat;

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;
	};
}