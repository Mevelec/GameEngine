#pragma once
#include <glm/glm.hpp>

#include <glm/gtc/quaternion.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GameEngine {

	class ITransform
	{
	public:
		ITransform();

		//GETTERS
		inline glm::mat4 getTransform() { return this->transform; };
		inline glm::vec3 getPosition() { return this->position; };
		inline glm::vec3 getRotation() { return glm::eulerAngles(this->rotation) * 3.14159f / 180.f; };

		//TRANSFORM
		void translate(glm::vec3 direction);

		//ROTATE
		void rotate(glm::vec3 rotation);

	protected:
		glm::fquat rotation;
		glm::vec3 dimensions;
		glm::vec3 position;

		glm::vec3 forward;
		glm::vec3 up;

	protected:
		virtual void update();

	private:
		glm::mat4 transform;
	};
}