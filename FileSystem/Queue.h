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
	const T& peek() const;

private:
	int count;

	Node<T>* first;
	Node<T>* last;
};

template <typename T>
Queue<T>::Queue() : first(NULL), last(NULL), count(0)
{ }

template <typename T>
Queue<T>::~Queue()
{
	clear();
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
	Node<T>* newLast = new Node<T>(element, last);
	last = newLast;

	++count;
	if (count == 1)
		first = last;
}

template <typename T>
T Queue<T>::dequeue()
{
	if (isEmpty())
		throw std::exception("Queue is empty!");

	Node<T>* second = first->next;

	T data = first->data;
	delete first;
	first = second;

	--count;
	return data;
}

template <typename T>
const T& Queue<T>::peek() const
{
	if (isEmpty())
		throw std::exception("Queue is empty!");

	return first->data;
}

#endif // QUEUE_H
