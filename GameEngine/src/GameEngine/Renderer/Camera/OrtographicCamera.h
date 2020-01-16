#pragma once

#include "Camera.h"

namespace GameEngine {

	class GE_API OrtographicCamera : public Camera
	{
	public:
		OrtographicCamera(float aspectRatio, glm::vec3 position);
		~OrtographicCamera();
		
		virtual void onWindowResized(WindowResizeEvent& e) override;

	private:
		virtual void update() override;
		float aspectRatio;
		float zoomLevel = 1;
	};
}
