#pragma once

#include <cmath>

#include "VoxelData.h"



// An SVO node. Only contains child pointers, extend this if you want parent pointers as well
namespace OcTree {

	template<class T>
	class Node
	{
	public:
		Node()
		{
			this->data = NULL;
			this->children_offset = nullptr;
		}
	public:
		T data;
		Node<T>* children_offset;

		// If the data pointer is NODATA, there is no data
		inline bool hasData() const { return !(data == NULL);	}
	};

	template<class T>
	class OcTree
	{
	public:
		OcTree()
			:
			root()
		{

		};

		Node<T> root;
		int size = 64;

		//get nearest node of pos at layer e
		Node<T>& getNode(int posx, int posy, int posz, int e) {
			int e0 = 30; // Conventionnellement, dans ce code, la largeur du cube racine est de 2^30
			Node<T>& node = this->root;
			while (node.children_offset != NULL && e0 > e) {// tant qu'il y a des fils et que la profondeur n'est pas atteinte
				e0--;// on	 descend d'un niveau dans la profondeur de l'arbre
				node = (Node<T>&)node.children_offset[
					((posx >> e0) & 1) +
					(((posy >> e0) & 1) << 1) +
					(((posz >> e0) & 1) << 2)
				];
			}
			return node;
		}

		//get nearest node of pos at layer e
		Node<T>& setNode(T data, int posx, int posy, int posz, int depthSeek = 0) {
			int maxdepth = std::log2(size + 1);
			//depthSeek = depthSeek > 0? depthSeek : maxdepth; // width = 2^depth

			Node<T>& node = this->root;
			while (maxdepth > depthSeek) {// tant qu'il y a des fils et que la profondeur n'est pas atteinte
				maxdepth--;// on	 descend d'un niveau dans la profondeur de l'arbre
				if (node.children_offset == NULL)
				{
					this->subdivide(node);
				}

				node = (Node<T>&)node.children_offset[
					((posx >> size) & 1) +
					(((posy >> size) & 1) << 1) +
					(((posz >> size) & 1) << 2)
				];

			}
			node.data = data;
			return node;
		}

		void subdivide(Node<T>& node)
		{
			node.children_offset = new Node<T>[8];
		}

	};
}


