#include "FileSystem.h"
#include "Sector.h"
#include "FileSystemException.h"

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

SectorInformation FileSystem::write(const byte* content, size_t size)
{
	SectorInformation info;

	if (deletedSectors.isEmpty())
		file.seekp(0, std::ios::end);
	else
		file.seekp(deletedSectors.peek() * SectorInformation::SECTOR_SIZE, std::ios::beg);

	while (!writeCore(content, size, info))
		moveToNextFragmentID();

	return info;
}

size_t FileSystem::append(byte*& content, std::istream& input, size_t size, SectorInformation& info)
{
	size_t bytesWritten = size > info.freeSpace() ? info.freeSpace() : size;
	input.read(reinterpret_cast<char*>(content), bytesWritten * sizeof(byte));

	file.seekp(-static_cast<int>(SectorInformation::AVAILABLE_SIZE() - info.size), std::ios::cur);
	file.write(reinterpret_cast<const char*>(content), bytesWritten * sizeof(byte));

	info.size += bytesWritten;
	if (info.size != SectorInformation::AVAILABLE_SIZE())
	{
		byte* nullBytes = new byte[info.freeSpace()];
		memset(nullBytes, 0xFE, info.freeSpace() * sizeof(byte));

		file.write(reinterpret_cast<const char*>(nullBytes), info.freeSpace() * sizeof(byte));
		delete[] nullBytes;
	}
	else
	{
		info.nextFragment = getNextFragmentID();
		moveToNextFragmentID();

		file.seekp(-static_cast<int>(SectorInformation::SECTOR_SIZE), std::ios::cur);
		info.serialize(file);
	}

	return bytesWritten;
}

bool FileSystem::writeCore(const byte*& content, size_t& size, SectorInformation& info)
{
	info.nextFragment = getNextFragmentID();

	if (size > SectorInformation::AVAILABLE_SIZE())
	{
		info.size = SectorInformation::AVAILABLE_SIZE();
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
		//file.seekp((-1) * info.size * static_cast<int>(sizeof(byte)), std::ios::cur);

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

	write(NULL, 0);

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

		file.seekg(fileNode->data->getFragmentID() * SectorInformation::SECTOR_SIZE, std::ios::beg);

		byte* placeholder = NULL;
		allocate<byte>(placeholder, BUFFER_SIZE);

		SectorInformation info;
		int filled = 0;

		do
		{
			filled = read(placeholder, info);
			output.write(reinterpret_cast<const char*>(placeholder), filled * sizeof(byte));
		} while (info.nextFragment != SectorInformation::noNext);

		output.close();
		delete[] placeholder;
	}
}

int FileSystem::read(byte* content, SectorInformation& info)
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
		file.seekg(info.nextFragment * SectorInformation::SECTOR_SIZE, std::ios::beg);
	} while (info.nextFragment != SectorInformation::noNext);

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

// Needs Refactoring and append option to be used
void FileSystem::importFile(const std::string& path, const std::string& dest)
{
	std::ifstream input(path, std::ios::in | std::ios::binary);
	if (!input)
		throw InvalidFileOperation("Can't open file for import!");

	stringPair pair = splitPathAndName(dest);

	File* toImport = new File(pair.second, getNextFragmentID());
	moveToNextFragmentID();

	size_t fileSize = File::getFileSize(input);
	input.seekg(0, std::ios::beg);

	byte* part = NULL;
	allocate<byte>(part, BUFFER_SIZE);

	SectorInformation info;
	info.size = INT_MAX;

	size_t readSize = BUFFER_SIZE;
	while (fileSize)
	{
		if (readSize > fileSize)
			readSize = fileSize;

		input.read(reinterpret_cast<char*>(part), readSize * sizeof(byte));
		info = write(part, readSize);
		fileSize -= readSize;

		if (info.size < SectorInformation::AVAILABLE_SIZE())
				fileSize -= append(part, input, fileSize, info);

		//if (fileSize && info.size < SectorInformation::AVAILABLE_SIZE())
		//{
		//	fileSize -= append(part, fileSize, info);
		//	//if (readSize > fileSize)
		//	//	readSize = fileSize;

		//	//;
		//	//fileSize -= append(part, readSize, info);
		//	/*file.seekp(-(int)SectorInformation::SECTOR_SIZE, std::ios::cur);
		//	info.nextFragment = getNextFragmentID();
		//	info.serialize(file);
		//	moveToNextFragmentID();*/
		//}
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

	SectorInformation info;
	int filled = 0;
	int flag = 0;

	file.seekg(toCopy->data->getFragmentID() * SectorInformation::SECTOR_SIZE, std::ios::beg);
	do
	{
		filled = read(courier, info);
		flag = info.nextFragment;
		info = write(courier, filled);

		if (flag != SectorInformation::noNext)
		{
			file.seekp(-(int)SectorInformation::SECTOR_SIZE, std::ios::cur);
			info.nextFragment = getNextFragmentID();
			info.serialize(file);
			moveToNextFragmentID();
			file.seekg(flag * SectorInformation::SECTOR_SIZE, std::ios::beg);
		}

	} while (flag != SectorInformation::noNext);

	delete[] courier;
	files.insert(pair.first, theCopy);
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