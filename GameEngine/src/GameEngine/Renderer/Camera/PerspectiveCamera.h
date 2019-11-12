#pragma once

#include "ICamera.h"

namespace GameEngine {

	class GE_API PerspectiveCamera : public ICamera
	{
	public:
		PerspectiveCamera(float fov, float aspect, float clipNear, float clipFar);
		~PerspectiveCamera();

		virtual void setPostion(const glm::vec3& position) override { this->position = position; this->update(); };
		virtual void setRotation(const float rotation) override { this->rotation = rotation; this->update(); };

	private:
		virtual void update() override;
		float fov;
		float clipNear, clipFar;
		
		glm::vec3 forward;
		glm::vec3 up;
	};
}
