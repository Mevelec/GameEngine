#pragma once

#include "VoxelData.h"

#define NOCHILD -1
#define NODATA 0


// An SVO node. Only contains child pointers, extend this if you want parent pointers as well
namespace OcTree {

	class Node
	{
	public:
		Node();
	public:
		size_t data;
		Node* children_offset;

		// If the data pointer is NODATA, there is no data
		inline bool hasData() const { return !(data == NODATA);	}
	};

	class OcTree
	{
	public:
		OcTree()
			:
			root()
		{

		};

		Node root;
		int size = 1;

		Node& getNode(int posx, int posy, int posz, int e) {
			int e0 = 30; // Conventionnellement, dans ce code, la largeur du cube racine est de 2^30
			Node& node = this->root;
			while (node.children_offset != NULL && e0 > e) {// tant qu'il y a des fils et que la profondeur n'est pas atteinte
				e0--;// on	 descend d'un niveau dans la profondeur de l'arbre
				node = (Node&)node.children_offset[
					((posx >> e0) & 1) +
						(((posy >> e0) & 1) << 1) +
						(((posz >> e0) & 1) << 2)
				];
			}
			return node;
		}
	};
}


