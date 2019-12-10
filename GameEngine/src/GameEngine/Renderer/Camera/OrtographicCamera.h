#pragma once

#include "ICamera.h"

namespace GameEngine {

	class GE_API OrtographicCamera : public ICamera
	{
	public:
		OrtographicCamera(float left, float right, float bottom, float top);
		~OrtographicCamera();

	private:
		virtual void update() override;
	};
}
