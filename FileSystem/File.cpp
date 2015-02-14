#include <fstream>
#include "FileSystem.h"

File::File() : firstSectorID(-1), lastSectorID(-1), isDir(false), size(0)
{  }

File::File(std::string n, int st, int end) : name(n), firstSectorID(st), lastSectorID(end), isDir(false), size(0)
{  }

File::File(const File* other) : File(*other)
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
	return name + " - " + std::to_string(size) + " bytes";
}

void File::serialize(std::ostream& output) const
{
	output.write(reinterpret_cast<const char*>(&isDir), sizeof(bool));
	size_t strSize = name.size();

	output.write(reinterpret_cast<const char*>(&strSize), sizeof(size_t));
	output.write(name.c_str(), strSize * sizeof(char));
	output.write(reinterpret_cast<const char*>(&firstSectorID), sizeof(int));
	output.write(reinterpret_cast<const char*>(&lastSectorID), sizeof(int));
	output.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
}

void File::deserialize(std::istream& input)
{
	size_t strSize = 0;
	input.read(reinterpret_cast<char*>(&strSize), sizeof(size_t));

	char* buffer = new char[strSize + 1];
	input.read(buffer, strSize * sizeof(char));

	buffer[strSize] = '\0';
	name = buffer;
	delete[] buffer;

	input.read(reinterpret_cast<char*>(&firstSectorID), sizeof(int));
	input.read(reinterpret_cast<char*>(&lastSectorID), sizeof(int));
	input.read(reinterpret_cast<char*>(&size), sizeof(size_t));
}

void File::setSize(size_t updatedSize)
{
	size = updatedSize;
}

void File::setName(const std::string& updatedName)
{
	name = updatedName;
}

void File::setLastSectorID(int last)
{
	lastSectorID = last;
}
