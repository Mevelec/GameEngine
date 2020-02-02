#pragma once

#include <morton.h>

// An SVO node. Only contains child pointers, extend this if you want parent pointers as well
namespace OcTree {

	template<class T>
	class Node
	{
	public:
		Node()
		{
			this->childs = nullptr;
		}
	public:
		T data;
		Node<T>* childs;
	};
}


