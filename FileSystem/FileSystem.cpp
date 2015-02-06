#include "FileSystem.h"
#include "Sector.h"
#include "FileSystemException.h"

typedef unsigned char byte;
const char* FileSystem::FILE_NAME = "myFileSystem.bin";

FileSystem::FileSystem() : treeAt(-1), lastFragmentID(0)
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
	file.write(reinterpret_cast<const char*>(&treeAt), sizeof(int));
	file.write(reinterpret_cast<const char*>(&lastFragmentID), sizeof(int));
}

void FileSystem::readCoreData()
{
	file.seekg(-2 * static_cast<int>(sizeof(int)), std::ios::end);

	file.read(reinterpret_cast<char*>(&treeAt), sizeof(int));
	file.read(reinterpret_cast<char*>(&lastFragmentID), sizeof(int));
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

	if (size > SectorInformation::SECTOR_SIZE)
	{
		info.size = SectorInformation::SECTOR_SIZE;
		info.nextFragment = nextFragmentID;
		info.serialize(file);

		file.write(reinterpret_cast<const char*>(content), info.size * sizeof(byte));
		size -= info.size;
		content += info.size;
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

//rebuild ?? really?
void FileSystem::addDirectory(const std::string& dir)
{
	stringPair pair = splitPathAndName(dir);


	files.insert(pair.first, new Directory(pair.second));
}

// rebuild
void FileSystem::importFile(const std::string& path, const std::string& dest)
{
	stringPair pair = splitPathAndName(path);

	File* toImport = new File(pair.second);
	//toImport->read(path);
	files.insert(dest, toImport);
}

// rebuild
void FileSystem::exportFile(const std::string& path, const std::string& dest)
{
	TNode* file = files.getNode(path);

	if (file)
	{
	}//file->data->write(dest);
}

// rebuild
void FileSystem::deleteFile(const std::string& path)
{
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