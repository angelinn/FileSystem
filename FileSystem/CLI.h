#ifndef CLI_H
#define CLI_H

#include "FileSystem.h"

class CLI
{
public:
	void createFS();
	void loadFS(const std::string &);

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
	FileSystem fileSystem;
};


#endif // CLI_H
