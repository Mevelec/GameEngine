#include "hzpch.h"

#include "Primitives.h"

namespace GameEngine {
	const uint32_t Square::indices[2 * 3] = {
				0, 1, 2,
				2, 3, 0,
	};

	const uint32_t CubeSimple::indices[12 * 3] = {
				0, 1, 2,
				2, 3, 0,

				4, 5, 6,
				6, 7, 4,

				4, 0, 3,
				3, 7, 4,

				5, 1, 2,
				2, 6, 5,

				0, 1, 5,
				5, 4, 0,

				3, 2, 6,
				6, 7, 3,
	};

	const uint32_t Cube::indices[12 * 3] = {
				0, 1, 2,
				2, 3, 0,

				4, 5, 6,
				6, 7, 4,

				8, 9, 10,
				10, 11, 8,

				12, 13, 14,
				14, 15, 12,

				16, 17, 18, 
				18, 19, 16,

				20, 21, 22,
				22, 23, 20, 
	};
}