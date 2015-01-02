#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <stdexcept>

template <typename T>
class Queue
{
public:
	Queue();
	~Queue();

private:
	Queue& operator=(const Queue &);
	Queue(const Queue &);

public:
	int getSize() const { return count; }
	bool isEmpty() const { return !count; }
	void clear();
	void enqueue(const T &);
	T dequeue();
	T& peek();

private:
	int count;

	Node<T>* first;
	Node<T>* last;

	Node<T>* getAt(int);
	void copyFrom(const Queue &);
};

template <typename T>
Queue<T>::Queue() : first(NULL), last(NULL), count(0)
{ }

template <typename T>
Queue<T>::Queue(const Queue& other)
{
	copyFrom(other);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other)
{
	if (this != &other)
	{
		clear();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
Queue<T>::~Queue()
{
	clear();
}

template <typename T>
void Queue<T>::copyFrom(const Queue& other)
{
	first = other.first ? new Node<T>(*other.first) : NULL;
	last = other.last ? new Node<T>(*other.last) : NULL;

	count = other.count;
}

template <typename T>
void Queue<T>::clear()
{
	while (!isEmpty())
		dequeue();
}

template <typename T>
void Queue<T>::enqueue(const T& element)
{
	Node<T>* newFirst = new Node<T>(element, first);
	first = newFirst;

	++count;
	if (count == 1)
		last = first;
}

template <typename T>
Node<T>* Queue<T>::getAt(int position)
{
	if (position >= count)
		throw std::out_of_range("Invalid position!");

	Node<T>* result = first;
	while (position > 0)
	{
		result = result->next;
		--position;
	}

	return result;
}

template <typename T>
T Queue<T>::dequeue()
{
	if (isEmpty())
		throw std::exception("Queue is empty!");

	Node<T>* preLast = getAt(count - 2);
	preLast->next = NULL;

	T data = last->data;
	delete last;
	last = preLast;

	--count;
	return data;
}

template <typename T>
T& Queue<T>::peek()
{
	if (isEmpty())
		throw std::exception("Queue is empty!");

	return last->data;
}

#endif // QUEUE_H
