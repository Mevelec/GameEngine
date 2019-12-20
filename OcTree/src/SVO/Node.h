#pragma once

#define NOCHILD -1
#define NODATA 0

const char LEAF[8] = { NOCHILD, NOCHILD, NOCHILD, NOCHILD, NOCHILD, NOCHILD, NOCHILD, NOCHILD };

namespace OcTree {
	class Node
	{
	public:
		Node();
	public:
		size_t data;
		size_t children_base;
		char childs[8];

		bool hasChild(unsigned int i) const;
		size_t getChildPos(unsigned int i) const;
		bool isLeaf() const;
		bool hasData() const;
		bool isNull() const;
	};
}


