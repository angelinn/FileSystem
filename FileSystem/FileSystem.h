#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "Directory.h"
#include "Tree.h"
#include "Tools.h"

class FileSystem
{
public:
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
		
private:
	int treeAt;


private:
	Tree files;
};


#endif // FILE_SYSTEM_H
