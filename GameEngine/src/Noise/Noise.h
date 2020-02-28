#pragma once

namespace GameEngine {

	class Noise
	{
	public:
		Noise(int width, int height, int depth = 1);
		void save();

		const float& get(int x, int y, int z);
	private :
		int width, height, depth;

		std::vector<float> noise;
	};
}


