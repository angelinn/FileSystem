#include <fstream>
#include "FileSystem.h"

File::File() : startFragmentID(0), isDir(false)
{  }

File::File(std::string n, int fragmentID) : name(n), startFragmentID(fragmentID), isDir(false)
{  }

size_t File::getFileSize(std::istream& file)
{
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();

	if (size == -1)
		throw "bla";
	else
		return size;

}

std::string File::toString() const
{
	return name;
}

void File::serialize(std::ostream& output) const
{
	size_t size = name.size();

	output.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	output.write(name.c_str(), size * sizeof(char));
	output.write(reinterpret_cast<const char*>(&startFragmentID), sizeof(int));
	output.write(reinterpret_cast<const char*>(&isDir), sizeof(bool));
}

void File::deserialize(std::istream& input)
{
	size_t size = 0;
	input.read(reinterpret_cast<char*>(&size), sizeof(size_t));

	char* buffer = new char[size + 1];
	input.read(buffer, size * sizeof(char));

	buffer[size] = '\0';
	name = buffer;
	delete[] buffer;

	input.read(reinterpret_cast<char*>(&startFragmentID), sizeof(int));
	input.read(reinterpret_cast<char*>(&isDir), sizeof(bool));
}

bool operator==(const File* file, const std::string& string)
{
	return file->name.compare(string) == 0;
}