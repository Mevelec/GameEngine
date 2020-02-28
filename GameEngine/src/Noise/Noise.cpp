#include "hzpch.h"
#include "Noise.h"

#include <FastNoiseSIMD/FastNoiseSIMD.h>

#include "GameEngine/Renderer/Material/Texture.h"

namespace GameEngine {
	Noise::Noise(int width, int height, int depth)
		: 
		width(width),
		height(height), 
		depth(depth)
	{
		FastNoiseSIMD* myNoise = FastNoiseSIMD::NewFastNoiseSIMD();
		myNoise->SetFrequency(0.01);
		myNoise->SetSeed(1337);
		myNoise->SetNoiseType(FastNoiseSIMD::NoiseType::Perlin);
		float* noiseSet = myNoise->GetNoiseSet(0, 0, 0, this->width, this->height, this->depth);



		std::ofstream img("picture.ppm");
		img << "P3" << std::endl;
		img << this->width << " " << this->height << std::endl;
		img << "255" << std::endl;

		int index = 0;
		for (int x = 0; x < this->width; x++)
		{
			for (int y = 0; y < this->height; y++)
			{
				for (int z = 0; z < this->depth; z++)
				{
					int v = abs(noiseSet[index]) * 255;
					img << v << " " << v << " " << v << " " << std::endl;

					index++;
				}
			}
		}		

		FastNoiseSIMD::FreeNoiseSet(noiseSet);
		system("open picture.ppm");
	}
}