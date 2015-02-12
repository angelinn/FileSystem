#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "Directory.h"
#include "Tree.h"
#include "Tools.h"
#include "Queue.h"
#include <fstream>

class FileSystem
{
	typedef unsigned char byte;

public:
	void printTree() const;

	FileSystem();
	~FileSystem();
	static const char* FILE_NAME;

	void create(const std::string &, bool = false);

public:
	void addEmptyFile(const std::string &);
	void addDirectory(const std::string &);
	void importFile(const std::string &, const std::string &);
	void importDirectory(const std::string &, const std::string &);
	void exportFile(const std::string &, const std::string &);
	void exportDirectory(const std::string &, const std::string &);
	void deleteFile(const std::string &);
	void moveFile(const std::string &, const std::string &);
	void copyFile(const std::string &, const std::string &);
	void copyDirectory(const std::string &, const std::string &);
	bool isDirectory(const std::string &) const;
	void rename(const std::string &, const std::string &);
	void appendText(const std::string &, const std::string &);
	std::string getFileInfo(const std::string &);

private:
	size_t readFromFS(byte *, size_t, SectorInfo &);
	stringPair splitPathAndName(const std::string &) const;
	DLList<std::string> getFilesFromADirectory(const std::string &) const;

	SectorInfo writeToFS(const byte *, size_t);
	bool writeCore(const byte *&, size_t &, SectorInfo &);
	void append(byte *&, size_t, SectorInfo &);

	int getNextFragmentID() const;
	void moveToNextFragmentID();
	bool setNextFragment(SectorInfo &);

	void writeCoreData();
	void readCoreData();

public:
	TNode* getFile(const std::string& str) { return files.getNode(str); }
	void flush() { file.flush(); }

private:
	size_t treeAt;
	int lastFragmentID;
	std::fstream file;

	void goToLastSector(int);
private:
	// TO DO : Serialize Queue
	Queue<int> deletedSectors;
	Tree files;
	size_t totalSize;
};


#endif // FILE_SYSTEM_H
