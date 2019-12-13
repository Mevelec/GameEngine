#pragma once

#include "Camera.h"

namespace GameEngine {

	class GE_API OrtographicCamera : public Camera
	{
	public:
		OrtographicCamera(float left, float right, float bottom, float top);
		~OrtographicCamera();

	private:
		virtual void update() override;
	};
}
