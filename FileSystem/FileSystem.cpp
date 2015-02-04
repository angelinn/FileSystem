#include "FileSystem.h"
#include <fstream>

const char* FILE_PATH = "myFileSystem.bin";

void FileSystem::addEmptyFile(const std::string& file)
{
	stringPair pair = splitPathAndName(file);
	files.insert(pair.first, new File(pair.second));
}

void FileSystem::addDirectory(const std::string& dir)
{
	stringPair pair = splitPathAndName(dir);
	files.insert(pair.first, new Directory(pair.second));
}

void FileSystem::importFile(const std::string& path, const std::string& dest)
{
	stringPair pair = splitPathAndName(path);

	File* toImport = new File(pair.second);
	toImport->read(path);
	files.insert(dest, toImport);
}

void FileSystem::exportFile(const std::string& path, const std::string& dest)
{
	TNode* file = files.getNode(path);

	if (file)
		file->data->write(dest);
}

void FileSystem::deleteFile(const std::string& path)
{
	files.remove(path);
}


stringPair FileSystem::splitPathAndName(const std::string& path) const
{
	size_t backslash = path.rfind(BACKSLASH_CHAR);

	if (backslash == std::string::npos)
		throw - 1;

	std::string pathOnly(path, 0, backslash);
	std::string name(path, backslash + 1);

	return stringPair(pathOnly, name);
}