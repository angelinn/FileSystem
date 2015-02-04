#include "ByteContainer.h"
#include <stdexcept>
#include <ostream>

ByteContainer::ByteContainer(byte* bytes, size_t volume) : content(bytes), size(volume)
{ 
	if (content && size)
	{
		try
		{
			content = new byte[size];
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

void ByteContainer::write(std::ostream& stream)
{
	stream.write(reinterpret_cast<const char*>(content), size * sizeof(byte));
}
