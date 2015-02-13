#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <stdexcept>
#include <istream>
#include <ostream>

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

public:
	void serializeBuiltInType(std::ostream &);
	void deserializeBuiltInType(std::istream &);

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
	if (!last)
		last = new Node<T>(element, NULL);
	else
	{
		Node<T>* newLast = new Node<T>(element, NULL);
		last->next = newLast;
		last = newLast;
	}

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

template <typename T>
void Queue<T>::serializeBuiltInType(std::ostream& output)
{
	T data;

	output.write(reinterpret_cast<const char*>(&count), sizeof(int));
	while (!isEmpty())
	{
		data = dequeue();
		output.write(reinterpret_cast<const char*>(&data), sizeof(T));
	}
}

template <typename T>
void Queue<T>::deserializeBuiltInType(std::istream& input)
{
	int size = 0;
	input.read(reinterpret_cast<char*>(&size), sizeof(int));

	T data;
	for (int i = 0; i < size; ++i)
	{
		input.read(reinterpret_cast<char*>(&data), sizeof(T));
		enqueue(data);
	}
}


#endif // QUEUE_H
