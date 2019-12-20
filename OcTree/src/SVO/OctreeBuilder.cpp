#include "OctreeBuilder.h"

#include <vector>
namespace OcTree {

	Node* OctreeBuilder::Create()
	{
		Node* root = new Node();
		root->data = 1;
		return root;
	}
}