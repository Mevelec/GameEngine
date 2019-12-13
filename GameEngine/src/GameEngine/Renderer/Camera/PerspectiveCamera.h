#pragma once

#include "Camera.h"

namespace GameEngine {

	class GE_API PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspect, float clipNear, float clipFar);
		~PerspectiveCamera();

	private:
		virtual void update() override;
		float fov;
		float clipNear, clipFar;
	};
}
