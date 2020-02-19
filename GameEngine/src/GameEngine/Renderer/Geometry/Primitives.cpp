#include "hzpch.h"

#include "Primitives.h"

namespace GameEngine {
	const uint32_t Square::indices[2 * 3] = {
				0, 1, 2,
				2, 3, 0,
	};

	const uint32_t Cube::indices[12 * 3] = {
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
}