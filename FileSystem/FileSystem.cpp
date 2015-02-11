#include "FileSystem.h"
#include "Sector.h"
#include "FileSystemException.h"
#include <sys/stat.h>
#include <direct.h>
#include "dirent/dirent.h"
#include <iostream>

typedef unsigned char byte;
const char* FileSystem::FILE_NAME = "myFileSystem.bin";

FileSystem::FileSystem() : treeAt(-1), lastFragmentID(-1), totalSize(0)
{  }

FileSystem::~FileSystem()
{
	writeCoreData();
	file.close();
}

void FileSystem::writeCoreData()
{
	file.seekp(0, std::ios::end);
	treeAt = file.tellp();

	files.serialize(file);
	file.write(reinterpret_cast<const char*>(&treeAt), sizeof(size_t));
	file.write(reinterpret_cast<const char*>(&lastFragmentID), sizeof(int));
	file.write(reinterpret_cast<const char*>(&totalSize), sizeof(size_t));
}

void FileSystem::readCoreData()
{
	// ?
	int variables = 2;

	file.seekg(-static_cast<int>(variables * sizeof(int) + sizeof(size_t)), std::ios::end);

	file.read(reinterpret_cast<char*>(&treeAt), sizeof(size_t));
	file.read(reinterpret_cast<char*>(&lastFragmentID), sizeof(int));
	file.read(reinterpret_cast<char*>(&totalSize), sizeof(size_t));

	files.deserialize(file, treeAt);
}

