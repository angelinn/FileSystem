#ifndef TREE_EXCEPTIONS
#define TREE_EXCEPTIONS

#include <stdexcept>

class TreeException : public std::runtime_error
{
public:
	TreeException(const char* message) : runtime_error(message)
	{  }
};

class InvalidTreeOperation : public TreeException
{
public:
	InvalidTreeOperation(const char* message) : TreeException(message)
	{  }
};


class EmptyTreeOperation : public TreeException
{
public:
	EmptyTreeOperation(const char* message) : TreeException(message)
	{  }
};


class CascadeDeleteWarning : public TreeException
{
public:
	CascadeDeleteWarning(const char* message) : TreeException(message)
	{  }
};

#endif // TREE_EXCEPTIONS