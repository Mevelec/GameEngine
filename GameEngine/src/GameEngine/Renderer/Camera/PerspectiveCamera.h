#pragma once

#include "Camera.h"

namespace GameEngine {

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspect, float clipNear, float clipFar, glm::vec3 position);
		PerspectiveCamera(float fov, float aspect, float clipNear, float clipFar);
		~PerspectiveCamera();

		virtual void onWindowResized(WindowResizeEvent& e) override;
		virtual void zoom(const float& value) override;

	private:
		virtual void update() override;
		float fov;
		float clipNear, clipFar;
		float aspectRatio;

	};
}
