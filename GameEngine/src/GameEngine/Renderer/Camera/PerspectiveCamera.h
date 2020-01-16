#pragma once

#include "Camera.h"

namespace GameEngine {

	class GE_API PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspect, float clipNear, float clipFar, glm::vec3 position);
		~PerspectiveCamera();

		virtual void onWindowResized(WindowResizeEvent& e) override;

	private:
		virtual void update() override;
		float fov;
		float clipNear, clipFar;
		float aspectRatio;

	};
}
