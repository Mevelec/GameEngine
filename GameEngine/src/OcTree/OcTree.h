#pragma once
#include "SVO/Node.h"
#include <cmath>
#include <morton.h>

namespace OcTree {
	template <class T>
	class Octree
	{
	public:
		virtual T& get(int posx, int posy, int posz) = 0;
		virtual void set(T value, int posx, int posy, int posz) = 0;

		virtual int getWidth() = 0;
	};
  }