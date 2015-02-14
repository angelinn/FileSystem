#include "Directory.h"

Directory::Directory() : File()
{
	isDir = true;
}

Directory::Directory(const std::string& n) : File(n)
{
	isDir = true;
}

// Not pretty
Directory::Directory(const File* other) : File(other)
{  }

std::string Directory::toString() const
{
	return "<" + name + ">";
}