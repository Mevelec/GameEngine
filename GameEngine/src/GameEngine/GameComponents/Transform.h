#pragma once
#include <glm/glm.hpp>

#include <glm/gtc/quaternion.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GameEngine {

	class Transform
	{
	public:
		Transform();

		//GETTERS
		inline glm::mat4 getTransform() { return this->transform; };
		inline glm::vec3 getPosition() { return this->position; };
		inline glm::vec3 getScale() { return this->scale; };
		//Rotation
		inline glm::vec3 getRotation() {return glm::degrees(glm::eulerAngles(this->rotation)); };
		inline glm::vec3 getEulerAngles() { return glm::eulerAngles(this->rotation); };
		inline glm::fquat getQuaternions() { return this->rotation; };
		//Scale
		inline void setScale(glm::vec3 scale) { this->scale = scale; this->update(); };
		inline void setScale(float scale) { this->scale = glm::vec3(scale); this->update(); };

		//TRANSFORM
		void translate(glm::vec3 direction);


		inline void setPostion(glm::vec3 position) { this->position = position; this->update(); };

		//ROTATE
		void rotate(glm::vec3 rotation);

	protected:
		glm::fquat rotation;
		glm::vec3 scale;
		glm::vec3 position;

		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;

	protected:
		virtual void update();

	private:
		glm::mat4 transform;
	};
}