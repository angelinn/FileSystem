#include "Directory.h"

Directory::Directory(const std::string& n) : File(n)
{
	isDir = true;
}


// Not pretty
Directory::Directory(const File* other) : File(*other)
{  }