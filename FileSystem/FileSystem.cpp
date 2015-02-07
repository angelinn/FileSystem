#include "FileSystem.h"
#include "Sector.h"
#include "FileSystemException.h"

typedef unsigned char byte;
const char* FileSystem::FILE_NAME = "myFileSystem.bin";

FileSystem::FileSystem() : treeAt(-1), lastFragmentID(0), totalSize(0)
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
	int variables = 3;

	file.seekg(- variables * static_cast<int>(sizeof(int)), std::ios::end);

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

void FileSystem::write(const byte* content, size_t size)
{
	while (!deletedSectors.isEmpty())
	{
		file.seekp(deletedSectors.dequeue() * SectorInformation::SECTOR_SIZE, std::ios::beg);

		if (deletedSectors.isEmpty())
		{
			if (writeCore(content, size, lastFragmentID++))
				return;
		}
		else if (writeCore(content, size, deletedSectors.dequeue()))
			return;
	}

	std::streamoff a = 0;
	file.seekp(0, std::ios::end);
	while (!writeCore(content, size, lastFragmentID++))
	{  }
}

bool FileSystem::writeCore(const byte*& content, size_t size, int nextFragmentID)
{
	SectorInformation info;

	if (size > SectorInformation::AVAILABLE_SIZE())
	{
		info.size = SectorInformation::AVAILABLE_SIZE();
		info.nextFragment = nextFragmentID;
		info.serialize(file);

		file.write(reinterpret_cast<const char*>(content), info.size * sizeof(byte));
		size -= info.size;
		content += info.size;
		totalSize += SectorInformation::SECTOR_SIZE;

		return false;
	}

	else
	{
		info.size = size;
		info.nextFragment = SectorInformation::noNext;
		info.serialize(file);

		if (content)
			file.write(reinterpret_cast<const char*>(content), info.size * sizeof(byte));

		// FIX IT
		byte* nullBytes = new byte[info.freeSpace()];
		memset(nullBytes, 0x00, info.freeSpace() * sizeof(byte));

		file.write(reinterpret_cast<const char*>(nullBytes), info.freeSpace() * sizeof(byte));
		delete[] nullBytes;
		// ENDFIX

		totalSize += info.size + SectorInformation::informationSize();
		return true;
	}
}

int FileSystem::getStartFragmentID() const
{
	return deletedSectors.isEmpty() ? lastFragmentID : deletedSectors.peek();
}

void FileSystem::addEmptyFile(const std::string& file)
{
	stringPair pair = splitPathAndName(file);
	int id = getStartFragmentID();

	write(NULL, 0);

	files.insert(pair.first, new File(pair.second, id));
	this->file.flush();
}

void FileSystem::addDirectory(const std::string& dir)
{
	stringPair pair = splitPathAndName(dir);
	files.insert(pair.first, new Directory(pair.second));
}

// Needs Testing
void FileSystem::importFile(const std::string& path, const std::string& dest)
{
	stringPair pair = splitPathAndName(path);

	File* toImport = new File(pair.second, getStartFragmentID());

	std::ifstream input(path, std::ios::in | std::ios::binary);
	if (!input)
		throw InvalidFileOperation("Can't open file for import!");

	size_t readSize = 64 * KILO_BYTE;
	size_t fileSize = File::getFileSize(input);
	input.seekg(0, std::ios::beg);

	byte* part = new byte[readSize];

	while (fileSize)
	{
		if (readSize > fileSize)
			readSize = fileSize;

		input.read(reinterpret_cast<char*>(part), readSize * sizeof(byte));
		write(part, readSize);
		fileSize -= readSize;
	}


	files.insert(dest, toImport);
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

		file.seekp(fileNode->data->getFragmentID(), std::ios::beg);


	}//file->data->write(dest);
}

// rebuild - ? needs testing
void FileSystem::deleteFile(const std::string& path)
{
	TNode* toDelete = files.getNode(path);
	deletedSectors.enqueue(toDelete->data->getFragmentID());

	files.remove(path);
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
	SectorInformation info{ 0, 0 };

	do
	{
		currentSectorID = info.nextFragment;
		file.seekg(SectorInformation::SECTOR_SIZE * currentSectorID, std::ios::beg);
		info.deserialize(file);
	} while (info.nextFragment != SectorInformation::noNext);

	file.seekg(info.size, std::ios::cur);
}

void FileSystem::printTree() const
{
	files.DFS();
}