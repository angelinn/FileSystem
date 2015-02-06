#include <fstream>
#include "FileSystem.h"

File::File() : startFragmentID(0), isDirectory(false)
{  }

File::File(std::string n, int fragmentID, bool isDir) : name(n), startFragmentID(fragmentID), isDirectory(isDir)
{  }

size_t File::getFileSize(std::fstream& file)
{
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();

	if (size == -1)
		throw "bla";
	else
		return size;

}

std::string File::toString()
{
	return name;
}

void File::serialize(std::fstream& output) const
{
	size_t size = name.size();

	output.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	output.write(name.c_str(), size * sizeof(char));
	output.write(reinterpret_cast<const char*>(&isDirectory), sizeof(bool));
}

void File::deserialize(std::fstream& input)
{
	size_t size = 0;
	input.read(reinterpret_cast<char*>(&size), sizeof(size_t));

	char* buffer = new char[size + 1];
	input.read(buffer, size * sizeof(char));

	buffer[size] = '\0';
	name = buffer;
	delete[] buffer;

	input.read(reinterpret_cast<char*>(&isDirectory), sizeof(bool));
}

bool operator==(const File* file, const std::string string)
{
	return file->name.compare(string) == 0;
}