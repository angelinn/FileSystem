#include <fstream>
#include "FileSystem.h"

File::File(std::string n) : name(n), ByteContainer()
{  }

void File::read(const std::string& path)
{
	std::ifstream input(path, std::ios::in | std::ios::binary);
	if (!input)
		throw 1;

	size_t inputSize = getFileSize(input);

	input.read(reinterpret_cast<char*>(content), inputSize * sizeof(byte));
	input.close();
}

void File::write(const std::string& path)
{
	std::ofstream output(path, std::ios::out | std::ios::binary);
	if (!output)
		throw - 1;

	output.write(reinterpret_cast<const char*>(content), size * sizeof(byte));
	output.close();
}

void File::buurn()
{
	std::ofstream out(FileSystem::FILE_NAME, std::ios::out | std::ios::binary);


}

File::File(const File& other) : ByteContainer(other)
{  }

File& File::operator=(const File& other)
{
	ByteContainer::operator=(other);
	return *this;
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

bool operator==(const File* file, const std::string string)
{
	return file->name.compare(string) == 0;
}