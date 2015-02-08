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
	void importFile(const std::string &, const std::string &);
	void addDirectory(const std::string &);
	void exportFile(const std::string &, const std::string &);
	void deleteFile(const std::string &);
	void moveFile(const std::string &, const std::string &);
	void copyFile(const std::string &, const std::string &);

public:
	std::string getFileInfo(const std::string &);
	void appendText(const std::string &, const std::string &);

	TNode* getFile(const std::string& str) { return files.getNode(str); }

private:
	int read(byte *, SectorInformation &);
	void writeCoreData();
	void readCoreData();
	stringPair splitPathAndName(const std::string &) const;
	void goToLastSector(int);
	SectorInformation write(const byte *, size_t);
	bool writeCore(const byte *&, size_t &, SectorInformation &);
	int getNextFragmentID() const;
	void moveToNextFragmentID();
	size_t append(byte *&, size_t, SectorInformation &);
	

private:
	int treeAt;
	int lastFragmentID;
	std::fstream file;


private:
	// TO DO : Serialize Queue
	Queue<int> deletedSectors;
	Tree files;
	size_t totalSize;
};


#endif // FILE_SYSTEM_H
