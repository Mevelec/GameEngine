#pragma once

#include "ICamera.h"

namespace GameEngine {

	class GE_API OrtographicCamera : public ICamera
	{
	public:
		OrtographicCamera(float left, float right, float bottom, float top);
		~OrtographicCamera();
	
		virtual void setPostion(const glm::vec3& position) override { this->position = position; this->update(); };
		virtual void setRotation(const float rotation) override  { this->rotation = rotation; this->update(); };

	private:
		virtual void update() override;
	};
}
