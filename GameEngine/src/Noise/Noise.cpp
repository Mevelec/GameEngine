#include "hzpch.h"
#include "Noise.h"

#include <FastNoiseSIMD/FastNoiseSIMD.h>
#include <vector>
#include "GameEngine/Renderer/Material/Texture.h"

namespace GameEngine {
	Noise::Noise(int width, int height, int depth)
		: 
		width(width),
		height(height), 
		depth(depth),
		posX(0),
		posY(0),
		posZ(0)
	{
		this->loadNoiseAt(this->posX, this->posY, this->posZ);
	}


	void Noise::save(const std::string& name)
	{
		std::ofstream img(name + ".ppm");
		img << "P3" << std::endl;
		img << this->width << " " << this->height << std::endl;
		img << "255" << std::endl;

		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				for (int z = 0; z < this->depth; z++)
				{
					int v = abs(this->get(y, (this->height - 1) - x, z)) * 255;
					img << v << " " << v << " " << v << " " << std::endl;
				}
			}
		}
	}
	void Noise::loadNoiseFor(int x, int y, int z) {
		this->loadNoiseAt(x % this->width, y % this->height, z % this->depth);
	}
	void Noise::loadNoiseAt(int x, int y, int z)
	{
		FastNoiseSIMD* myNoise = FastNoiseSIMD::NewFastNoiseSIMD();
		myNoise->SetFrequency(0.1);
		myNoise->SetSeed(1337);
		myNoise->SetNoiseType(FastNoiseSIMD::NoiseType::Perlin);
		/*myNoise->SetFractalType(FastNoiseSIMD::FractalType::FBM);
		myNoise->SetFractalOctaves(5);
		myNoise->SetFractalLacunarity(2.0);
		myNoise->SetFractalGain(5.0);*/
		float* tempnoise = myNoise->GetNoiseSet(x * this->width, y * this->height, z * this->depth, this->width, this->height, this->depth);

		this->noise = std::vector(tempnoise, tempnoise + (this->width * this->height * this->depth));
		FastNoiseSIMD::FreeNoiseSet(tempnoise);

		this->posX = x;
		this->posY = y;
		this->posZ = z;
	}

	const float& Noise::get(int x, int y, int z)
	{
		if (this->posX != x / this->width)
			this->loadNoiseFor(x, y ,z);
		else if (this->posY != y / this->height)
			this->loadNoiseFor(x, y, z);
		else if (this->posZ != z / this->depth)
			this->loadNoiseFor(x, y, z);
		

		if (x >= 0 && x <= this->width)
			if (y >= 0 && y <= this->height)
				if (z >= 0 && z <= this->depth)
					return this->noise[x * this->height * this->depth + y * this->depth + z];
	}
}