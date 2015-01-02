#include "File.h"
#include <fstream>

File::File(std::string& n) : name(n), content(NULL)
{  }

File::File(std::string& n, std::string& otherFilePath) : File(n)
{
	std::ifstream input(otherFilePath, std::ios::in | std::ios::binary);
	size_t inputSize = getFileSize(input);

	input.read(reinterpret_cast<char*>(content), inputSize * sizeof(char));
	input.close();
}

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

size_t File::getFileSize(std::ifstream& file)
{
	file.seekg(std::ios::end);
	std::streamoff size = file.tellg();

	if (size == -1)
		throw "bla";
	else
		return static_cast<size_t>(size);

}

std::string File::toString()
{
	return name;
}