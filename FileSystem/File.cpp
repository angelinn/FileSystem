#include "File.h"

File::File(std::string& n) : name(n), content(NULL)
{  }

File::File(const File& other) : content(NULL)
{
	copyFrom(other);
}

File& File::operator=(const File& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

File::~File()
{
	free();
}

void File::free()
{
	delete[] content;
}

void File::copyFrom(const File& other)
{
	name = other.name;
	size = other.size;
	memcpy(content, other.content, other.size * sizeof(byte));
}