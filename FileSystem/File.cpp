#include <fstream>
#include "FileSystem.h"

File::File(std::string n, int fragmentID) : name(n), startFragmentID(fragmentID)
{  }

//size_t File::getFileSize(std::ifstream& file)
//{
//	file.seekg(std::ios::end);
//	std::streamoff size = file.tellg();
//
//	if (size == -1)
//		throw "bla";
//	else
//		return static_cast<size_t>(size);
//
//}

std::string File::toString()
{
	return name;
}

bool operator==(const File* file, const std::string string)
{
	return file->name.compare(string) == 0;
}