#include "ByteContainer.h"
#include <stdexcept>

ByteContainer::ByteContainer(byte* bytes, size_t volume) : content(content), size(volume)
{ 
	if (bytes && volume)
	{
		try
		{
			bytes = new byte[volume];
		}
		catch (std::bad_alloc&)
		{
			free();
			throw;
		}
	}
}

ByteContainer::ByteContainer(const ByteContainer& other) : content(NULL), size(0)
{
	copyFrom(other);
}

ByteContainer& ByteContainer::operator=(const ByteContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ByteContainer::~ByteContainer()
{
	free();
}

void ByteContainer::copyFrom(const ByteContainer& other)
{
	size = other.size;
	memcpy(content, other.content, other.size * sizeof(byte));
}

void ByteContainer::free()
{
	delete[] content;
}