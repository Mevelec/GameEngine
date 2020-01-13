#pragma once

#include <cmath>

#include "VoxelData.h"
#include <morton.h>



// An SVO node. Only contains child pointers, extend this if you want parent pointers as well
namespace OcTree {



	template<class T>
	class Node
	{
	public:
		Node()
		{
			this->data = NULL;
			this->childs = nullptr;
		}
	public:
		T data;
		Node<T>* childs;
	};




	template<class T>
	class OcTree
	{
	public:
	public:
		OcTree()
			:
			root()
		{
			this->depth = 6;
			this->splitRec(this->root, this->depth);
		};

		inline bool hasData(Node<T>* node) const { return !(node->data == NULL); }

		void splitRec(Node<T>& node, int depth) {
			if (depth > 0) {
				Node<T>* nodeChilds = this->split(node);
				this->splitRec(nodeChilds[0], depth - 1);
				this->splitRec(nodeChilds[1], depth - 1);
				this->splitRec(nodeChilds[2], depth - 1);
				this->splitRec(nodeChilds[3], depth - 1);
				this->splitRec(nodeChilds[4], depth - 1);
				this->splitRec(nodeChilds[5], depth - 1);
				this->splitRec(nodeChilds[6], depth - 1);
				this->splitRec(nodeChilds[7], depth - 1);
			}
		}

		Node<T>* split(Node<T>& node) { 
			node.childs = new Node<T>[8];
			return node.childs; 
		}
		
		void setNode(T value, uint_fast16_t posx, uint_fast16_t posy, uint_fast16_t posz,  int depthSeek)
		{
			uint_fast32_t mortonCode = morton3D_32_encode(posx, posy, posz);

			int depth =this->depth;
			Node<T> *node = &this->root;
			while (depth > depthSeek)
			{
				depth--;
				node = &(*node).childs[(mortonCode >> 3 * depth) & 7];
			}
			node->data = value;
		}

		Node<T>& getNode(uint_fast16_t posx, uint_fast16_t posy, uint_fast16_t posz, int depthSeek)
		{
			uint_fast32_t mortonCode = morton3D_32_encode(posx, posy, posz);

			int depth = this->depth;
			Node<T>* node = &this->root;
			while (depth > depthSeek)
			{
				depth--;
				node = &(*node).childs[(mortonCode >> 3 * depth) & 7];
			}
			return (*node);
		}
	private :
		Node<T> root;
		int depth;
	};
}


