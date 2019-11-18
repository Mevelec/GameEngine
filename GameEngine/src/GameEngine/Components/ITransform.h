#pragma once
#include <glm/glm.hpp>

#include <glm/gtc/quaternion.hpp> 

namespace GameEngine {

	class ITransform
	{
	public:
		ITransform();

		const glm::vec3 getRotation() const;
		void rotate(const glm::vec3& angles);
		void rotate(const glm::quat& rotation);
		void lookAt(const glm::vec3& position);
		void lookAt(const glm::vec3& position, const glm::vec3&  up);

		void scale();

		void translate(const glm::vec3& translate);
		void translateForward();

		const glm::mat4& getTransform() const;
		const inline glm::vec3& getPosition() const { return this->position; };
	protected:
		glm::fquat rotation;
		glm::vec3 dimensions;
		glm::vec3 position;

		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;

	protected:
		virtual void update();

	private:
		glm::mat4 transform;
	};
}