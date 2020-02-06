#pragma once

#include "Camera.h"

namespace GameEngine {

	class OrtographicCamera : public Camera
	{
	public:
		OrtographicCamera(float aspectRatio, glm::vec3 position);
		OrtographicCamera(float aspectRatio);

		~OrtographicCamera();
		
		virtual void onWindowResized(WindowResizeEvent& e) override;

		virtual void zoom(const float& value) override;

	private:
		virtual void update() override;
		float aspectRatio;
	};
}
