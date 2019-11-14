#pragma once
#include <glm/glm.hpp>

namespace GameEngine {

	class Transform
	{
	public:
		Transform();

		void rotate();

		void scale();

		void translate(const glm::vec3& translate);
		void moveForward();

		const glm::mat4& getTransform() const;
	private:
		void update();
	private:
		glm::vec3 origine;

		glm::mat4 transform;
		glm::vec3 scaleV;
		glm::vec3 locationV;
		glm::vec3 rotationV;

		// transform = location* rotation* scale;

	};
}