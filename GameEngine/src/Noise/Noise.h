#pragma once

namespace GameEngine {

	class Noise
	{
	public:
		Noise(int width, int height, int depth = 1);
		void save(const std::string& name);

		const float& get(int x, int y, int z);
		void loadNoiseFor(int x, int y, int z);
		void loadNoiseAt(int x, int y, int z);

	private :
		int width, height, depth;
		int posX, posY, posZ;

		std::vector<float> noise;
	};
}


