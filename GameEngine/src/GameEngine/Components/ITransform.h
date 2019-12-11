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
		//Rotation getters
		inline glm::vec3 getRotation() {return glm::degrees(glm::eulerAngles(this->rotation)); };
		inline glm::vec3 getEulerAngles() { return glm::eulerAngles(this->rotation); };
		inline glm::fquat getQuaternions() { return this->rotation; };


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