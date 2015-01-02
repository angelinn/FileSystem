#ifndef TREE_H
#define TREE_H

#include "TNode.h"
#include "TreeException.h"
#include "Queue.h"

template <typename T>

class Tree
{
public:
	class Iterator
	{
	public:

		Iterator& operator++();
		const Iterator& operator++() const;

		bool operator==(const Iterator &) const;
		bool operator!=(const Iterator &) const;
		operator bool() const { return !nodes.isEmpty(); }
		T operator*() const;
		T& operator*();

	private:
		Iterator(TNode<T> *);
		mutable Queue<TNode<T>*> nodes;

		friend class Tree;
	};

public:
	Tree();
	~Tree();

public:
	Iterator begin() const;

private:
	Tree(const Tree &);
	Tree& operator=(const Tree &);

private:
	typedef typename DLList<TNode<T>*>::Iterator ListIterator;

	TNode<T>* root;
	void deleteTree(TNode<T> *&);
};

template <typename T>
Tree<T>::Iterator::Iterator(TNode<T>* curr)
{
	nodes.enqueue(curr);
}

template <typename T>
const typename Tree<T>::Iterator& Tree<T>::Iterator::operator++() const
{
	TNode<T>* current = nodes.dequeue();
	for (ListIterator iter = current->children.begin(); iter; ++iter)
		nodes.enqueue((*iter));

	return *this;
}

template <typename T>
typename Tree<T>::Iterator& Tree<T>::Iterator::operator++()
{
	return const_cast<Tree<T>::Iterator&> (static_cast<const Tree<T>::Iterator &> (*this).operator++());
}

template <typename T>
bool Tree<T>::Iterator::operator==(const Iterator& other) const
{
	return nodes.peek() == other.nodes.peek();
}

template <typename T>
bool Tree<T>::Iterator::operator!=(const Iterator& other) const
{
	return !((*this) == other);
}

template <typename T>
T& Tree<T>::Iterator::operator*()
{
	if (nodes.peek())
		return nodes.peek()->data;

	throw TreeException("No element selected!");
}

template <typename T>
T Tree<T>::Iterator::operator*() const
{
	if (nodes.peek())
		return nodes.peek()->data;

	throw TreeException("No element selected!");
}

template <typename T>
typename Tree<T>::Iterator Tree<T>::begin() const
{
	return Iterator(root);
}

template <typename T>
Tree<T>::Tree() : root(NULL)
{  }

template <typename T>
Tree<T>::~Tree()
{
	if (root)
		deleteTree(root);
}

template <typename T>
void Tree<T>::deleteTree(TNode<T>*& node)
{
	for (ListIterator iter = node->children.begin(); iter; ++iter)
		deleteTree(*iter);

	delete node;
	node = NULL;
}

#endif // TREE_H