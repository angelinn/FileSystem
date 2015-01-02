#ifndef TNODE_H
#define TNODE_H

#include "DLList.h"

template <typename T>

class TNode
{
public:
	TNode(const T &);

	DLList<TNode*> children;
	T data;

private:
	TNode(const TNode &);
	TNode& operator=(const TNode &);
};

template <typename T>
TNode<T>::TNode(const T& item) : data(item)
{  }

#endif // TNODE_H