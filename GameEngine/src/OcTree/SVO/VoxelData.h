#pragma once

#include <stdint.h>

namespace OcTree {
	// sizeof(VoxelData would work too)
	const size_t VOXELDATA_SIZE = sizeof(uint_fast64_t) + 2 * (3 * sizeof(float));

	// This struct defines VoxelData for our voxelizer.
	// This is the main memory hogger: the less data you store here, the better.
	struct VoxelData {
		::uint_fast64_t morton;
		int id;

		VoxelData() : morton(0), id(0) {}
		VoxelData(::uint_fast64_t morton, int id) : morton(morton), id(id) {}

		bool operator > (const VoxelData& a) const {
			return morton > a.morton;
		}

		bool operator < (const VoxelData& a) const {
			return morton < a.morton;
		}
	};
}