#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "Directory.h"
#include "Tree.h"
#include "Tools.h"
#include "Queue.h"
#include "WriteState.h"
#include <fstream>

struct ReadState;

class FileSystem
{
	typedef unsigned char byte;

public:
	FileSystem();
	~FileSystem();
	void create(const std::string &, bool);

public:
	void addEmptyFile(const std::string &);
	void addDirectory(const std::string &);
	void importFile(const std::string &, const std::string &);
	void importDirectory(const std::string &, const std::string &);
	void exportFile(const std::string &, const std::string &);
	void exportDirectory(const std::string &, const std::string &);
	void deleteFile(const std::string &);
	void deleteDirectory(const std::string &);
	void moveFile(const std::string &, const std::string &);
	void copyFile(const std::string &, const std::string &);
	void copyDirectory(const std::string &, const std::string &);
	bool isDirectory(const std::string &) const;
	void rename(const std::string &, const std::string &);
	void appendText(const std::string &, const std::string &);
	std::string getFileInfo(const std::string &);

private:
	ReadState readFromFS(byte *, size_t);
	stringPair splitPathAndName(const std::string &) const;
	DLList<std::string> getFilesFromADirectory(const std::string &) const;

	WriteState writeToFS(const byte *, size_t);
	bool writeCore(const byte *&, size_t &, WriteState &);
	void append(const byte *, size_t, SectorInfo &);

	int getNextSectorID() const;
	void moveTonextSectorID();
	bool setnextSector(SectorInfo &);

	void writeCoreData();
	void readCoreData();

public:
	TNode* getFile(const std::string& str) { return files.getNode(str); }
	size_t getTotalSize() const { return totalSize; }
	void deleteAllSectors(size_t);

private:
	size_t treeAt;
	int lastFragmentID;
	std::fstream file;

private:
	Queue<int> deletedSectors;
	Tree files;
	size_t totalSize;
};


#endif // FILE_SYSTEM_H
