#pragma once

#include "GameEngine/Renderer/Geometry/Geometry.h"

namespace GameEngine {


	class Square
	{

	public:
		static const uint32_t indices[2 * 3];
		static const uint32_t iCount = 2 * 3;

		static const uint32_t vCount = 4;
		static const uint32_t vStride = sizeof(float) * 3;

		static float* CreateQuad() {

			float* array = new float[3*4] {
				-0.5f, -0.5f, 0.0f,       // position

				0.5f, -0.5f, 0.0f,       // position

				0.5f, 0.5f, 0.0f,       // position


				-0.5f, 0.5f, 0.0f,       // position
			};
	
			return array;
		}
	};
	
	class Cube
	{

	public:
		static const uint32_t indices[12 * 3];
		static const uint32_t iCount = 12 * 3;

		static const uint32_t vStride = sizeof(float) * (3 + 4);
		static const uint32_t vCount = 8;

		static std::vector<float> CreateCube( glm::fvec3 position) {
			return std::vector<float>{
				-0.5f + position.x, -0.5f + position.y, -0.5f + position.z,      1.0f, 0.0f, 1.0f, 1.0f,
				 0.5f + position.x, -0.5f + position.y, -0.5f + position.z,	     1.0f, 0.0f, 1.0f, 1.0f,
				 0.5f + position.x,  0.5f + position.y, -0.5f + position.z,	     1.0f, 0.0f, 1.0f, 1.0f,
				-0.5f + position.x,  0.5f + position.y, -0.5f + position.z,	     1.0f, 0.0f, 1.0f, 1.0f,
				-0.5f + position.x, -0.5f + position.y,  0.5f + position.z,	     1.0f, 0.0f, 1.0f, 1.0f,
				 0.5f + position.x, -0.5f + position.y,  0.5f + position.z,	     1.0f, 0.0f, 1.0f, 1.0f,
				 0.5f + position.x,  0.5f + position.y,  0.5f + position.z,	     1.0f, 0.0f, 1.0f, 1.0f,
				-0.5f + position.x,  0.5f + position.y,  0.5f + position.z,	     1.0f, 0.0f, 1.0f, 1.0f,
			}; 
		}
	};
}