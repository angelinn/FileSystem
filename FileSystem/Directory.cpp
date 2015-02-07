#include "Directory.h"

Directory::Directory(const std::string& n) : File(n)
{
	isDir = true;
}