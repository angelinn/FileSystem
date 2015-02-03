#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "Directory.h"
#include "Tree.h"

class FileSystem
{
public:
	void addEmptyFile();
	void addFile(const std::string &);
	void addFile(const File *);
	void addDirectory(const File *);
	void exportFile(const std::string &, const std::string &);
	void deleteFile(const std::string &);
	void moveFile(const std::string &, const std::string &);
	void copyFile(const std::string &, const std::string &);
	std::string getFileInfo(const std::string &);
	void appendText(const std::string &, const std::string &);

private:
	Tree files;
};


#endif // FILE_SYSTEM_H