void FileSystem::create(const std::string& path, bool newFS)
{
	if (newFS)
	{
		file.open(path, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
		if (!file)
			throw FileOpeningFailed("Can't open file in create() method.");

		files.setRoot();
	}
	else
	{
		file.open(path, std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
		if (!file)
			throw FileOpeningFailed("Can't open file in create() method.");

		readCoreData();
	}
}

SectorInfo FileSystem::writeToFS(const byte* content, size_t size)
{
	SectorInfo info;
	size_t pos;

	if (deletedSectors.isEmpty())
		file.seekp(0, std::ios::end);
	else
		file.seekp(deletedSectors.peek() * SectorInfo::SECTOR_SIZE, std::ios::beg);

	pos = file.tellg();
	while (!writeCore(content, size, info))
		moveToNextFragmentID();

	return info;
}

void FileSystem::append(byte*& content, size_t size, SectorInfo& info)
{
	file.seekp(-static_cast<int>(SectorInfo::AVAILABLE_SIZE() - info.size), std::ios::cur);
	file.write(reinterpret_cast<const char*>(content), size * sizeof(byte));

	info.size += size;
	if (info.size != SectorInfo::AVAILABLE_SIZE())
	{
		byte* nullBytes = new byte[info.freeSpace()];
		memset(nullBytes, 0xFE, info.freeSpace() * sizeof(byte));

		file.write(reinterpret_cast<const char*>(nullBytes), info.freeSpace() * sizeof(byte));
		delete[] nullBytes;
	}
}

bool FileSystem::writeCore(const byte*& content, size_t& size, SectorInfo& info)
{
	info.nextFragment = getNextFragmentID();

	if (size > SectorInfo::AVAILABLE_SIZE())
	{
		info.size = SectorInfo::AVAILABLE_SIZE();
		info.serialize(file);

		file.write(reinterpret_cast<const char*>(content), info.size * sizeof(byte));
		size -= info.size;
		content += info.size;
		totalSize += SectorInfo::SECTOR_SIZE;

		return false;
	}

	else
	{
		info.size = size;
		info.nextFragment = SectorInfo::noNext;
		info.serialize(file);

		if (content)
			file.write(reinterpret_cast<const char*>(content), info.size * sizeof(byte));

		// FIX IT
		byte* nullBytes = new byte[info.freeSpace()];
		memset(nullBytes, 0x00, info.freeSpace() * sizeof(byte));

		file.write(reinterpret_cast<const char*>(nullBytes), info.freeSpace() * sizeof(byte));
		delete[] nullBytes;
		// ENDFIX

		totalSize += info.size + SectorInfo::informationSize();

		return true;
	}
}

inline int FileSystem::getNextFragmentID() const
{
	return deletedSectors.isEmpty() ? lastFragmentID + 1 : deletedSectors.peek();
}

void FileSystem::moveToNextFragmentID()
{
	if (deletedSectors.isEmpty())
		++lastFragmentID;
	else
		deletedSectors.dequeue();
}

void FileSystem::addEmptyFile(const std::string& file)
{
	stringPair pair = splitPathAndName(file);
	int id = getNextFragmentID();
	moveToNextFragmentID();

	writeToFS(NULL, 0);

	files.insert(pair.first, new File(pair.second, id));
	this->file.flush();
}

void FileSystem::addDirectory(const std::string& dir)
{
	stringPair pair = splitPathAndName(dir);
	files.insert(pair.first, new Directory(pair.second));
}

void FileSystem::moveFile(const std::string& path, const std::string& dest)
{
	TNode* toMove = files.remove(path);

	stringPair pair = splitPathAndName(dest);
	toMove->data->setName(pair.second);

	files.moveTree(files.getNode(pair.first), toMove);
}

// rebuild
void FileSystem::exportFile(const std::string& path, const std::string& dest)
{
	TNode* fileNode = files.getNode(path);

	if (fileNode)
	{
		std::ofstream output(dest, std::ios::out | std::ios::binary);
		if (!output)
			throw InvalidFileOperation("Couldn't open file for writing!");

		file.seekg(fileNode->data->getFragmentID() * SectorInfo::SECTOR_SIZE, std::ios::beg);

		byte* placeholder = NULL;
		allocate<byte>(placeholder, BUFFER_SIZE);

		SectorInfo info;
		size_t filled = 0;
		do
		{
			filled = readFromFS(placeholder, BUFFER_SIZE, info);
			output.write(reinterpret_cast<const char*>(placeholder), filled * sizeof(byte));
		} while (info.nextFragment != SectorInfo::noNext);

		output.close();
		delete[] placeholder;
	}
}

void FileSystem::exportDirectory(const std::string& path, const std::string& dest)
{
	TNode* dirNode = files.getNode(path);
	if (!dirNode)
		throw InvalidFilePath("Dir not found.");

	if (!dirNode->data->isDirectory())
		throw InvalidFileOperation("File is not a directory.");

	_mkdir(dest.c_str());

	for (ListIterator iter = dirNode->children.begin(); iter; ++iter)
	{
		if ((*iter)->data->isDirectory())
			exportDirectory(buildPath(path, (*iter)->data->getName()), buildPath(dest, (*iter)->data->getName()));
		else
			exportFile(buildPath(path, (*iter)->data->getName()), buildPath(dest, (*iter)->data->getName()));
	}

}

size_t FileSystem::readFromFS(byte* content, size_t maxSize, SectorInfo& info)
{
	int filled = 0;

	do
	{
		if (filled >= BUFFER_SIZE)
			if (filled == BUFFER_SIZE)
				break;
			else
				throw InvalidFileOperation("filled > BUFFER_SIZE instead of equal!");

		info.deserialize(file);
		if ((filled + info.size) > BUFFER_SIZE)
		{
			file.seekg(-8, std::ios::cur);
			return filled;
		}

		file.read(reinterpret_cast<char*>(content), sizeof(byte) * info.size);
		filled += info.size;
		content += info.size;
		file.seekg(info.nextFragment * SectorInfo::SECTOR_SIZE, std::ios::beg);
	} while (info.nextFragment != SectorInfo::noNext);

	content -= info.size;
	return filled;
}

// rebuild - ? needs testing
void FileSystem::deleteFile(const std::string& path)
{
	TNode* toDelete = files.getNode(path);
	deletedSectors.enqueue(toDelete->data->getFragmentID());

	delete files.remove(path);
}

// append still needs a little testing
void FileSystem::importFile(const std::string& path, const std::string& dest)
{
	std::ifstream input(path, std::ios::in | std::ios::binary);
	if (!input)
		throw InvalidFileOperation("Can't open file for import!");

	size_t fileSize = File::getFileSize(input);
	if (!fileSize)
	{
		addEmptyFile(dest);
		return;
	}

	stringPair pair = splitPathAndName(dest);

	File* toImport = new File(pair.second, getNextFragmentID());
	moveToNextFragmentID();

	input.seekg(0, std::ios::beg);

	byte* part = NULL;
	allocate<byte>(part, BUFFER_SIZE);

	SectorInfo info;
	info.size = INT_MAX;

	size_t readSize = BUFFER_SIZE;
	while (fileSize)
	{
		if (readSize > fileSize)
			readSize = fileSize;

		input.read(reinterpret_cast<char*>(part), readSize * sizeof(byte));
		info = writeToFS(part, readSize);
		fileSize -= readSize;

		if (info.size < SectorInfo::AVAILABLE_SIZE())
		{
			size_t bytesToWrite = fileSize > info.freeSpace() ? info.freeSpace() : fileSize;
			input.read(reinterpret_cast<char*>(part), bytesToWrite * sizeof(byte));
			append(part, bytesToWrite, info);
			fileSize -= bytesToWrite;
		}

		if (fileSize && info.nextFragment == SectorInfo::noNext)
			setNextFragment(info);
	}

	delete[] part;
	files.insert(pair.first, toImport);
	input.close();
}

void FileSystem::copyFile(const std::string& path, const std::string& dest)
{
	TNode* toCopy = files.getNode(path);
	if (!toCopy)
		throw InvalidFilePath("File not found.");

	stringPair pair = splitPathAndName(dest);
	byte* courier = NULL;
	allocate<byte>(courier, BUFFER_SIZE);
	File* theCopy = new File(pair.second, getNextFragmentID());
	moveToNextFragmentID();

	SectorInfo reader, writer;
	size_t filled = 0;
	size_t tellgPos = toCopy->data->getFragmentID() * SectorInfo::SECTOR_SIZE;

	do
	{
		file.seekg(tellgPos, std::ios::beg);
		filled = readFromFS(courier, BUFFER_SIZE, reader);
		tellgPos = file.tellg();

		writer = writeToFS(courier, filled);

		if (reader.nextFragment != SectorInfo::noNext)
			setNextFragment(writer);

	} while (reader.nextFragment != SectorInfo::noNext);

	delete[] courier;
	files.insert(pair.first, theCopy);
}

void FileSystem::copyDirectory(const std::string& path, const std::string& dest)
{
	TNode* toCopy = files.getNode(path);
	if (!toCopy)
		throw InvalidFilePath("Directory not found.");

	if (!toCopy->data->isDirectory())
		throw InvalidFileOperation("File is not a directory.");

	stringPair pair = splitPathAndName(dest);
	files.insert(pair.first, new Directory(pair.second));

	for (ListIterator iter = toCopy->children.begin(); iter; ++iter)
	{
		// fix
		if ((*iter)->data->isDirectory())
			copyDirectory(path + BACKSLASH_STR + (*iter)->data->getName(), 
						  dest + BACKSLASH_STR + (*iter)->data->getName());
		else
			copyFile(path + BACKSLASH_STR + (*iter)->data->getName(), 
					 dest + BACKSLASH_STR + (*iter)->data->getName());
	}
}

///
/// Checks if the path is a directory, using the stat structure
///
bool FileSystem::isDirectory(const std::string& path) const
{
	struct stat buffer;
	stat(path.c_str(), &buffer);

	/// S_IFMT is a mask, that combined with st_mode can be compared with other masks
	return (buffer.st_mode & S_IFMT) == S_IFDIR;
}

void FileSystem::importDirectory(const std::string& path, const std::string& dest)
{
	if (!isDirectory(path))
		throw InvalidFilePath("File is not a directory!");

	stringPair pair = splitPathAndName(dest);
	files.insert(pair.first, new Directory(pair.second));

	DLList<std::string> fileNames = getFilesFromADirectory(path);
	for (DLList<std::string>::Iterator iter = fileNames.begin(); iter; ++iter)
	{
		if (isDirectory(path + "\\" + (*iter)))
			importDirectory(path + "\\" + (*iter), buildPath(dest, *iter));
		else
			importFile(path + "\\" + (*iter), buildPath(dest, *iter));
	}
}

void FileSystem::rename(const std::string& path, const std::string& newName)
{
	TNode* toRename = files.getNode(path);
	if (!toRename)
		throw InvalidFilePath("File not found.");

	toRename->data->setName(newName);
}

bool FileSystem::setNextFragment(SectorInfo& info)
{
	info.nextFragment = getNextFragmentID();
	moveToNextFragmentID();

	file.seekp(-static_cast<int>(SectorInfo::SECTOR_SIZE), std::ios::cur);
	info.serialize(file);

	return true;
}

DLList<std::string> FileSystem::getFilesFromADirectory(const std::string& path) const
{
	DLList<std::string> fileNames;
	struct dirent* buffer;
	DIR* dir = opendir(path.c_str());

	if (!dir)
		throw InvalidFilePath("Directory not found.");

	while (buffer = readdir(dir))
		if (strcmp(buffer->d_name, ".") && strcmp(buffer->d_name, ".."))
			fileNames.pushBack(buffer->d_name);

	return fileNames;
}

stringPair FileSystem::splitPathAndName(const std::string& path) const
{
	size_t backslash = path.rfind(BACKSLASH_CHAR);

	if (backslash == std::string::npos)
		throw InvalidFilePath("Backslash not found!");

	std::string pathOnly(path, 0, backslash);

	if (!backslash)
		pathOnly = "/";

	std::string name(path, backslash + 1);

	return stringPair(pathOnly, name);
}

void FileSystem::goToLastSector(int firstSectorID)
{
	int currentSectorID = firstSectorID;
	SectorInfo info{ 0, 0 };

	do
	{
		currentSectorID = info.nextFragment;
		file.seekg(SectorInfo::SECTOR_SIZE * currentSectorID, std::ios::beg);
		info.deserialize(file);
	} while (info.nextFragment != SectorInfo::noNext);

	file.seekg(info.size, std::ios::cur);
}

void FileSystem::printTree() const
{
	files.DFS();
}