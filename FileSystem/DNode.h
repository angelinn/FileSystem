#ifndef DNODE_H
#define DNODE_H

#include <stdlib.h>

template <typename T>

class DNode
{
public:
	DNode(DNode<T> *, const T &, DNode<T> *);
	DNode(const DNode<T> &);

	DNode<T>* next;
	DNode<T>* prev;
	T data;
};

template <typename T>
DNode<T>::DNode(DNode<T>* nPrev, const T& item, DNode<T>* nNext) : prev(nPrev), data(item), next(nNext)
{ }

template <typename T>
DNode<T>::DNode(const DNode<T>& other)
{
	prev = other.prev ? new DNode(*other.prev) : NULL;
	next = other.next ? new DNode(*other.next) : NULL;

	data = other.data
}

#endif // DNODE_H
