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
	FileSystem();
	~FileSystem();
	static const char* FILE_NAME;

public:
	void addEmptyFile(const std::string &);
	void importFile(const std::string &, const std::string &);
	void addDirectory(const std::string &);
	void exportFile(const std::string &, const std::string &);
	void deleteFile(const std::string &);

public:

	void moveFile(const std::string &, const std::string &);
	void copyFile(const std::string &, const std::string &);
	std::string getFileInfo(const std::string &);
	void appendText(const std::string &, const std::string &);

private:
	stringPair splitPathAndName(const std::string &) const;
	void goToLastSector(int);
	void write(const byte *, size_t);
	bool writeCore(const byte *&, size_t, int);
	int getStartFragmentID() const;

private:
	int treeAt;
	int lastFragmentID;
	std::fstream file;


private:
	Queue<int> deletedSectors;
	Tree files;
};


#endif // FILE_SYSTEM_H
