#pragma once

#include "glm.hpp"

namespace GameEngine {
	class GE_API OrtographicCamera
	{
	public:
		OrtographicCamera(float left, float right, float bottom, float top);
		~OrtographicCamera();
	
		inline const glm::vec3& getPositon() const { return this->position; };
		void setPostion(const glm::vec3& position) { this->position = position; this->update(); };

		inline float getRotation() const { return this->rotation; };
		void setRotation(const float rotation) { this->rotation = rotation; this->update(); };

		const glm::mat4& getProjectionMat() const { return this->projectionMat; };
		const glm::mat4& getViewMat() const { return this->viewMat; };
		const glm::mat4& getViewProjectionMat() const { return this->viewProjectionMat; };
	private:
		void update();
	private:
		glm::mat4 projectionMat;
		glm::mat4 viewMat;;
		glm::mat4 viewProjectionMat;

		glm::vec3 position;
		float rotation;
	};
}
