#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

template <typename T>

class Node
{
public:
	Node(const T &, Node<T> *);
	Node(const Node<T> &);

	Node<T>* next;
	T data;
};

template <typename T>
Node<T>::Node(const T& item, Node<T>* nNext) : next(nNext), data(item)
{ }

template <typename T>
Node<T>::Node(const Node<T>& other)
{
	next = other.next ? new Node<T>(*other.next) : NULL;

	data = other.data;
}

#endif // NODE_H
