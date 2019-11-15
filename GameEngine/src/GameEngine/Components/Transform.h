#pragma once
#include <glm/glm.hpp>

#include <glm/gtc/quaternion.hpp> 

namespace GameEngine {

	class Transform
	{
	public:
		Transform();

		void rotate(const glm::vec3& angles);
		void rotate(const glm::quat& rotation);
		void lookAt(const glm::vec3& position);
		void lookAt(const glm::vec3& position, const glm::vec3&  up);

		void scale();

		void translate(const glm::vec3& translate);
		void translateForward();

		const glm::mat4& getTransform() const;
	private:
		void update();
	private:
		glm::mat4 transform;

		glm::fquat rotation;
		glm::vec3 dimensions;
		glm::vec3 position;

		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;
	};
}