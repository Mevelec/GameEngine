#include "Node.h"
#include <cstring> 

namespace OcTree{
	Node::Node() 
		: 
		data(0), 
		children_base(0)
	{
		memset(childs, (char)NOCHILD, 8);
	}

	inline bool Node::hasChild(unsigned int i) const {
		return !(childs[i] == NOCHILD);
	}

	inline size_t Node::getChildPos(unsigned int i) const {
		if (childs[i] == NOCHILD) {
			return 0;
		}
		else {
			return children_base + childs[i];
		}
	}

	inline bool Node::isNull() const {
		return isLeaf() && !hasData();
	}

	inline bool Node::isLeaf() const {
		if (strncmp(childs, LEAF, 8 * sizeof(char)) == 0) {
			return true;
		}
		return false;
	}

	inline bool Node::hasData() const {
		return !(data == NODATA);
	}
}