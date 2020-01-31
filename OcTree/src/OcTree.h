#include "SVO/Node.h"
#include "SVO/VoxelData.h"

namespace OcTree {

	template<class T>
	class  Octree
	{
	public:
		virtual T& get(uint_fast16_t x, uint_fast16_t y, uint_fast16_t z);
		virtual void set(const T&, uint_fast16_t x, uint_fast16_t y, uint_fast16_t z);

		virtual int getWidth();
	};
}